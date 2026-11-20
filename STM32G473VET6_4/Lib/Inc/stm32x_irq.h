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

/******************************************************************************
* TIM1
******************************************************************************/
__attribute__((weak)) void tim1_u_callback(void);
__attribute__((weak)) void tim1_cc1_callback(void);
__attribute__((weak)) void tim1_cc2_callback(void);
__attribute__((weak)) void tim1_cc3_callback(void);
__attribute__((weak)) void tim1_cc4_callback(void);
__attribute__((weak)) void tim1_trg_callback(void);
__attribute__((weak)) void tim1_brk_callback(void);
__attribute__((weak)) void tim1_brk2_callback(void);
__attribute__((weak)) void tim1_com_callback(void);

/******************************************************************************
* TIM8
******************************************************************************/
__attribute__((weak)) void tim8_u_callback(void);
__attribute__((weak)) void tim8_cc1_callback(void);
__attribute__((weak)) void tim8_cc2_callback(void);
__attribute__((weak)) void tim8_cc3_callback(void);
__attribute__((weak)) void tim8_cc4_callback(void);
__attribute__((weak)) void tim8_trg_callback(void);
__attribute__((weak)) void tim8_brk_callback(void);
__attribute__((weak)) void tim8_com_callback(void);
__attribute__((weak)) void tim8_rep_callback(void);
__attribute__((weak)) void tim8_dma_callback(void);

/******************************************************************************
* TIM2–TIM5 (general purpose, full CC capable)
******************************************************************************/
__attribute__((weak)) void tim2_u_callback(void);
__attribute__((weak)) void tim2_cc1_callback(void);
__attribute__((weak)) void tim2_cc2_callback(void);
__attribute__((weak)) void tim2_cc3_callback(void);
__attribute__((weak)) void tim2_cc4_callback(void);

__attribute__((weak)) void tim3_u_callback(void);
__attribute__((weak)) void tim3_cc1_callback(void);
__attribute__((weak)) void tim3_cc2_callback(void);
__attribute__((weak)) void tim3_cc3_callback(void);
__attribute__((weak)) void tim3_cc4_callback(void);

__attribute__((weak)) void tim4_u_callback(void);
__attribute__((weak)) void tim4_cc1_callback(void);
__attribute__((weak)) void tim4_cc2_callback(void);
__attribute__((weak)) void tim4_cc3_callback(void);
__attribute__((weak)) void tim4_cc4_callback(void);

__attribute__((weak)) void tim5_u_callback(void);
__attribute__((weak)) void tim5_cc1_callback(void);
__attribute__((weak)) void tim5_cc2_callback(void);
__attribute__((weak)) void tim5_cc3_callback(void);
__attribute__((weak)) void tim5_cc4_callback(void);

/******************************************************************************
* TIM6–TIM7 (basic timers)
******************************************************************************/
__attribute__((weak)) void tim6_u_callback(void);
__attribute__((weak)) void tim7_u_callback(void);

/******************************************************************************
* TIM15–TIM17 (low power timers)
******************************************************************************/
__attribute__((weak)) void tim15_u_callback(void);
__attribute__((weak)) void tim15_cc1_callback(void);
__attribute__((weak)) void tim15_cc2_callback(void);
__attribute__((weak)) void tim15_trg_callback(void);
__attribute__((weak)) void tim15_com_callback(void);
__attribute__((weak)) void tim15_brk_callback(void);

__attribute__((weak)) void tim16_u_callback(void);
__attribute__((weak)) void tim16_cc1_callback(void);
__attribute__((weak)) void tim16_brk_callback(void);

__attribute__((weak)) void tim17_u_callback(void);
__attribute__((weak)) void tim17_cc1_callback(void);
__attribute__((weak)) void tim17_brk_callback(void);

/******************************************************************************
*TIM20 (advanced / high resolution)
******************************************************************************/
__attribute__((weak)) void tim20_u_callback(void);
__attribute__((weak)) void tim20_cc1_callback(void);
__attribute__((weak)) void tim20_cc2_callback(void);
__attribute__((weak)) void tim20_cc3_callback(void);
__attribute__((weak)) void tim20_cc4_callback(void);
__attribute__((weak)) void tim20_trg_callback(void);
__attribute__((weak)) void tim20_brk_callback(void);
__attribute__((weak)) void tim20_brk2_callback(void);
__attribute__((weak)) void tim20_com_callback(void);

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
    callback_t rtof;       // receiver timeout;
    callback_t eob;        // end of block
    callback_t cmf;        // character match
    callback_t wuf;        // wake up
    callback_t txfe;
    callback_t rxff;

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

