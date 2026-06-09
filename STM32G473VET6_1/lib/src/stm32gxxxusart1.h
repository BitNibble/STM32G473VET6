/******************************************************************************
    STM32GXXXUSART1.H
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473
Date:     08/06/2026
*******************************************************************************/
#ifndef STM32GXXXUSART1_H
#define STM32GXXXUSART1_H

#include "stm32g473vet6.h"

#define USART1_RX_SIZE 512
#define USART1_TX_SIZE 256

/* =========================================================
   HIGH LEVEL HANDLE (Singleton V-table Interface)
   ========================================================= */
typedef struct {
    /* Lifecycle */
    void (*init)(uint32_t baud);
    void (*start_rx)(void);

    /* RX API */
    uint16_t (*available)(void);
    uint16_t (*read)(uint8_t *out);

    /* TX API */
    void (*send)(const uint8_t *data, uint16_t len);
    uint8_t (*tx_ready)(void);

    /* Memory Inspection Helpers */
    const uint8_t* (*get_rx_buffer_ptr)(void);
    uint16_t (*get_rx_read_index)(void);
    uint16_t (*get_rx_write_index)(void);

    /* Hardware Interrupt Entry hooks */
    void (*idle_irq)(void);
    void (*dma_tx_irq)(void);
} USARTG4_Handle;

/* Public Factory Singleton Accessor */
const USARTG4_Handle* usart1(void);

#endif /* STM32GXXXUSART1_H */
