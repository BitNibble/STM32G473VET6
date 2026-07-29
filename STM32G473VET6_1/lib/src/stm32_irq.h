#ifndef STM32_IRQ_H
	#define STM32_IRQ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*-------------------------------------------------------------
    CALLBACK
-------------------------------------------------------------*/

typedef void (*callback_t)(void);

/*-------------------------------------------------------------
    TIM
-------------------------------------------------------------*/

typedef struct
{
    callback_t update;
    callback_t cc1;
    callback_t cc2;
    callback_t cc3;
    callback_t cc4;
    callback_t trigger;
    callback_t commutation;
    callback_t break_event;
    callback_t break2;

} irq_tim_event_t;

typedef struct
{
    irq_tim_event_t *tim1;
    irq_tim_event_t *tim2;
    irq_tim_event_t *tim3;
    irq_tim_event_t *tim4;
    irq_tim_event_t *tim5;
    irq_tim_event_t *tim6;
    irq_tim_event_t *tim7;
    irq_tim_event_t *tim8;
    irq_tim_event_t *tim15;
    irq_tim_event_t *tim16;
    irq_tim_event_t *tim17;
    irq_tim_event_t *tim20;

} irq_tim_t;

/*-------------------------------------------------------------
    USART / UART
-------------------------------------------------------------*/

typedef struct
{
    callback_t rxne;
    callback_t txe;
    callback_t tc;
    callback_t idle;
    callback_t error;

} irq_usart_event_t;

typedef struct
{
    irq_usart_event_t *usart1;
    irq_usart_event_t *usart2;
    irq_usart_event_t *usart3;
    irq_usart_event_t *uart4;
    irq_usart_event_t *uart5;

} irq_uart_t;

/*-------------------------------------------------------------
    I2C
-------------------------------------------------------------*/

typedef struct
{
    callback_t txis;
    callback_t rxne;
    callback_t stop;
    callback_t nack;
    callback_t tc;
    callback_t error;

} irq_i2c_event_t;

typedef struct
{
    irq_i2c_event_t *i2c1;
    irq_i2c_event_t *i2c2;
    irq_i2c_event_t *i2c3;
    irq_i2c_event_t *i2c4;

} irq_i2c_t;

/*-------------------------------------------------------------
    SPI
-------------------------------------------------------------*/

typedef struct
{
    callback_t txe;
    callback_t rxne;
    callback_t eot;
    callback_t error;

} irq_spi_event_t;

typedef struct
{
    irq_spi_event_t *spi1;
    irq_spi_event_t *spi2;
    irq_spi_event_t *spi3;
    irq_spi_event_t *spi4;

} irq_spi_t;

/*-------------------------------------------------------------
    DMA
-------------------------------------------------------------*/

typedef struct
{
    callback_t complete;
    callback_t half;
    callback_t error;

} irq_dma_channel_t;

typedef struct
{
    irq_dma_channel_t *ch1;
    irq_dma_channel_t *ch2;
    irq_dma_channel_t *ch3;
    irq_dma_channel_t *ch4;
    irq_dma_channel_t *ch5;
    irq_dma_channel_t *ch6;
    irq_dma_channel_t *ch7;

} irq_dma_controller_t;

typedef struct
{
    irq_dma_controller_t *dma1;
    irq_dma_controller_t *dma2;

} irq_dma_t;

/*-------------------------------------------------------------
    ADC
-------------------------------------------------------------*/

typedef struct
{
    callback_t eoc;
    callback_t eos;
    callback_t awd;
    callback_t overrun;

} irq_adc_event_t;

typedef struct
{
    irq_adc_event_t *adc1;
    irq_adc_event_t *adc2;
    irq_adc_event_t *adc3;
    irq_adc_event_t *adc4;
    irq_adc_event_t *adc5;

} irq_adc_t;

/*-------------------------------------------------------------
    EXTI
-------------------------------------------------------------*/

typedef struct
{
    callback_t line0;
    callback_t line1;
    callback_t line2;
    callback_t line3;
    callback_t line4;
    callback_t line5_9;
    callback_t line10_15;

} irq_exti_t;

/*-------------------------------------------------------------
    ROOT
-------------------------------------------------------------*/

typedef struct
{
    irq_tim_t  *tim;
    irq_uart_t *uart;
    irq_i2c_t  *i2c;
    irq_spi_t  *spi;
    irq_dma_t  *dma;
    irq_adc_t  *adc;
    irq_exti_t *exti;

} irq_t;

irq_t *irq(void);

#ifdef __cplusplus
}
#endif

#endif