/******************************************************************************
 * USART1
 ******************************************************************************/
void usart1_pe_callback(void)    __attribute__((weak));
void usart1_fe_callback(void)    __attribute__((weak));
void usart1_ne_callback(void)    __attribute__((weak));
void usart1_ore_callback(void)   __attribute__((weak));

void usart1_idle_callback(void)  __attribute__((weak));
void usart1_rxne_callback(void)  __attribute__((weak));
void usart1_txe_callback(void)   __attribute__((weak));
void usart1_tc_callback(void)    __attribute__((weak));

void usart1_cts_callback(void)   __attribute__((weak));
void usart1_rtof_callback(void)  __attribute__((weak));
void usart1_eob_callback(void)   __attribute__((weak));
void usart1_cmf_callback(void)   __attribute__((weak));
void usart1_wuf_callback(void)   __attribute__((weak));

void usart1_txfe_callback(void)  __attribute__((weak));
void usart1_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * USART2
 ******************************************************************************/
void usart2_pe_callback(void)    __attribute__((weak));
void usart2_fe_callback(void)    __attribute__((weak));
void usart2_ne_callback(void)    __attribute__((weak));
void usart2_ore_callback(void)   __attribute__((weak));

void usart2_idle_callback(void)  __attribute__((weak));
void usart2_rxne_callback(void)  __attribute__((weak));
void usart2_txe_callback(void)   __attribute__((weak));
void usart2_tc_callback(void)    __attribute__((weak));

void usart2_cts_callback(void)   __attribute__((weak));
void usart2_rtof_callback(void)  __attribute__((weak));
void usart2_eob_callback(void)   __attribute__((weak));
void usart2_cmf_callback(void)   __attribute__((weak));
void usart2_wuf_callback(void)   __attribute__((weak));

void usart2_txfe_callback(void)  __attribute__((weak));
void usart2_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * USART3
 ******************************************************************************/
void usart3_pe_callback(void)    __attribute__((weak));
void usart3_fe_callback(void)    __attribute__((weak));
void usart3_ne_callback(void)    __attribute__((weak));
void usart3_ore_callback(void)   __attribute__((weak));

void usart3_idle_callback(void)  __attribute__((weak));
void usart3_rxne_callback(void)  __attribute__((weak));
void usart3_txe_callback(void)   __attribute__((weak));
void usart3_tc_callback(void)    __attribute__((weak));

void usart3_cts_callback(void)   __attribute__((weak));
void usart3_rtof_callback(void)  __attribute__((weak));
void usart3_eob_callback(void)   __attribute__((weak));
void usart3_cmf_callback(void)   __attribute__((weak));
void usart3_wuf_callback(void)   __attribute__((weak));

void usart3_txfe_callback(void)  __attribute__((weak));
void usart3_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * UART4
 ******************************************************************************/
void uart4_pe_callback(void)     __attribute__((weak));
void uart4_fe_callback(void)     __attribute__((weak));
void uart4_ne_callback(void)     __attribute__((weak));
void uart4_ore_callback(void)    __attribute__((weak));

void uart4_idle_callback(void)   __attribute__((weak));
void uart4_rxne_callback(void)   __attribute__((weak));
void uart4_txe_callback(void)    __attribute__((weak));
void uart4_tc_callback(void)     __attribute__((weak));

void uart4_cts_callback(void)    __attribute__((weak));
void uart4_rtof_callback(void)   __attribute__((weak));
void uart4_eob_callback(void)    __attribute__((weak));
void uart4_cmf_callback(void)    __attribute__((weak));
void uart4_wuf_callback(void)    __attribute__((weak));

void uart4_txfe_callback(void)   __attribute__((weak));
void uart4_rxff_callback(void)   __attribute__((weak));

/******************************************************************************
 * UART5
 ******************************************************************************/
void uart5_pe_callback(void)     __attribute__((weak));
void uart5_fe_callback(void)     __attribute__((weak));
void uart5_ne_callback(void)     __attribute__((weak));
void uart5_ore_callback(void)    __attribute__((weak));

void uart5_idle_callback(void)   __attribute__((weak));
void uart5_rxne_callback(void)   __attribute__((weak));
void uart5_txe_callback(void)    __attribute__((weak));
void uart5_tc_callback(void)     __attribute__((weak));

