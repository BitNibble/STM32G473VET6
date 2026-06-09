/******************************************************************************
	STM32XXXUSART1.C
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     08062026
*******************************************************************************/
#include "stm32g473vet6.h"
#include <string.h>
#include <stdint.h>

/* =========================================================
   INTERNAL HELPERS
   ========================================================= */

static inline uint16_t rx_write_pos(USARTG4_DMA *d)
{
    return d->rx_size - d->rx_dma->CNDTR;
}

/* =========================================================
   CORE FUNCTIONS
   ========================================================= */

static void init(USARTG4_DMA *d)
{
    d->rx_read  = 0;
    d->rx_write = 0;
    d->tx_busy  = 0;

    /* enable clocks assumed external */

    /* ---------------- DMAMUX ---------------- */
    DMAMUX1_Channel0->CCR = d->dmamux_rx;
    DMAMUX1_Channel1->CCR = d->dmamux_tx;

    /* ---------------- USART ---------------- */
    d->uart->CR3 |= USART_CR3_DMAR | USART_CR3_DMAT;
    d->uart->CR1 |= USART_CR1_IDLEIE;
    d->uart->CR1 |= USART_CR1_UE;
}

/* =========================================================
   RX START (circular DMA)
   ========================================================= */

static void start_rx(USARTG4_DMA *d)
{
    d->rx_dma->CCR &= ~DMA_CCR_EN;

    d->rx_dma->CPAR  = (uint32_t)&d->uart->RDR;
    d->rx_dma->CMAR  = (uint32_t)d->rx_buf;
    d->rx_dma->CNDTR = d->rx_size;

    d->rx_dma->CCR =
        DMA_CCR_MINC |
        DMA_CCR_CIRC;

    d->rx_dma->CCR |= DMA_CCR_EN;
}

/* =========================================================
   RX AVAILABLE
   ========================================================= */

static uint16_t available(USARTG4_DMA *d)
{
    d->rx_write = rx_write_pos(d);

    if (d->rx_write >= d->rx_read)
        return d->rx_write - d->rx_read;

    return (d->rx_size - d->rx_read + d->rx_write);
}

/* =========================================================
   RX READ
   ========================================================= */

static uint16_t read(USARTG4_DMA *d, uint8_t *out)
{
    if (d->rx_read == d->rx_write)
        return 0;

    *out = d->rx_buf[d->rx_read++];

    if (d->rx_read >= d->rx_size)
        d->rx_read = 0;

    return 1;
}

/* =========================================================
   TX SEND (DMA block)
   ========================================================= */

static void send(USARTG4_DMA *d, uint8_t *data, uint16_t len)
{
    if (d->tx_busy || len == 0)
        return;

    d->tx_busy = 1;

    d->tx_dma->CCR &= ~DMA_CCR_EN;

    memcpy(d->tx_buf, data, len);

    DMAMUX1_Channel1->CCR = d->dmamux_tx;

    d->tx_dma->CPAR  = (uint32_t)&d->uart->TDR;
    d->tx_dma->CMAR  = (uint32_t)d->tx_buf;
    d->tx_dma->CNDTR = len;

    d->tx_dma->CCR =
        DMA_CCR_MINC;

    d->tx_dma->CCR |= DMA_CCR_EN;
}

/* =========================================================
   TX READY
   ========================================================= */

static uint8_t tx_ready(USARTG4_DMA *d)
{
    return !d->tx_busy;
}

/* =========================================================
   IDLE IRQ
   ========================================================= */

static void idle_irq(USARTG4_DMA *d)
{
    volatile uint32_t tmp;

    tmp = d->uart->ISR;
    tmp = d->uart->RDR;

    (void)tmp;

    d->rx_write = rx_write_pos(d);
}

/* =========================================================
   DMA TX IRQ
   ========================================================= */

static void dma_tx_irq(USARTG4_DMA *d)
{
    d->tx_busy = 0;
}

/* =========================================================
   CONSTRUCTOR (THIS WAS MISSING BEFORE)
   ========================================================= */

USARTG4_Handle usart_g4_dma_enable(USARTG4_DMA *d)
{
    USARTG4_Handle h;

    h.d = d;

    h.init       = init;
    h.start_rx   = start_rx;

    h.available  = available;
    h.read       = read;

    h.send       = send;
    h.tx_ready   = tx_ready;

    h.idle_irq   = idle_irq;
    h.dma_tx_irq = dma_tx_irq;

    return h;
}

void USART1_IRQHandler(void)
{
    if (usart_g4.d->uart->ISR & USART_ISR_IDLE)
    {
        usart_g4.idle_irq(usart_g4.d);
    }

    if (usart_g4.d->uart->ISR & USART_ISR_ORE)
    {
        usart_g4.d->uart->ICR = USART_ICR_ORECF;
    }
}

void DMA1_Channel1_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF1;
        usart_g4.dma_rx_irq(usart_g4.d);
    }
}

void DMA1_Channel2_IRQHandler(void)
{
    if (DMA1->ISR & DMA_ISR_TCIF2)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF2;
        usart_g4.dma_tx_irq(usart_g4.d);
    }
}

