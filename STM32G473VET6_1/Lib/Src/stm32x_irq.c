/******************************************************************************
	stm32x_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*******************************************************************************/
#include "stm32x_irq.h"

/*-------------------------------------------------------------
    TIM
-------------------------------------------------------------*/

static irq_tim_event_t tim1 = {0};
static irq_tim_event_t tim2 = {0};
static irq_tim_event_t tim3 = {0};
static irq_tim_event_t tim4 = {0};
static irq_tim_event_t tim5 = {0};
static irq_tim_event_t tim6 = {0};
static irq_tim_event_t tim7 = {0};
static irq_tim_event_t tim8 = {0};
static irq_tim_event_t tim15 = {0};
static irq_tim_event_t tim16 = {0};
static irq_tim_event_t tim17 = {0};
static irq_tim_event_t tim20 = {0};

static irq_tim_t tim =
{
    &tim1,
    &tim2,
    &tim3,
	&tim4,
	&tim5,
	&tim6,
	&tim7,
	&tim8,
	&tim15,
	&tim16,
	&tim17,
	&tim20
};

/********************************************************************
 * TIM1
 ********************************************************************/

void tim1_u_callback(void) {}
void tim1_cc1_callback(void) {}
void tim1_cc2_callback(void) {}
void tim1_cc3_callback(void) {}
void tim1_cc4_callback(void) {}
void tim1_trg_callback(void) {}
void tim1_brk_callback(void) {}
void tim1_brk2_callback(void) {}
void tim1_com_callback(void) {}

/********************************************************************
 * TIM8
 ********************************************************************/

void tim8_u_callback(void) {}
void tim8_cc1_callback(void) {}
void tim8_cc2_callback(void) {}
void tim8_cc3_callback(void) {}
void tim8_cc4_callback(void) {}
void tim8_trg_callback(void) {}
void tim8_brk_callback(void) {}
void tim8_com_callback(void) {}
void tim8_rep_callback(void) {}
void tim8_dma_callback(void) {}

/********************************************************************
 * TIM2–TIM5 (GENERAL PURPOSE)
 ********************************************************************/

void tim2_u_callback(void) {}
void tim2_cc1_callback(void) {}
void tim2_cc2_callback(void) {}
void tim2_cc3_callback(void) {}
void tim2_cc4_callback(void) {}

void tim3_u_callback(void) {}
void tim3_cc1_callback(void) {}
void tim3_cc2_callback(void) {}
void tim3_cc3_callback(void) {}
void tim3_cc4_callback(void) {}

void tim4_u_callback(void) {}
void tim4_cc1_callback(void) {}
void tim4_cc2_callback(void) {}
void tim4_cc3_callback(void) {}
void tim4_cc4_callback(void) {}

void tim5_u_callback(void) {}
void tim5_cc1_callback(void) {}
void tim5_cc2_callback(void) {}
void tim5_cc3_callback(void) {}
void tim5_cc4_callback(void) {}

/********************************************************************
 * TIM6–TIM7 (BASIC TIMERS)
 ********************************************************************/

void tim6_u_callback(void) {}
void tim7_u_callback(void) {}

/********************************************************************
 * TIM15–TIM17 (LOW POWER TIMERS)
 ********************************************************************/

void tim15_u_callback(void) {}
void tim15_cc1_callback(void) {}
void tim15_cc2_callback(void) {}
void tim15_trg_callback(void) {}
void tim15_com_callback(void) {}
void tim15_brk_callback(void) {}

void tim16_u_callback(void) {}
void tim16_cc1_callback(void) {}
void tim16_brk_callback(void) {}

void tim17_u_callback(void) {}
void tim17_cc1_callback(void) {}
void tim17_brk_callback(void) {}

/********************************************************************
 * TIM20 (ADVANCED / HIGH RESOLUTION)
 ********************************************************************/

void tim20_u_callback(void) {}
void tim20_cc1_callback(void) {}
void tim20_cc2_callback(void) {}
void tim20_cc3_callback(void) {}
void tim20_cc4_callback(void) {}
void tim20_trg_callback(void) {}
void tim20_brk_callback(void) {}
void tim20_brk2_callback(void) {}
void tim20_com_callback(void) {}

/*-------------------------------------------------------------
    UART
-------------------------------------------------------------*/

static irq_usart_event_t usart1 = {0};
static irq_usart_event_t usart2 = {0};
static irq_usart_event_t usart3 = {0};
static irq_usart_event_t uart4  = {0};
static irq_usart_event_t uart5  = {0};
static irq_usart_event_t lpuart1  = {0};

