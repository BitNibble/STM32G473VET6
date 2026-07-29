#include "stm32_irq.h"

/*-------------------------------------------------------------
    TIM
-------------------------------------------------------------*/

static irq_tim_event_t tim1 = {0};
static irq_tim_event_t tim2 = {0};
static irq_tim_event_t tim3 = {0};
/* ... */

static irq_tim_t tim =
{
    &tim1,
    &tim2,
    &tim3,
    /* ... */
};

/*-------------------------------------------------------------
    UART
-------------------------------------------------------------*/

static irq_usart_event_t usart1 = {0};
static irq_usart_event_t usart2 = {0};
static irq_usart_event_t usart3 = {0};
static irq_usart_event_t uart4  = {0};
static irq_usart_event_t uart5  = {0};

static irq_uart_t uart =
{
    &usart1,
    &usart2,
    &usart3,
    &uart4,
    &uart5
};

/*-------------------------------------------------------------
    I2C
-------------------------------------------------------------*/

static irq_i2c_event_t i2c1 = {0};
static irq_i2c_event_t i2c2 = {0};

static irq_i2c_t i2c =
{
    &i2c1,
    &i2c2,
    0,
    0
};

/*-------------------------------------------------------------
    ROOT
-------------------------------------------------------------*/

static irq_t irq_root =
{
    &tim,
    &uart,
    &i2c,
    0,      /* spi */
    0,      /* dma */
    0,      /* adc */
    0       /* exti */
};

irq_t *irq(void)
{
    return &irq_root;
}