void uart5_cts_callback(void)    __attribute__((weak));
void uart5_rtof_callback(void)   __attribute__((weak));
void uart5_eob_callback(void)    __attribute__((weak));
void uart5_cmf_callback(void)    __attribute__((weak));
void uart5_wuf_callback(void)    __attribute__((weak));

void uart5_txfe_callback(void)   __attribute__((weak));
void uart5_rxff_callback(void)   __attribute__((weak));

/******************************************************************************
 * LPUART1
 ******************************************************************************/
void lpuart1_pe_callback(void)   __attribute__((weak));
void lpuart1_fe_callback(void)   __attribute__((weak));
void lpuart1_ne_callback(void)   __attribute__((weak));
void lpuart1_ore_callback(void)  __attribute__((weak));

void lpuart1_idle_callback(void) __attribute__((weak));
void lpuart1_rxne_callback(void) __attribute__((weak));
void lpuart1_txe_callback(void)  __attribute__((weak));
void lpuart1_tc_callback(void)   __attribute__((weak));

void lpuart1_cts_callback(void)  __attribute__((weak));
void lpuart1_rtof_callback(void) __attribute__((weak));
void lpuart1_eob_callback(void)  __attribute__((weak));
void lpuart1_cmf_callback(void)  __attribute__((weak));
void lpuart1_wuf_callback(void)  __attribute__((weak));

void lpuart1_txfe_callback(void) __attribute__((weak));
void lpuart1_rxff_callback(void) __attribute__((weak));

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

/******************************************************************************
 * I2C1
 ******************************************************************************/
/* Error interrupts */
void i2c1_berr_callback(void)    __attribute__((weak));
void i2c1_arlo_callback(void)    __attribute__((weak));
void i2c1_ovr_callback(void)     __attribute__((weak));
void i2c1_pecerr_callback(void)  __attribute__((weak));
void i2c1_timeout_callback(void) __attribute__((weak));
void i2c1_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c1_rxne_callback(void)    __attribute__((weak));
void i2c1_txis_callback(void)    __attribute__((weak));
void i2c1_addr_callback(void)    __attribute__((weak));
void i2c1_nack_callback(void)    __attribute__((weak));
void i2c1_stop_callback(void)    __attribute__((weak));
void i2c1_tc_callback(void)      __attribute__((weak));
void i2c1_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C2
 ******************************************************************************/
/* Error interrupts */
void i2c2_berr_callback(void)    __attribute__((weak));
void i2c2_arlo_callback(void)    __attribute__((weak));
void i2c2_ovr_callback(void)     __attribute__((weak));
void i2c2_pecerr_callback(void)  __attribute__((weak));
void i2c2_timeout_callback(void) __attribute__((weak));
void i2c2_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c2_rxne_callback(void)    __attribute__((weak));
void i2c2_txis_callback(void)    __attribute__((weak));
void i2c2_addr_callback(void)    __attribute__((weak));
void i2c2_nack_callback(void)    __attribute__((weak));
void i2c2_stop_callback(void)    __attribute__((weak));
void i2c2_tc_callback(void)      __attribute__((weak));
void i2c2_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C3
 ******************************************************************************/
/* Error interrupts */
void i2c3_berr_callback(void)    __attribute__((weak));
void i2c3_arlo_callback(void)    __attribute__((weak));
void i2c3_ovr_callback(void)     __attribute__((weak));
void i2c3_pecerr_callback(void)  __attribute__((weak));
void i2c3_timeout_callback(void) __attribute__((weak));
void i2c3_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c3_rxne_callback(void)    __attribute__((weak));
void i2c3_txis_callback(void)    __attribute__((weak));
void i2c3_addr_callback(void)    __attribute__((weak));
void i2c3_nack_callback(void)    __attribute__((weak));
void i2c3_stop_callback(void)    __attribute__((weak));
void i2c3_tc_callback(void)      __attribute__((weak));
void i2c3_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C4
 ******************************************************************************/
/* Error interrupts */
void i2c4_berr_callback(void)    __attribute__((weak));
void i2c4_arlo_callback(void)    __attribute__((weak));
void i2c4_ovr_callback(void)     __attribute__((weak));
void i2c4_pecerr_callback(void)  __attribute__((weak));
void i2c4_timeout_callback(void) __attribute__((weak));
void i2c4_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c4_rxne_callback(void)    __attribute__((weak));
void i2c4_txis_callback(void)    __attribute__((weak));
void i2c4_addr_callback(void)    __attribute__((weak));
void i2c4_nack_callback(void)    __attribute__((weak));
void i2c4_stop_callback(void)    __attribute__((weak));
void i2c4_tc_callback(void)      __attribute__((weak));
void i2c4_tcr_callback(void)     __attribute__((weak));

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

