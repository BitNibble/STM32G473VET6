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

/*** USART1 PARAMETER ***/
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

/*** USART1 GET ***/
typedef const struct {
	uint8_t (*wordlength)(void);
	uint8_t (*stopbit)(void);
	uint8_t (*samplingmode)(void);
	uint32_t (*baudrate)(void);
} USART1_get;

/*** USART1 SET ***/
typedef const struct {
	void (*wordlength)(uint8_t value);
	void (*stopbit)(uint8_t value);
	void (*samplingmode)(uint8_t value);
	void (*baudrate)(uint32_t value);
} USART1_set;

/*** USART1 CALLBACK ***/
typedef struct {
	/* Hardware Interrupt Entry hooks */
	void (*idle)(void);
	void (*dma_tx)(void);
} USART1_irq;

/*** USART1 V-TABLE ***/
typedef const struct {
    /* Lifecycle */
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

/*** USART1 HANDLER ***/
typedef const struct {
	USART1_par* par;
	USART1_get* get;
	USART1_set* set;
	USART1_irq* irq;
	USART1_run* run;
} USARTG4_Handle;

/*** USART1 ACCESSOR FUNCTION ***/
USARTG4_Handle* usart1(void);

void DMA1_CH2_IRQHandler(void);

#endif /* STM32GXXXUSART1_H */

