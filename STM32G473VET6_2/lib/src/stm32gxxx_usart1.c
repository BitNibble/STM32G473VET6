/******************************************************************************
    STM32GXXXUSART1.C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473 (sigleton model)
Date:     08/06/2026
*******************************************************************************/
#include "stm32gxxx_usart1.h"
#include <stdio.h>
#include <string.h>

#define USART1_RX_COUNT (USART1_RX_SIZE - ONE)
#define USART1_TX_COUNT (USART1_TX_SIZE - ONE)
/* Static private memory allocation buffers hidden from application workspace */
static uint8_t u1_rx_raw[USART1_RX_SIZE + ONE] = {0}; // overflow safety
static uint8_t u1_tx_raw[USART1_TX_SIZE] = {0};

/*** USART1 PARAMETER ***/
static USART1_par par_setup = {
	.wordlength     = 8,
	.stopbit        = 0,
	.samplingmode   = 16,
	.baudrate       = 38400,
	.rx_left 		= 0,
	.rx_read_index  = 0,
	.rx_write_index = 0,
	.rx_available   = 0,
	.rx_overflow    = 0,
	.tx_busy        = 0,
	.buff_rx        = u1_rx_raw,
	.buff_tx        = u1_tx_raw
};

static void impl_config(USART1_par par_setup);
static void impl_init(void);
static void impl_start_rx(void);
static uint16_t impl_read(uint8_t *out);
static char impl_read_char(void);
static uint16_t impl_read_str(char* str);
static uint16_t impl_read_str_size(char* str, uint16_t max_len);
static void impl_send(const uint8_t *data, uint16_t len);
static uint8_t impl_tx_ready(void);
void impl_send_v2(const uint8_t *data, uint16_t len);
uint8_t impl_tx_ready_v2(void);
static uint16_t impl_get_rx_left(void);
static uint16_t impl_get_rx_read_index(void);
static uint16_t impl_get_rx_write_index(void);
static uint16_t impl_rx_available(void);
static void default_idle_irq(void);
static void default_dma_tx_irq(void);

/*** USART1 CALLBACK ***/
static USART1_irq	irq_setup = {
	.idle    = default_idle_irq,
	.dma_tx = default_dma_tx_irq,
};
/*** USART1 V-TABLE ***/
static USART1_run run_setup = {
	.config             = impl_config,
	.init               = impl_init,
	.start_rx           = impl_start_rx,
	.read               = impl_read,
	.read_char          = impl_read_char,
	.read_str           = impl_read_str,
	.read_str_size      = impl_read_str_size,
	.send               = impl_send,
	.tx_ready           = impl_tx_ready,
	.get_rx_left        = impl_get_rx_left,
	.get_rx_read_index  = impl_get_rx_read_index,
	.get_rx_write_index = impl_get_rx_write_index,
	.rx_available       = impl_rx_available
};

/*** USART1 HANDLER ***/
static USARTG4_Handle handle_instance = {
		.par = &par_setup,
		.irq = &irq_setup,
		.run = &run_setup
};

/*** USART1 ACCESSOR FUNCTION ***/
USARTG4_Handle* usart1(void) { return &handle_instance; }

/* ============================================================================
   DRIVER CODE IMPLEMENTATIONS
   ============================================================================ */
static inline uint16_t _rx_dma_write_snapshot(void) {
    return USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;
}

/******/
static void impl_set_wordlength(uint8_t wordlength) {
	volatile uint32_t* cr1_reg = &(dev()->comm->usart1->CR1);
	// Setup Word Length (Split across CR1->M1 and CR1->M0)
	uint32_t m0_val = 0;
	uint32_t m1_val = 0;

	switch(wordlength) {
		case 7:  // 7-bit data
			m0_val = 0;
			m1_val = 1;
			break;
		case 9:  // 9-bit data
			m0_val = 1;
			m1_val = 0;
			break;
		case 8:  // 8-bit data (Default)
		default:
			m0_val = 0;
			m1_val = 0;
			break;
	}
	write_field_value(cr1_reg, USART_CR1_M0_Msk, USART_CR1_M0_Pos, m0_val);
	write_field_value(cr1_reg, USART_CR1_M1_Msk, USART_CR1_M1_Pos, m1_val);
}

static void impl_set_stopbit(uint8_t stopbit) {
	volatile uint32_t* cr2_reg = &(dev()->comm->usart1->CR2);
	write_field_value(cr2_reg, USART_CR2_STOP_Msk, USART_CR2_STOP_Pos, stopbit);
}

static void impl_set_samplingmode(uint8_t samplingmode) {
	volatile uint32_t* cr1_reg = &(dev()->comm->usart1->CR1);
	if(samplingmode == 8) {
	    write_field_value(cr1_reg, USART_CR1_OVER8_Msk, USART_CR1_OVER8_Pos, ONE);
	} else {
		write_field_value(cr1_reg, USART_CR1_OVER8_Msk, USART_CR1_OVER8_Pos, ZERO);
	}
}

