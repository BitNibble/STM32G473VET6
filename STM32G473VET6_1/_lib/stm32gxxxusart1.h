/******************************************************************************
	STM32GXXXUSART1.H
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     08062026
*******************************************************************************/
#ifndef STM32GXXXUSART1_H
	#define STM32GXXXUSART1_H

#include "stm32g473vet6.h"

#define USART1_RX_SIZE 512
#define USART1_TX_SIZE 256

/* =========================================================
   LOW LEVEL DMA CONTEXT
   ========================================================= */

typedef struct {

    USART_TypeDef *uart;

    DMA_Channel_TypeDef *rx_dma;
    DMA_Channel_TypeDef *tx_dma;

    /* DMAMUX request IDs (critical on G4) */
    uint32_t dmamux_rx;
    uint32_t dmamux_tx;

    /* Buffers */
    uint8_t *rx_buf;
    uint16_t rx_size;

    uint8_t *tx_buf;
    uint16_t tx_size;

    /* Ring buffer state */
    volatile uint16_t rx_read;
    volatile uint16_t rx_write;

    /* TX state */
    volatile uint8_t tx_busy;

} USARTG4_DMA;

/* =========================================================
   HIGH LEVEL HANDLE (your V-table style)
   ========================================================= */

typedef struct {

    USARTG4_DMA *d;

    /* lifecycle */
    void (*init)(USARTG4_DMA *d);
    void (*start_rx)(USARTG4_DMA *d);

    /* RX API */
    uint16_t (*available)(USARTG4_DMA *d);
    uint16_t (*read)(USARTG4_DMA *d, uint8_t *out);

    /* TX API */
    void (*send)(USARTG4_DMA *d, uint8_t *data, uint16_t len);
    uint8_t (*tx_ready)(USARTG4_DMA *d);

    /* interrupts */
    void (*idle_irq)(USARTG4_DMA *d);
    void (*dma_tx_irq)(USARTG4_DMA *d);

} USARTG4_Handle;

/* factory */
USARTG4_Handle usart_g4_dma_enable(USARTG4_DMA *d);

#endif