static irq_uart_t uart =
{
    &usart1,
    &usart2,
    &usart3,
    &uart4,
    &uart5,
	&lpuart1
};

/******************************************************************************
 * USART1
 ******************************************************************************/
void usart1_pe_callback(void)   {}
void usart1_fe_callback(void)   {}
void usart1_ne_callback(void)   {}
void usart1_ore_callback(void)  {}

void usart1_idle_callback(void) {}
void usart1_rxne_callback(void) {}
void usart1_txe_callback(void)  {}
void usart1_tc_callback(void)   {}

void usart1_cts_callback(void)  {}
void usart1_rtof_callback(void) {}
void usart1_eob_callback(void)  {}
void usart1_cmf_callback(void)  {}
void usart1_wuf_callback(void)  {}

void usart1_txfe_callback(void) {}
void usart1_rxff_callback(void) {}

/******************************************************************************
 * USART2
 ******************************************************************************/
void usart2_pe_callback(void)   {}
void usart2_fe_callback(void)   {}
void usart2_ne_callback(void)   {}
void usart2_ore_callback(void)  {}

void usart2_idle_callback(void) {}
void usart2_rxne_callback(void) {}
void usart2_txe_callback(void)  {}
void usart2_tc_callback(void)   {}

void usart2_cts_callback(void)  {}
void usart2_rtof_callback(void) {}
void usart2_eob_callback(void)  {}
void usart2_cmf_callback(void)  {}
void usart2_wuf_callback(void)  {}

void usart2_txfe_callback(void) {}
void usart2_rxff_callback(void) {}

/******************************************************************************
 * USART3
 ******************************************************************************/
void usart3_pe_callback(void)   {}
void usart3_fe_callback(void)   {}
void usart3_ne_callback(void)   {}
void usart3_ore_callback(void)  {}

void usart3_idle_callback(void) {}
void usart3_rxne_callback(void) {}
void usart3_txe_callback(void)  {}
void usart3_tc_callback(void)   {}

void usart3_cts_callback(void)  {}
void usart3_rtof_callback(void) {}
void usart3_eob_callback(void)  {}
void usart3_cmf_callback(void)  {}
void usart3_wuf_callback(void)  {}

void usart3_txfe_callback(void) {}
void usart3_rxff_callback(void) {}

/******************************************************************************
 * UART4
 ******************************************************************************/
void uart4_pe_callback(void)    {}
void uart4_fe_callback(void)    {}
void uart4_ne_callback(void)    {}
void uart4_ore_callback(void)   {}

void uart4_idle_callback(void)  {}
void uart4_rxne_callback(void)  {}
void uart4_txe_callback(void)   {}
void uart4_tc_callback(void)    {}

void uart4_cts_callback(void)   {}
void uart4_rtof_callback(void)  {}
void uart4_eob_callback(void)   {}
void uart4_cmf_callback(void)   {}
void uart4_wuf_callback(void)   {}

void uart4_txfe_callback(void)  {}
void uart4_rxff_callback(void)  {}

/******************************************************************************
 * UART5
 ******************************************************************************/
void uart5_pe_callback(void)    {}
void uart5_fe_callback(void)    {}
void uart5_ne_callback(void)    {}
void uart5_ore_callback(void)   {}

void uart5_idle_callback(void)  {}
void uart5_rxne_callback(void)  {}
void uart5_txe_callback(void)   {}
void uart5_tc_callback(void)    {}

void uart5_cts_callback(void)   {}
void uart5_rtof_callback(void)  {}
void uart5_eob_callback(void)   {}
void uart5_cmf_callback(void)   {}
void uart5_wuf_callback(void)   {}

void uart5_txfe_callback(void)  {}
void uart5_rxff_callback(void)  {}

/******************************************************************************
 * LPUART1
 ******************************************************************************/
void lpuart1_pe_callback(void)   {}
void lpuart1_fe_callback(void)   {}
void lpuart1_ne_callback(void)   {}
void lpuart1_ore_callback(void)  {}

void lpuart1_idle_callback(void) {}
void lpuart1_rxne_callback(void) {}
void lpuart1_txe_callback(void)  {}
void lpuart1_tc_callback(void)   {}

void lpuart1_cts_callback(void)  {}
void lpuart1_rtof_callback(void) {}
void lpuart1_eob_callback(void)  {}
void lpuart1_cmf_callback(void)  {}
void lpuart1_wuf_callback(void)  {}

void lpuart1_txfe_callback(void) {}
void lpuart1_rxff_callback(void) {}

/*-------------------------------------------------------------
    I2C
-------------------------------------------------------------*/