static uint8_t impl_get_samplingmode(void) {
	if(get_field_value(dev()->comm->usart1->CR1, USART_CR1_OVER8_Msk, USART_CR1_OVER8_Pos)){
		return 8;
	} else {
		return 16;
	}
}

static void impl_set_baudrate(uint32_t baudrate) {
	uint32_t pclk = dev()->get_par->pclk2();
	uint32_t brr_calculated_val = ZERO;
	// Calculate BRR using direct floor division (as expected by STM32 hardware)
	if (impl_get_samplingmode() == 8) {
		// Oversampling by 8
		// Hardware expects: (2 * pclk) / baudrate
		uint32_t usartdiv = (2 * pclk) / baudrate;
		// Shift logic to fit USARTDIV into BRR register fields when OVER8 = 1
		brr_calculated_val = (usartdiv & 0xFFF0) | ((usartdiv & 0x0007) >> 1);
	} else {
		// Oversampling by 16 (Standard Mode)
		brr_calculated_val = pclk / baudrate;
	}
	// Write calculated value to the USART1 BRR Register
	write_field_value(&(dev()->comm->usart1->BRR), USART_BRR_BRR_Msk, USART_BRR_BRR_Pos, brr_calculated_val);
}

static void impl_config(USART1_par par) {
	par.buff_rx = u1_rx_raw;
	par.buff_tx = u1_tx_raw;
	par_setup = par;
    // Setup Word Length (Split across CR1->M1 and CR1->M0)
    impl_set_wordlength(par_setup.wordlength);
    // Setup Stop Bits (CR2->STOP[1:0])
    // Expected input values standard mapping: 00: 1 Stop bit, 01: 0.5 Stop bit, 10: 2 Stop bits, 11: 1.5 Stop bits
    impl_set_stopbit(par_setup.stopbit);
    // Setup Sampling Mode (CR1->OVER8)
    // 0: Oversampling by 16, 1: Oversampling by 8
    impl_set_samplingmode(par_setup.samplingmode);
    // Fetch the peripheral clock frequency
    impl_set_baudrate(par_setup.baudrate);
}

static void impl_init(void) {
    // Gating Clocks via Native GPIO and Clock System tree APIs
	dev()->run->gpio_clock(dev()->gpio->a, ONE);
    set_reg(&(dev()->sys->rcc->AHB1ENR), RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN);
    set_reg(&(dev()->sys->rcc->APB2ENR), RCC_APB2ENR_USART1EN);

    // Configure Alternate Pin Functions using your tool functions (AF7 for USART1)
    dev()->run->gpio_moder(GPIOA, 9,  MODE_AF);  // PA9  -> TX Line
    dev()->run->gpio_moder(GPIOA, 10, MODE_AF);  // PA10 -> RX Line
    dev()->run->gpio_af(GPIOA, 9,  7);
    dev()->run->gpio_af(GPIOA, 10, 7);

    dev()->run->gpio_ospeed(GPIOA, 9,  3);
    dev()->run->gpio_ospeed(GPIOA, 10, 3);

    dev()->run->gpio_otype(GPIOA, 9,  0);
    dev()->run->gpio_otype(GPIOA, 10, 0);

    dev()->run->gpio_pupd(GPIOA, 9,  0);
    dev()->run->gpio_pupd(GPIOA, 10, 1);

    // Routing Peripheral Signals into DMAMUX Matrices (Ch1=RX, Ch2=TX)
    write_field_value(&(dev()->dma->dmamux1_ch1->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 24);
    write_field_value(&(dev()->dma->dmamux1_ch2->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 25);

    // Configure DMA RX Channel (Circular mode)
    clear_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch1->CPAR  = (uint32_t)&(dev()->comm->usart1->RDR);
    dev()->dma->dma1_ch1->CMAR  = (uint32_t)par_setup.buff_rx;
    dev()->dma->dma1_ch1->CNDTR = USART1_RX_SIZE;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_PL_0);

    // Configure DMA TX Channel (Normal Single-Shot mode)
    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CPAR  = (uint32_t)&(dev()->comm->usart1->TDR);
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE);
    //set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_MINC | DMA_CCR_DIR);

    // Set USART registers using dynamic system clock reading helper
    clear_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    impl_set_baudrate(par_setup.baudrate);

    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_TE | USART_CR1_RE | USART_CR1_IDLEIE);
    set_reg(&(dev()->comm->usart1->CR3), USART_CR3_DMAT | USART_CR3_DMAR);
    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    // Core NVIC Interrupt Vectors Configurations
    NVIC_SetPriority(USART1_IRQn, 5);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(DMA1_Channel2_IRQn, 5);
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

static void impl_start_rx(void) {
    par_setup.rx_read_index  = ZERO;
    par_setup.rx_write_index = ZERO;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
}

static uint16_t impl_read(uint8_t *out) {
    if (isPtrNull(out)) return ZERO;

    par_setup.rx_write_index = _rx_dma_write_snapshot();

    if (par_setup.rx_read_index == par_setup.rx_write_index) {
        return ZERO;
    }

    *out = par_setup.buff_rx[par_setup.rx_read_index];
    uint16_t next = par_setup.rx_read_index + ONE;
    if (next >= USART1_RX_SIZE) {
        next = ZERO;
    }
    par_setup.rx_read_index = next;
    return ONE;
}

