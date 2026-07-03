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
	volatile uint16_t rx_left;
    volatile uint16_t rx_read_index;
    volatile uint16_t rx_write_index;
    volatile uint16_t rx_available;
    uint8_t rx_overflow;
    volatile uint8_t  tx_busy;
	uint8_t*  buff_rx;
	uint8_t*  buff_tx;
} USART1_par;

typedef struct {
	/* Hardware Interrupt Entry hooks */
	void (*idle)(void);
	void (*dma_tx)(void);
} USART1_irq;

typedef const struct {
    /* Lifecycle */
	void (*config)(USART1_par par);
    void (*init)(void);
    void (*start_rx)(void);

    /* RX API */
    uint16_t (*read)(uint8_t *out);
    char (*read_char)(void);
    uint16_t (*read_str)(char* str);
    uint16_t (*read_str_size)(char* str, uint16_t max_len);

    /* TX API */
    void (*send)(const uint8_t *data, uint16_t len);
    uint8_t (*tx_ready)(void);

    /* Memory Inspection Helpers */
    uint16_t (*get_rx_left)(void);
    uint16_t (*get_rx_read_index)(void);
    uint16_t (*get_rx_write_index)(void);
    uint16_t (*rx_available)(void);
} USART1_run;

/* =========================================================
   HIGH LEVEL HANDLE (Singleton V-table Interface)
   ========================================================= */
typedef const struct {
	USART1_par* par;
	USART1_irq* irq;
	USART1_run* run;
} USARTG4_Handle;

/* Public Factory Singleton Accessor */
USARTG4_Handle* usart1(void);

void DMA1_CH2_IRQHandler(void);

#endif /* STM32GXXXUSART1_H */