static irq_i2c_event_t irq_i2c1 = {0};
static irq_i2c_event_t irq_i2c2 = {0};
static irq_i2c_event_t irq_i2c3 = {0};
static irq_i2c_event_t irq_i2c4 = {0};

static irq_i2c_t i2c =
{
    .i2c1 = &irq_i2c1,
    .i2c2 = &irq_i2c2,
    .i2c3 = &irq_i2c3,
    .i2c4 = &irq_i2c4
};

/******************************************************************************
 * I2C1
 ******************************************************************************/
/* Error interrupts */
void i2c1_berr_callback(void)    {}
void i2c1_arlo_callback(void)    {}
void i2c1_ovr_callback(void)     {}
void i2c1_pecerr_callback(void)  {}
void i2c1_timeout_callback(void) {}
void i2c1_alert_callback(void)   {}

/* Event interrupts */
void i2c1_rxne_callback(void)      {}
void i2c1_txis_callback(void)      {}
void i2c1_addr_callback(void)    {}
void i2c1_nack_callback(void)    {}
void i2c1_stop_callback(void)    {}
void i2c1_tc_callback(void)      {}
void i2c1_tcr_callback(void)     {}

/******************************************************************************
 * I2C2
 ******************************************************************************/
/* Error interrupts */
void i2c2_berr_callback(void)    {}
void i2c2_arlo_callback(void)    {}
void i2c2_ovr_callback(void)     {}
void i2c2_pecerr_callback(void)  {}
void i2c2_timeout_callback(void) {}
void i2c2_alert_callback(void)   {}

/* Event interrupts */
void i2c2_rxne_callback(void)      {}
void i2c2_txis_callback(void)      {}
void i2c2_addr_callback(void)    {}
void i2c2_nack_callback(void)    {}
void i2c2_stop_callback(void)    {}
void i2c2_tc_callback(void)      {}
void i2c2_tcr_callback(void)     {}

/******************************************************************************
 * I2C3
 ******************************************************************************/
/* Error interrupts */
void i2c3_berr_callback(void)    {}
void i2c3_arlo_callback(void)    {}
void i2c3_ovr_callback(void)     {}
void i2c3_pecerr_callback(void)  {}
void i2c3_timeout_callback(void) {}
void i2c3_alert_callback(void)   {}

/* Event interrupts */
void i2c3_rxne_callback(void)      {}
void i2c3_txis_callback(void)      {}
void i2c3_addr_callback(void)    {}
void i2c3_nack_callback(void)    {}
void i2c3_stop_callback(void)    {}
void i2c3_tc_callback(void)      {}
void i2c3_tcr_callback(void)     {}

/******************************************************************************
 * I2C4
 ******************************************************************************/
/* Error interrupts */
void i2c4_berr_callback(void)    {}
void i2c4_arlo_callback(void)    {}
void i2c4_ovr_callback(void)     {}
void i2c4_pecerr_callback(void)  {}
void i2c4_timeout_callback(void) {}
void i2c4_alert_callback(void)   {}

/* Event interrupts */
void i2c4_rxne_callback(void)      {}
void i2c4_txis_callback(void)      {}
void i2c4_addr_callback(void)    {}
void i2c4_nack_callback(void)    {}
void i2c4_stop_callback(void)    {}
void i2c4_tc_callback(void)      {}
void i2c4_tcr_callback(void)     {}

/*-------------------------------------------------------------
    SPI
-------------------------------------------------------------*/

static irq_spi_event_t irq_spi1 = {0};
static irq_spi_event_t irq_spi2 = {0};
static irq_spi_event_t irq_spi3 = {0};
static irq_spi_event_t irq_spi4 = {0};

static irq_spi_t spi =
{
    .spi1 = &irq_spi1,
    .spi2 = &irq_spi2,
    .spi3 = &irq_spi3,
    .spi4 = &irq_spi4
};

/******************************************************************************
 * SPI1
 ******************************************************************************/
void spi1_rxne_callback(void)   {}
void spi1_txe_callback(void)    {}

void spi1_ovr_callback(void)    {}
void spi1_modf_callback(void)   {}
void spi1_crcerr_callback(void) {}
void spi1_fre_callback(void)    {}

/******************************************************************************
 * SPI2
 ******************************************************************************/
void spi2_rxne_callback(void)   {}
void spi2_txe_callback(void)    {}

void spi2_ovr_callback(void)    {}
void spi2_modf_callback(void)   {}
void spi2_crcerr_callback(void) {}
void spi2_fre_callback(void)    {}

/******************************************************************************
 * SPI3
 ******************************************************************************/
void spi3_rxne_callback(void)   {}
void spi3_txe_callback(void)    {}

