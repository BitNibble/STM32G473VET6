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

/* Static private memory allocation buffers hidden from application workspace */
static uint8_t u1_rx_raw[USART1_RX_SIZE];
static uint8_t u1_tx_raw[USART1_TX_SIZE];

/* Static internal Singleton context tracking structures */
typedef struct {
    volatile uint16_t rx_read;
    volatile uint16_t rx_write;
    volatile uint8_t  tx_busy;
} USART1_Private_Ctx;

static USART1_Private_Ctx u1_singleton = {
    .rx_read  = ZERO,
    .rx_write = ZERO,
    .tx_busy  = ZERO
};

/* Forward Declaration of V-Table Implementations */
static void           impl_init(uint32_t baud);
static void           impl_start_rx(void);
static uint16_t       impl_available(void);
static uint16_t       impl_read(uint8_t *out);
static void           impl_send(const uint8_t *data, uint16_t len);
static uint8_t        impl_tx_ready(void);
static const uint8_t* impl_get_rx_buffer_ptr(void);
static uint16_t       impl_get_rx_read_index(void);
static uint16_t       impl_get_rx_write_index(void);
static void           impl_idle_irq(void);
static void           impl_dma_tx_irq(void);

/* V-Table initialization mapping back to public struct blueprint */
static const USARTG4_Handle handle_instance = {
    .init               = impl_init,
    .start_rx           = impl_start_rx,
    .available          = impl_available,
    .read               = impl_read,
    .send               = impl_send,
    .tx_ready           = impl_tx_ready,
    .get_rx_buffer_ptr  = impl_get_rx_buffer_ptr,
    .get_rx_read_index  = impl_get_rx_read_index,
    .get_rx_write_index = impl_get_rx_write_index,
    .idle_irq           = impl_idle_irq,
    .dma_tx_irq         = impl_dma_tx_irq
};

/* Singleton factory gateway entry point */
const USARTG4_Handle* usart1(void) {
    return &handle_instance;
}

/* ============================================================================
   DRIVER CODE IMPLEMENTATIONS WITH YOUR BACKBONE
   ============================================================================ */

static void impl_init(uint32_t baud) {
    // 1. Gating Clocks via your Native GPIO and Clock System tree APIs
    GPIO_clock(dev()->gpio->a, ONE);
    set_reg(&(dev()->system->rcc->AHB1ENR), RCC_AHB1ENR_DMA1EN | RCC_AHB1ENR_DMAMUX1EN);
    set_reg(&(dev()->system->rcc->APB2ENR), RCC_APB2ENR_USART1EN);

    // 2. Configure Alternate Pin Functions using your tool functions (AF7 for USART1)
    GPIO_moder(dev()->gpio->a, 9,  MODE_AF);  // PA9  -> TX Line
    GPIO_moder(dev()->gpio->a, 10, MODE_AF);  // PA10 -> RX Line
    GPIO_af(dev()->gpio->a, 9,  7);
    GPIO_af(dev()->gpio->a, 10, 7);

    // 3. Routing Peripheral Signals into DMAMUX Matrices via your mapped device tree channel structures
    write_reg_field_value(&(dev()->dma->dmamux1_ch1->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 24);
    write_reg_field_value(&(dev()->dma->dmamux1_ch2->CCR), DMAMUX_CxCR_DMAREQ_ID_Msk, DMAMUX_CxCR_DMAREQ_ID_Pos, 25);

    // 4. Configure DMA RX Channel (Circular mode, memory auto-incrementing pointer blocks)
    clear_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch1->CPAR  = (uint32_t)&(dev()->comm->usart1->RDR);
    dev()->dma->dma1_ch1->CMAR  = (uint32_t)u1_rx_raw;
    dev()->dma->dma1_ch1->CNDTR = USART1_RX_SIZE;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_PL_0);

    // 5. Configure DMA TX Channel (Normal Single-Shot mode, memory increment, TCIE active)
    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CPAR  = (uint32_t)&(dev()->comm->usart1->TDR);
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE);

    // 6. Set USART registers using your dynamic system clock reading helper
    clear_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    uint32_t brr_calculated_val = get_sysclk() / baud;
    write_reg_field_value(&(dev()->comm->usart1->BRR), USART_BRR_BRR_Msk, USART_BRR_BRR_Pos, brr_calculated_val);

    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_TE | USART_CR1_RE | USART_CR1_IDLEIE);
    set_reg(&(dev()->comm->usart1->CR3), USART_CR3_DMAT | USART_CR3_DMAR);
    set_reg(&(dev()->comm->usart1->CR1), USART_CR1_UE);

    // 7. Core NVIC Interrupt Vectors Configurations via your layout handles
    NVIC_SetPriority(USART1_IRQn, 5);
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(DMA1_Channel2_IRQn, 5);
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

