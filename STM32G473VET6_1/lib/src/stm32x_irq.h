/******************************************************************************
	stm32x_irq.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*******************************************************************************/
#ifndef STM32X_IRQ_H
	#define STM32X_IRQ_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

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
    callback_t rxne;       // RX not empty
    callback_t txe;        // TX empty
    callback_t tc;         // Transmission complete
    callback_t idle;       // Idle line detected

    callback_t ore;        // Overrun error
    callback_t ne;         // Noise error
    callback_t fe;         // Framing error
    callback_t pe;         // Parity error

    callback_t cts;        // CTS change
    callback_t wakeup;     // Wakeup from stop mode

    callback_t rtof;
    callback_t eob;
    callback_t cmf;
    callback_t wuf;
    callback_t txfe;
    callback_t rxff;
    callback_t parity_error;
    callback_t framing_error;
    callback_t noise_error;
    callback_t overrun_error;
    callback_t receiver_timeout;
    callback_t end_of_block;
    callback_t wake_up;
    callback_t character_match;

} irq_usart_event_t;

typedef struct
{
    irq_usart_event_t *usart1;
    irq_usart_event_t *usart2;
    irq_usart_event_t *usart3;
    irq_usart_event_t *uart4;
    irq_usart_event_t *uart5;
    irq_usart_event_t *lpuart1;

} irq_uart_t;

/*-------------------------------------------------------------
    I2C
-------------------------------------------------------------*/

typedef struct
{
    callback_t rxne;
    callback_t txis;

    callback_t addr;
    callback_t nack;
    callback_t stop;

    callback_t tc;
    callback_t tcr;

    callback_t berr;
    callback_t arlo;
    callback_t ovr;

    callback_t pecerr;
    callback_t timeout;
    callback_t alert;

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
    callback_t rxne;
    callback_t txe;

    callback_t ovr;
    callback_t modf;
    callback_t crcerr;
    callback_t fre;

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
    callback_t tc;     /* Transfer Complete */
    callback_t ht;     /* Half Transfer */
    callback_t te;     /* Transfer Error */
    callback_t gif;    /* Global Interrupt */

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
    callback_t eoc;       /* End Of Conversion */
    callback_t eos;       /* End Of Sequence */
    callback_t awd;       /* Analog Watchdog */
    callback_t overrun;   /* Data Overrun */

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
    RTC
-------------------------------------------------------------*/

typedef struct {
	callback_t Alarm;
	callback_t WakeUp;
	callback_t TimeStamp;
	callback_t Tamper;
	callback_t Overrun;

} irq_rtc_t;

/*-------------------------------------------------------------
    ROOT
-------------------------------------------------------------*/

typedef struct
{
    irq_tim_t  *timer;
    irq_uart_t *uart;
    irq_i2c_t  *i2c;
    irq_spi_t  *spi;
    irq_dma_t  *dma;
    irq_adc_t  *adc;
    irq_exti_t *exti;
    irq_rtc_t *rtc;

} irq_t;

irq_t *irq(void);

#ifdef __cplusplus
}
#endif

#endif

/*** EOF ***/