void spi3_ovr_callback(void)    {}
void spi3_modf_callback(void)   {}
void spi3_crcerr_callback(void) {}
void spi3_fre_callback(void)    {}

/******************************************************************************
 * SPI4
 ******************************************************************************/
void spi4_rxne_callback(void)   {}
void spi4_txe_callback(void)    {}

void spi4_ovr_callback(void)    {}
void spi4_modf_callback(void)   {}
void spi4_crcerr_callback(void) {}
void spi4_fre_callback(void)    {}

/*-------------------------------------------------------------
    DMA
-------------------------------------------------------------*/

static irq_dma_channel_t dma1_ch1 = {0};
static irq_dma_channel_t dma1_ch2 = {0};
static irq_dma_channel_t dma1_ch3 = {0};
static irq_dma_channel_t dma1_ch4 = {0};
static irq_dma_channel_t dma1_ch5 = {0};
static irq_dma_channel_t dma1_ch6 = {0};
static irq_dma_channel_t dma1_ch7 = {0};

static irq_dma_channel_t dma2_ch1 = {0};
static irq_dma_channel_t dma2_ch2 = {0};
static irq_dma_channel_t dma2_ch3 = {0};
static irq_dma_channel_t dma2_ch4 = {0};
static irq_dma_channel_t dma2_ch5 = {0};
static irq_dma_channel_t dma2_ch6 = {0};
static irq_dma_channel_t dma2_ch7 = {0};

static irq_dma_controller_t irq_dma1 =
{
    .ch1 = &dma1_ch1,
    .ch2 = &dma1_ch2,
    .ch3 = &dma1_ch3,
    .ch4 = &dma1_ch4,
    .ch5 = &dma1_ch5,
    .ch6 = &dma1_ch6,
    .ch7 = &dma1_ch7
};

static irq_dma_controller_t irq_dma2 =
{
    .ch1 = &dma2_ch1,
    .ch2 = &dma2_ch2,
    .ch3 = &dma2_ch3,
    .ch4 = &dma2_ch4,
    .ch5 = &dma2_ch5,
    .ch6 = &dma2_ch6,
    .ch7 = &dma2_ch7
};

static irq_dma_t dma =
{
    .dma1 = &irq_dma1,
    .dma2 = &irq_dma2
};

/******************************************************************************
 * DMA1
 ******************************************************************************/

/* Channel 1 */
void dma1_ch1_gif_callback(void) {}
void dma1_ch1_tc_callback(void)  {}
void dma1_ch1_ht_callback(void)  {}
void dma1_ch1_te_callback(void)  {}

/* Channel 2 */
void dma1_ch2_gif_callback(void) {}
void dma1_ch2_tc_callback(void)  {}
void dma1_ch2_ht_callback(void)  {}
void dma1_ch2_te_callback(void)  {}

/* Channel 3 */
void dma1_ch3_gif_callback(void) {}
void dma1_ch3_tc_callback(void)  {}
void dma1_ch3_ht_callback(void)  {}
void dma1_ch3_te_callback(void)  {}

/* Channel 4 */
void dma1_ch4_gif_callback(void) {}
void dma1_ch4_tc_callback(void)  {}
void dma1_ch4_ht_callback(void)  {}
void dma1_ch4_te_callback(void)  {}

/* Channel 5 */
void dma1_ch5_gif_callback(void) {}
void dma1_ch5_tc_callback(void)  {}
void dma1_ch5_ht_callback(void)  {}
void dma1_ch5_te_callback(void)  {}

/* Channel 6 */
void dma1_ch6_gif_callback(void) {}
void dma1_ch6_tc_callback(void)  {}
void dma1_ch6_ht_callback(void)  {}
void dma1_ch6_te_callback(void)  {}

/* Channel 7 */
void dma1_ch7_gif_callback(void) {}
void dma1_ch7_tc_callback(void)  {}
void dma1_ch7_ht_callback(void)  {}
void dma1_ch7_te_callback(void)  {}

/******************************************************************************
 * DMA2
 ******************************************************************************/

/* Channel 1 */
void dma2_ch1_gif_callback(void) {}
void dma2_ch1_tc_callback(void)  {}
void dma2_ch1_ht_callback(void)  {}
void dma2_ch1_te_callback(void)  {}

/* Channel 2 */
void dma2_ch2_gif_callback(void) {}
void dma2_ch2_tc_callback(void)  {}
void dma2_ch2_ht_callback(void)  {}
void dma2_ch2_te_callback(void)  {}