static void impl_start_rx(void) {
    u1_singleton.rx_read  = ZERO;
    u1_singleton.rx_write = ZERO;
    set_reg(&(dev()->dma->dma1_ch1->CCR), DMA_CCR_EN);
}

static uint16_t impl_available(void) {
    u1_singleton.rx_write = USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;

    if (u1_singleton.rx_write >= u1_singleton.rx_read) {
        return (u1_singleton.rx_write - u1_singleton.rx_read);
    } else {
        return (USART1_RX_SIZE - u1_singleton.rx_read) + u1_singleton.rx_write;
    }
}

static uint16_t impl_read(uint8_t *out) {
    if (isPtrNull(out)) return ZERO;

    u1_singleton.rx_write = USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;

    if (u1_singleton.rx_read == u1_singleton.rx_write) {
        return ZERO;
    }

    *out = u1_rx_raw[u1_singleton.rx_read];
    uint16_t next = u1_singleton.rx_read + ONE;
    if (next >= USART1_RX_SIZE) {
        next = ZERO;
    }
    u1_singleton.rx_read = next;
    return ONE;
}

static void impl_send(const uint8_t *data, uint16_t len) {
    if (isPtrNull((void*)data) || len == ZERO || len > USART1_TX_SIZE || u1_singleton.tx_busy) {
        return;
    }

    u1_singleton.tx_busy = ONE;
    memcpy(u1_tx_raw, data, len);

    clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
    dev()->dma->dma1_ch2->CMAR  = (uint32_t)u1_tx_raw;
    dev()->dma->dma1_ch2->CNDTR = len;
    set_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
}

static uint8_t impl_tx_ready(void) {
    return !u1_singleton.tx_busy;
}

/* ============================================================================
   MEMORY INSPECTION TRACKING HELPER UTILITIES
   ============================================================================ */

static const uint8_t* impl_get_rx_buffer_ptr(void) {
    return u1_rx_raw; // Exposes base structural memory zone address safely as read-only pointer
}

static uint16_t impl_get_rx_read_index(void) {
    return u1_singleton.rx_read; // Current consumer application reading offset position
}

static uint16_t impl_get_rx_write_index(void) {
    // Read the real-time hardware status downcounter to return an absolute snapshot index
    u1_singleton.rx_write = USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;
    return u1_singleton.rx_write;
}

/* ============================================================================
   INTERRUPT VECTOR LAYER DRIVER CONNECTIONS
   ============================================================================ */

static void impl_idle_irq(void) {
    if (dev()->comm->usart1->ISR & USART_ISR_IDLE) {
        dev()->comm->usart1->ICR = USART_ICR_IDLECF;
        u1_singleton.rx_write = USART1_RX_SIZE - dev()->dma->dma1_ch1->CNDTR;
    }
}

static void impl_dma_tx_irq(void) {
    if (DMA1->ISR & DMA_ISR_TCIF2) {
        DMA1->IFCR = DMA_IFCR_CTCIF2;
        clear_reg(&(dev()->dma->dma1_ch2->CCR), DMA_CCR_EN);
        u1_singleton.tx_busy = ZERO;
    }
}