/******************************************************************************
 * SPI1
 ******************************************************************************/
void spi1_rxne_callback(void)    __attribute__((weak));
void spi1_txe_callback(void)     __attribute__((weak));

void spi1_ovr_callback(void)     __attribute__((weak));
void spi1_modf_callback(void)    __attribute__((weak));
void spi1_crcerr_callback(void)  __attribute__((weak));
void spi1_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI2
 ******************************************************************************/
void spi2_rxne_callback(void)    __attribute__((weak));
void spi2_txe_callback(void)     __attribute__((weak));

void spi2_ovr_callback(void)     __attribute__((weak));
void spi2_modf_callback(void)    __attribute__((weak));
void spi2_crcerr_callback(void)  __attribute__((weak));
void spi2_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI3
 ******************************************************************************/
void spi3_rxne_callback(void)    __attribute__((weak));
void spi3_txe_callback(void)     __attribute__((weak));

void spi3_ovr_callback(void)     __attribute__((weak));
void spi3_modf_callback(void)    __attribute__((weak));
void spi3_crcerr_callback(void)  __attribute__((weak));
void spi3_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI4
 ******************************************************************************/
void spi4_rxne_callback(void)    __attribute__((weak));
void spi4_txe_callback(void)     __attribute__((weak));

void spi4_ovr_callback(void)     __attribute__((weak));
void spi4_modf_callback(void)    __attribute__((weak));
void spi4_crcerr_callback(void)  __attribute__((weak));
void spi4_fre_callback(void)     __attribute__((weak));

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

/******************************************************************************
 * DMA1
 ******************************************************************************/

/* Channel 1 */
void dma1_ch1_gif_callback(void) __attribute__((weak));
void dma1_ch1_tc_callback(void)  __attribute__((weak));
void dma1_ch1_ht_callback(void)  __attribute__((weak));
void dma1_ch1_te_callback(void)  __attribute__((weak));

/* Channel 2 */
void dma1_ch2_gif_callback(void) __attribute__((weak));
void dma1_ch2_tc_callback(void)  __attribute__((weak));
void dma1_ch2_ht_callback(void)  __attribute__((weak));
void dma1_ch2_te_callback(void)  __attribute__((weak));

/* Channel 3 */
void dma1_ch3_gif_callback(void) __attribute__((weak));
void dma1_ch3_tc_callback(void)  __attribute__((weak));
void dma1_ch3_ht_callback(void)  __attribute__((weak));
void dma1_ch3_te_callback(void)  __attribute__((weak));

/* Channel 4 */
void dma1_ch4_gif_callback(void) __attribute__((weak));
void dma1_ch4_tc_callback(void)  __attribute__((weak));
void dma1_ch4_ht_callback(void)  __attribute__((weak));
void dma1_ch4_te_callback(void)  __attribute__((weak));

/* Channel 5 */
void dma1_ch5_gif_callback(void) __attribute__((weak));
void dma1_ch5_tc_callback(void)  __attribute__((weak));
void dma1_ch5_ht_callback(void)  __attribute__((weak));
void dma1_ch5_te_callback(void)  __attribute__((weak));

/* Channel 6 */
void dma1_ch6_gif_callback(void) __attribute__((weak));
void dma1_ch6_tc_callback(void)  __attribute__((weak));
void dma1_ch6_ht_callback(void)  __attribute__((weak));
void dma1_ch6_te_callback(void)  __attribute__((weak));

/* Channel 7 */
void dma1_ch7_gif_callback(void) __attribute__((weak));
void dma1_ch7_tc_callback(void)  __attribute__((weak));
void dma1_ch7_ht_callback(void)  __attribute__((weak));
void dma1_ch7_te_callback(void)  __attribute__((weak));

/******************************************************************************
 * DMA2
 ******************************************************************************/

/* Channel 1 */
void dma2_ch1_gif_callback(void) __attribute__((weak));
void dma2_ch1_tc_callback(void)  __attribute__((weak));
void dma2_ch1_ht_callback(void)  __attribute__((weak));
void dma2_ch1_te_callback(void)  __attribute__((weak));

