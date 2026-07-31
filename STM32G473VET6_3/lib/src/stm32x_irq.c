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

/*-------------------------------------------------------------
    I2C
-------------------------------------------------------------*/

/******************************************************************************
 * I2C OBJECTS
 ******************************************************************************/

static irq_i2c_event_t irq_i2c1 = {0};
static irq_i2c_event_t irq_i2c2 = {0};
static irq_i2c_event_t irq_i2c3 = {0};
static irq_i2c_event_t irq_i2c4 = {0};


/******************************************************************************
 * ROOT I2C OBJECT
 ******************************************************************************/

static irq_i2c_t i2c =
{
    .i2c1 = &irq_i2c1,
    .i2c2 = &irq_i2c2,
    .i2c3 = &irq_i2c3,
    .i2c4 = &irq_i2c4
};

/******************************************************************************
 * SPI OBJECTS
 ******************************************************************************/

static irq_spi_event_t irq_spi1 = {0};
static irq_spi_event_t irq_spi2 = {0};
static irq_spi_event_t irq_spi3 = {0};
static irq_spi_event_t irq_spi4 = {0};


/******************************************************************************
 * ROOT SPI OBJECT
 ******************************************************************************/

static irq_spi_t spi =
{
    .spi1 = &irq_spi1,
    .spi2 = &irq_spi2,
    .spi3 = &irq_spi3,
    .spi4 = &irq_spi4
};

/******************************************************************************
 * DMA CHANNEL OBJECTS
 ******************************************************************************/

/* DMA1 */
static irq_dma_channel_t dma1_ch1 = {0};
static irq_dma_channel_t dma1_ch2 = {0};
static irq_dma_channel_t dma1_ch3 = {0};
static irq_dma_channel_t dma1_ch4 = {0};
static irq_dma_channel_t dma1_ch5 = {0};
static irq_dma_channel_t dma1_ch6 = {0};
static irq_dma_channel_t dma1_ch7 = {0};

/* DMA2 */
static irq_dma_channel_t dma2_ch1 = {0};
static irq_dma_channel_t dma2_ch2 = {0};
static irq_dma_channel_t dma2_ch3 = {0};
static irq_dma_channel_t dma2_ch4 = {0};
static irq_dma_channel_t dma2_ch5 = {0};
static irq_dma_channel_t dma2_ch6 = {0};
static irq_dma_channel_t dma2_ch7 = {0};


/******************************************************************************
 * DMA CONTROLLERS
 ******************************************************************************/

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


/******************************************************************************
 * ROOT DMA OBJECT
 ******************************************************************************/

static irq_dma_t dma =
{
    .dma1 = &irq_dma1,
    .dma2 = &irq_dma2
};

/******************************************************************************
 * ADC OBJECTS
 ******************************************************************************/

static irq_adc_event_t irq_adc1 = {0};
static irq_adc_event_t irq_adc2 = {0};
static irq_adc_event_t irq_adc3 = {0};
static irq_adc_event_t irq_adc4 = {0};
static irq_adc_event_t irq_adc5 = {0};


/******************************************************************************
 * ROOT ADC OBJECT
 ******************************************************************************/

static irq_adc_t adc =
{
    .adc1 = &irq_adc1,
    .adc2 = &irq_adc2,
    .adc3 = &irq_adc3,
    .adc4 = &irq_adc4,
    .adc5 = &irq_adc5
};

/******************************************************************************
 * EXTI OBJECT
 ******************************************************************************/

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

/*-------------------------------------------------------------
    ROOT
-------------------------------------------------------------*/

static irq_t irq_root =
{
    &tim,
    &uart,
    &i2c,
    &spi,   /* spi */
    &dma,   /* dma */
    &adc,   /* adc */
    &exti   /* exti */
};

irq_t *irq(void)
{
    return &irq_root;
}

/*** EOF ***/