/* Channel 3 */
void dma2_ch3_gif_callback(void) {}
void dma2_ch3_tc_callback(void)  {}
void dma2_ch3_ht_callback(void)  {}
void dma2_ch3_te_callback(void)  {}

/* Channel 4 */
void dma2_ch4_gif_callback(void) {}
void dma2_ch4_tc_callback(void)  {}
void dma2_ch4_ht_callback(void)  {}
void dma2_ch4_te_callback(void)  {}

/* Channel 5 */
void dma2_ch5_gif_callback(void) {}
void dma2_ch5_tc_callback(void)  {}
void dma2_ch5_ht_callback(void)  {}
void dma2_ch5_te_callback(void)  {}

/* Channel 6 */
void dma2_ch6_gif_callback(void) {}
void dma2_ch6_tc_callback(void)  {}
void dma2_ch6_ht_callback(void)  {}
void dma2_ch6_te_callback(void)  {}

/* Channel 7 */
void dma2_ch7_gif_callback(void) {}
void dma2_ch7_tc_callback(void)  {}
void dma2_ch7_ht_callback(void)  {}
void dma2_ch7_te_callback(void)  {}

/*-------------------------------------------------------------
    ADC
-------------------------------------------------------------*/

static irq_adc_event_t irq_adc1 = {0};
static irq_adc_event_t irq_adc2 = {0};
static irq_adc_event_t irq_adc3 = {0};
static irq_adc_event_t irq_adc4 = {0};
static irq_adc_event_t irq_adc5 = {0};

static irq_adc_t adc =
{
    .adc1 = &irq_adc1,
    .adc2 = &irq_adc2,
    .adc3 = &irq_adc3,
    .adc4 = &irq_adc4,
    .adc5 = &irq_adc5
};

/******************************************************************************
 * ADC1
 ******************************************************************************/
void adc1_eoc_callback(void)     {}
void adc1_eos_callback(void)     {}
void adc1_awd_callback(void)     {}
void adc1_overrun_callback(void) {}

/******************************************************************************
 * ADC2
 ******************************************************************************/
void adc2_eoc_callback(void)     {}
void adc2_eos_callback(void)     {}
void adc2_awd_callback(void)     {}
void adc2_overrun_callback(void) {}

/******************************************************************************
 * ADC3
 ******************************************************************************/
void adc3_eoc_callback(void)     {}
void adc3_eos_callback(void)     {}
void adc3_awd_callback(void)     {}
void adc3_overrun_callback(void) {}

/******************************************************************************
 * ADC4
 ******************************************************************************/
void adc4_eoc_callback(void)     {}
void adc4_eos_callback(void)     {}
void adc4_awd_callback(void)     {}
void adc4_overrun_callback(void) {}

/******************************************************************************
 * ADC5
 ******************************************************************************/
void adc5_eoc_callback(void)     {}
void adc5_eos_callback(void)     {}
void adc5_awd_callback(void)     {}
void adc5_overrun_callback(void) {}

/*-------------------------------------------------------------
    EXTI
-------------------------------------------------------------*/

static irq_exti_t exti =
{
    .line0     = NULL,
    .line1     = NULL,
    .line2     = NULL,
    .line3     = NULL,
    .line4     = NULL,
    .line5_9   = NULL,
    .line10_15 = NULL
};

/******************************************************************************
 * EXTI
 ******************************************************************************/
void exti_line0_callback(void)     {}
void exti_line1_callback(void)     {}
void exti_line2_callback(void)     {}
void exti_line3_callback(void)     {}
void exti_line4_callback(void)     {}
void exti_line5_9_callback(void)   {}
void exti_line10_15_callback(void) {}

/*-------------------------------------------------------------
    RTC
-------------------------------------------------------------*/

static irq_rtc_t rtc =
{
    .Alarm     = NULL,
    .WakeUp    = NULL,
    .TimeStamp = NULL,
    .Tamper    = NULL,
    .Overrun   = NULL
};

/******************************************************************************
 * RTC
 ******************************************************************************/
void rtc_alarm_callback(void)     {}
void rtc_wakeup_callback(void)    {}
void rtc_timestamp_callback(void) {}
void rtc_tamper_callback(void)    {}
void rtc_overrun_callback(void)   {}

/*-------------------------------------------------------------
    ROOT
-------------------------------------------------------------*/

static IRQ_Handle irq_root =
{
    &tim,
    &uart,
    &i2c,
    &spi,   /* spi */
    &dma,   /* dma */
    &adc,   /* adc */
    &exti,  /* exti */
	&rtc    /* rtc */
};

IRQ_Handle *irq(void)
{
    return &irq_root;
}

/*** EOF ***/
