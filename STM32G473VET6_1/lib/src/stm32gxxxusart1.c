/******************************************************************************
    STM32GXXXUSART1.C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473
Date:     08/06/2026
*******************************************************************************/
#include "stm32gxxxusart1.h"
#include <stdio.h>
#include <string.h>

#define USART1_RX_COUNT (USART1_RX_SIZE - ONE)
#define USART1_TX_COUNT (USART1_TX_SIZE - ONE)
/* Static private memory allocation buffers hidden from application workspace */
static uint8_t u1_rx_raw[USART1_RX_SIZE + ONE] = {0}; // overflow safety
static uint8_t u1_tx_raw[USART1_TX_SIZE] = {0};

static void impl_config(uint8_t wordlength, uint8_t stopbit, uint8_t samplingmode, uint32_t baudrate, uint8_t* buff_rx, uint8_t* buff_tx);
static void impl_init(void);
static void impl_start_rx(void);
static uint16_t impl_read(uint8_t *out);
static char impl_read_char(void);
static uint16_t impl_read_str(char* str);
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

USART1_par par = {
	.wordlength     = 8,
	.stopbit        = 1,
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
USART1_irq	irq = {
	.idle    = default_idle_irq,
	.dma_tx = default_dma_tx_irq,
};
USART1_run run = {
	.config             = impl_config,
	.init               = impl_init,
	.start_rx           = impl_start_rx,
	.read               = impl_read,
	.read_char          = impl_read_char,
	.read_str           = impl_read_str,
	.send               = impl_send,
	.tx_ready           = impl_tx_ready,
	.get_rx_left        = impl_get_rx_left,
	.get_rx_read_index  = impl_get_rx_read_index,
	.get_rx_write_index = impl_get_rx_write_index,
	.rx_available       = impl_rx_available
};

/* V-Table initialization mapping back to public struct blueprint */
static USARTG4_Handle handle_instance = {
		.par = &par,
		.irq = &irq,
		.run = &run
};

/* Singleton factory gateway entry point */
const USARTG4_Handle* usart1(void) {
    return &handle_instance;
}

/* ============================================================================
   DRIVER CODE IMPLEMENTATIONS
   ============================================================================ */
static inline uint16_t _rx_dma_write_snapshot(void) {
    return USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;
}

static void impl_config(uint8_t wordlength, uint8_t stopbit, uint8_t samplingmode, uint32_t baudrate, uint8_t* buff_rx, uint8_t* buff_tx) {
    par.wordlength   = wordlength;
    par.stopbit      = stopbit;
    par.samplingmode = samplingmode;
    par.baudrate     = baudrate;
    if (!isPtrNull(buff_rx)) par.buff_rx = buff_rx;
    if (!isPtrNull(buff_tx)) par.buff_tx = buff_tx;
}

static void impl_init(void) {
    // 1. Gating Clocks via Native GPIO and Clock System tree APIs
    GPIO_clock(dev()->gpio->a, ONE);
    set_reg(&(dev()->sys->rcc->AHB1ENR), RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN);
    set_reg(&(dev()->sys->rcc->APB2ENR), RCC_APB2ENR_USART1EN);

    // 2. Configure Alternate Pin Functions using your tool functions (AF7 for USART1)
    GPIO_moder(GPIOA, 9,  MODE_AF);  // PA9  -> TX Line
    GPIO_moder(GPIOA, 10, MODE_AF);  // PA10 -> RX Line
    GPIO_af(GPIOA, 9,  7);
    GPIO_af(GPIOA, 10, 7);

    GPIO_ospeed(GPIOA, 9,  3);
    GPIO_ospeed(GPIOA, 10, 3);

    GPIO_otype(GPIOA, 9,  0);
    GPIO_otype(GPIOA, 10, 0);

    GPIO_pupd(GPIOA, 9,  0);
    GPIO_pupd(GPIOA, 10, 1);

    // 3. Routing Peripheral Signals into DMAMUX Matrices (Ch1=RX, Ch2=TX)
    write_field_value(&(dev()->dma->dmamux1_ch1->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 24);
    write_field_value(&(dev()->dma->dmamux1_ch2->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 25);

    // 4. Configure DMA RX Channel (Circular mode)
    clear_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch1->CPAR  = (uint32_t)&(dev()->comm->usart1->RDR);
    dev()->dma->dma1_ch1->CMAR  = (uint32_t)par.buff_rx;
    dev()->dma->dma1_ch1->CNDTR = USART1_RX_SIZE;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_PL_0);

    // 5. Configure DMA TX Channel (Normal Single-Shot mode)
    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CPAR  = (uint32_t)&(dev()->comm->usart1->TDR);
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE);
    //set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_MINC | DMA_CCR_DIR);

    // 6. Set USART registers using dynamic system clock reading helper
    clear_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    uint32_t brr_calculated_val = get_pclk2() / par.baudrate;
    write_field_value(&(dev()->comm->usart1->BRR), USART_BRR_BRR_Msk, USART_BRR_BRR_Pos, brr_calculated_val);


    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_TE | USART_CR1_RE | USART_CR1_IDLEIE);
    set_reg(&(dev()->comm->usart1->CR3), USART_CR3_DMAT | USART_CR3_DMAR);
    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    // 7. Core NVIC Interrupt Vectors Configurations
    NVIC_SetPriority(USART1_IRQn, 5);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(DMA1_Channel2_IRQn, 5);
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

static void impl_start_rx(void) {
    par.rx_read_index  = ZERO;
    par.rx_write_index = ZERO;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
}

static uint16_t impl_read(uint8_t *out) {
    if (isPtrNull(out)) return ZERO;

    par.rx_write_index = _rx_dma_write_snapshot();

    if (par.rx_read_index == par.rx_write_index) {
        return ZERO;
    }

    *out = par.buff_rx[par.rx_read_index];
    uint16_t next = par.rx_read_index + ONE;
    if (next >= USART1_RX_SIZE) {
        next = ZERO;
    }
    par.rx_read_index = next;
    return ONE;
}

static char impl_read_char(void) {
    char tmp;
    par.rx_write_index = _rx_dma_write_snapshot();

    if (par.rx_read_index == par.rx_write_index) {
        return ZERO;
    }

    tmp = par.buff_rx[par.rx_read_index];
    uint16_t next = par.rx_read_index + ONE;
    if (next >= USART1_RX_SIZE) {
        next = ZERO;
    }
    par.rx_read_index = next;
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

static void impl_send(const uint8_t *data, uint16_t len) {
    if (isPtrNull((void*)data) || len == ZERO || len > USART1_TX_SIZE || par.tx_busy) {
        return;
    }

    par.tx_busy = ONE;
    memcpy(par.buff_tx, data, len);

    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CMAR  = (uint32_t)par.buff_tx;
    dev()->dma->dma1_ch2->CNDTR = len;
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN); /* FIXED: This was commented out!*/
}

static uint8_t impl_tx_ready(void) {
    if (!(dev()->dma->dma1_ch2->CCR & DMA_CCR_EN)) {
        par.tx_busy = 0;
    }
    return !par.tx_busy;
}

/* ============================================================================
   MEMORY INSPECTION TRACKING HELPER UTILITIES
   ============================================================================ */
static uint16_t impl_get_rx_left(void) {
	par.rx_left = dev()->dma->dma1_ch1->CNDTR;
    return par.rx_left;
}

static uint16_t impl_get_rx_read_index(void) {
    return par.rx_read_index;
}

static inline uint16_t impl_get_rx_write_index(void) {
	par.rx_write_index = _rx_dma_write_snapshot();
	return par.rx_write_index;
}

static uint16_t impl_rx_available(void) {
    par.rx_write_index = _rx_dma_write_snapshot();

    uint16_t available;

    if (par.rx_write_index >= par.rx_read_index) {
        available = par.rx_write_index - par.rx_read_index;
    } else {
        available = (USART1_RX_SIZE - par.rx_read_index) + par.rx_write_index;
    }

    if (available == USART1_RX_COUNT) {
        par.rx_overflow = 1;
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
        par.rx_write_index = _rx_dma_write_snapshot();
        par.rx_available = impl_rx_available();
    }
}

static void default_dma_tx_irq(void) {
    // Read the DMA channel 2 status using your framework layout
    uint32_t isr = dev()->dma->dma1->ISR; // double check your framework's name for global ISR

    if (isr & DMA_ISR_TCIF2) {
        // Clear the Channel 2 Transfer Complete flag using your native helper/register
        dev()->dma->dma1->IFCR = DMA_IFCR_CTCIF2;

        par.tx_busy = ZERO; // Release the lock so next transfers can happen
    }
}

/*** INTERRUPT ***/
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