/* Channel 2 */
void dma2_ch2_gif_callback(void) __attribute__((weak));
void dma2_ch2_tc_callback(void)  __attribute__((weak));
void dma2_ch2_ht_callback(void)  __attribute__((weak));
void dma2_ch2_te_callback(void)  __attribute__((weak));

/* Channel 3 */
void dma2_ch3_gif_callback(void) __attribute__((weak));
void dma2_ch3_tc_callback(void)  __attribute__((weak));
void dma2_ch3_ht_callback(void)  __attribute__((weak));
void dma2_ch3_te_callback(void)  __attribute__((weak));

/* Channel 4 */
void dma2_ch4_gif_callback(void) __attribute__((weak));
void dma2_ch4_tc_callback(void)  __attribute__((weak));
void dma2_ch4_ht_callback(void)  __attribute__((weak));
void dma2_ch4_te_callback(void)  __attribute__((weak));

/* Channel 5 */
void dma2_ch5_gif_callback(void) __attribute__((weak));
void dma2_ch5_tc_callback(void)  __attribute__((weak));
void dma2_ch5_ht_callback(void)  __attribute__((weak));
void dma2_ch5_te_callback(void)  __attribute__((weak));

/* Channel 6 */
void dma2_ch6_gif_callback(void) __attribute__((weak));
void dma2_ch6_tc_callback(void)  __attribute__((weak));
void dma2_ch6_ht_callback(void)  __attribute__((weak));
void dma2_ch6_te_callback(void)  __attribute__((weak));

/* Channel 7 */
void dma2_ch7_gif_callback(void) __attribute__((weak));
void dma2_ch7_tc_callback(void)  __attribute__((weak));
void dma2_ch7_ht_callback(void)  __attribute__((weak));
void dma2_ch7_te_callback(void)  __attribute__((weak));

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

/******************************************************************************
 * ADC1
 ******************************************************************************/
void adc1_eoc_callback(void)     __attribute__((weak));
void adc1_eos_callback(void)     __attribute__((weak));
void adc1_awd_callback(void)     __attribute__((weak));
void adc1_overrun_callback(void) __attribute__((weak));

/******************************************************************************
 * ADC2
 ******************************************************************************/
void adc2_eoc_callback(void)     __attribute__((weak));
void adc2_eos_callback(void)     __attribute__((weak));
void adc2_awd_callback(void)     __attribute__((weak));
void adc2_overrun_callback(void) __attribute__((weak));

/******************************************************************************
 * ADC3
 ******************************************************************************/
void adc3_eoc_callback(void)     __attribute__((weak));
void adc3_eos_callback(void)     __attribute__((weak));
void adc3_awd_callback(void)     __attribute__((weak));
void adc3_overrun_callback(void) __attribute__((weak));

/******************************************************************************
 * ADC4
 ******************************************************************************/
void adc4_eoc_callback(void)     __attribute__((weak));
void adc4_eos_callback(void)     __attribute__((weak));
void adc4_awd_callback(void)     __attribute__((weak));
void adc4_overrun_callback(void) __attribute__((weak));

/******************************************************************************
 * ADC5
 ******************************************************************************/
void adc5_eoc_callback(void)     __attribute__((weak));
void adc5_eos_callback(void)     __attribute__((weak));
void adc5_awd_callback(void)     __attribute__((weak));
void adc5_overrun_callback(void) __attribute__((weak));

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

/******************************************************************************
 * EXTI
 ******************************************************************************/
void exti_line0_callback(void)     __attribute__((weak));
void exti_line1_callback(void)     __attribute__((weak));
void exti_line2_callback(void)     __attribute__((weak));
void exti_line3_callback(void)     __attribute__((weak));
void exti_line4_callback(void)     __attribute__((weak));
void exti_line5_9_callback(void)   __attribute__((weak));
void exti_line10_15_callback(void) __attribute__((weak));

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

/******************************************************************************
 * RTC
 ******************************************************************************/
void rtc_alarm_callback(void)     __attribute__((weak));
void rtc_wakeup_callback(void)    __attribute__((weak));
void rtc_timestamp_callback(void) __attribute__((weak));
void rtc_tamper_callback(void)    __attribute__((weak));
void rtc_overrun_callback(void)   __attribute__((weak));

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
    irq_rtc_t  *rtc;

} irq_t;

irq_t *irq(void);

#ifdef __cplusplus
}
#endif

#endif

/*** EOF ***/