static char impl_read_char(void) {
    par_setup.rx_write_index = _rx_dma_write_snapshot();

    if (par_setup.rx_read_index == par_setup.rx_write_index) {
        return ZERO;
    }

    char tmp = par_setup.buff_rx[par_setup.rx_read_index];
    uint16_t next = par_setup.rx_read_index + 1;

    if (next >= USART1_RX_SIZE) {
        next = ZERO;
    }

    par_setup.rx_read_index = next;
    return tmp;
}

static uint16_t impl_read_str(char* str) {
    uint16_t i = 0;
    if (str) {
        char ch;
        while ((ch = impl_read_char())) {
            str[i] = ch;
            i++;
        }
        str[i] = ZERO;
    }
    return i;
}

static uint16_t impl_read_str_size(char* str, uint16_t max_len) {
    uint16_t i = 0;

    if (!str || max_len == ZERO) {
        return ZERO;
    }

    while (par_setup.rx_read_index != par_setup.rx_write_index && i < (max_len - ONE)) {
        str[i++] = impl_read_char();
    }

    str[i] = ZERO;
    return i;
}

static void impl_send(const uint8_t *data, uint16_t len) {
    if (isPtrNull((void*)data) || len == ZERO || len > USART1_TX_SIZE || par_setup.tx_busy) {
        return;
    }

    par_setup.tx_busy = ONE;
    memcpy(par_setup.buff_tx, data, len);

    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CMAR  = (uint32_t)par_setup.buff_tx;
    dev()->dma->dma1_ch2->CNDTR = len;
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN); /* FIXED: This was commented out!*/
}

static uint8_t impl_tx_ready(void) {
    if (!(dev()->dma->dma1_ch2->CCR & DMA_CCR_EN)) {
        par_setup.tx_busy = ZERO;
    }
    return !par_setup.tx_busy;
}

/* ============================================================================
   MEMORY INSPECTION TRACKING HELPER UTILITIES
   ============================================================================ */
static uint16_t impl_get_rx_left(void) {
	par_setup.rx_left = dev()->dma->dma1_ch1->CNDTR;
    return par_setup.rx_left;
}

static uint16_t impl_get_rx_read_index(void) {
    return par_setup.rx_read_index;
}

static inline uint16_t impl_get_rx_write_index(void) {
	par_setup.rx_write_index = _rx_dma_write_snapshot();
	return par_setup.rx_write_index;
}

static uint16_t impl_rx_available(void) {
    par_setup.rx_write_index = _rx_dma_write_snapshot();

    uint16_t available;

    if (par_setup.rx_write_index >= par_setup.rx_read_index) {
        available = par_setup.rx_write_index - par_setup.rx_read_index;
    } else {
        available = (USART1_RX_SIZE - par_setup.rx_read_index) + par_setup.rx_write_index;
    }

    // Determine the next position the DMA will write to
    uint16_t next_write = par_setup.rx_write_index + 1;
    if (next_write >= USART1_RX_SIZE) {
        next_write = ZERO;
    }

    // If the next hardware write point hits our read index, it's completely full
    if (next_write == par_setup.rx_read_index) {
        par_setup.rx_overflow = ONE;
    }

    return available;
}


/* ============================================================================
   INTERRUPT VECTOR LAYER DRIVER CONNECTIONS
   ============================================================================ */
static void default_idle_irq(void) {
    uint32_t isr = dev()->comm->usart1->ISR;

    if (isr & USART_ISR_ORE) {
        dev()->comm->usart1->ICR = USART_ICR_ORECF;
    }

    if (isr & USART_ISR_IDLE) {
        dev()->comm->usart1->ICR = USART_ICR_IDLECF;
        par_setup.rx_write_index = _rx_dma_write_snapshot();
        par_setup.rx_available = impl_rx_available();
    }
}

static void default_dma_tx_irq(void) {
    // Read the DMA channel 2 status using your framework layout
    uint32_t isr = dev()->dma->dma1->ISR; // double check your framework's name for global ISR

    if (isr & DMA_ISR_TCIF2) {
        // Clear the Channel 2 Transfer Complete flag using your native helper/register
        dev()->dma->dma1->IFCR = DMA_IFCR_CTCIF2;

        par_setup.tx_busy = ZERO; // Release the lock so next transfers can happen
    }
}

/*** USART1 INTERRUPT ***/
void USART1_IRQHandler(void) {
	USART1_irq* req = usart1()->irq;
	//clear_pin( dev()->gpio->f, 2 );
    // Call high level driver singleton entry hook
    if(req->idle) req->idle();
}

void DMA1_CH2_IRQHandler(void) {
	USART1_irq* req = usart1()->irq;
	//set_pin( dev()->gpio->f, 2 );
    // Call DMA TX completion tracker hook
    if(req->dma_tx) req->dma_tx();
}

/*** EOF ***/

/***
	Singleton does not need to pass in by reference.
***/

