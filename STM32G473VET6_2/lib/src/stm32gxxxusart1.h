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

typedef struct {
	uint8_t wordlength;
	uint8_t stopbit;
	uint8_t samplingmode;
	uint32_t baudrate;
    volatile uint16_t rx_read_index;
    volatile uint16_t rx_write_index;
    volatile uint8_t  tx_busy;
	uint8_t*  buff_rx;
	uint8_t*  buff_tx;
} USART1_par;

typedef struct {
    /* Lifecycle */
	void (*config)(USART1_par* par, uint8_t wordlength, uint8_t stopbit, uint8_t samplingmode, uint32_t baudrate, uint8_t*  buff_rx, uint8_t*  buff_tx);
    void (*init)(USART1_par* par);
    void (*start_rx)(USART1_par* par);

    /* RX API */
    uint16_t (*available)(USART1_par* par);
    uint16_t (*read)(USART1_par* par, uint8_t *out);

    /* TX API */
    void (*send)(USART1_par* par, const uint8_t *data, uint16_t len);
    uint8_t (*tx_ready)(USART1_par* par);

    /* Memory Inspection Helpers */
    uint16_t (*get_rx_read_index)(USART1_par* par);
    uint16_t (*get_rx_write_index)(USART1_par* par);

    /* Hardware Interrupt Entry hooks */
    void (*idle_irq)(USART1_par* par);
    void (*dma_tx_irq)(USART1_par* par);
} USART1_run;

/* =========================================================
   HIGH LEVEL HANDLE (Singleton V-table Interface)
   ========================================================= */
typedef struct {
	USART1_par par;
	const USART1_run run;
} USARTG4_Handle;

/* Public Factory Singleton Accessor */
USARTG4_Handle* usart1(void);

void DMA1_CH2_IRQHandler(void);

#endif /* STM32GXXXUSART1_H */
