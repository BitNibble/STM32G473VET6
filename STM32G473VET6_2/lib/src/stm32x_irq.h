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

/*** INTERRUPT DEFINITION ***/
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDG_IRQHandler(void);
void PVD_PVM_IRQHandler(void);
void RTC_TAMP_CSS_LSE_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void DMA1_CH1_IRQHandler(void);
void DMA1_CH2_IRQHandler(void);
void DMA1_CH3_IRQHandler(void);
void DMA1_CH4_IRQHandler(void);
void DMA1_CH5_IRQHandler(void);
void DMA1_CH6_IRQHandler(void);
void DMA1_CH7_IRQHandler(void);
void ADC1_2_IRQHandler(void);
void USB_HP_IRQHandler(void);
void USB_LP_IRQHandler(void);
void FDCAN1_IT0_IRQHandler(void);
void FDCAN1_IT1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void TIM1_BRK_TIM15_IRQHandler(void);
void TIM1_UP_TIM16_IRQHandler(void);
void TIM1_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTC_ALARM_IRQHandler(void);
void USBWakeUP_IRQHandler(void);
void TIM8_BRK_IRQHandler(void);
void TIM8_UP_IRQHandler(void);
void TIM8_TRG_COM_IRQHandler(void);
void TIM8_CC_IRQHandler(void);
void ADC3_IRQHandler(void);
void FMC_IRQHandler(void);
void LPTIM1_IRQHandler(void);
void TIM5_IRQHandler(void);
void SPI3_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void TIM6_DACUNDER_IRQHandler(void);
void TIM7_IRQHandler(void);
void DMA2_CH1_IRQHandler(void);
void DMA2_CH2_IRQHandler(void);
void DMA2_CH3_IRQHandler(void);
void DMA2_CH4_IRQHandler(void);
void DMA2_CH5_IRQHandler(void);
void ADC4_IRQHandler(void);
void ADC5_IRQHandler(void);
void UCPD1_IRQHandler(void);
void COMP1_2_3_IRQHandler(void);
void COMP4_5_6_IRQHandler(void);
void COMP7_IRQHandler(void);
void CRS_IRQHandler(void);
void SAI_IRQHandler(void);
void TIM20_BRK_IRQHandler(void);
void TIM20_UP_IRQHandler(void);
void TIM20_TRG_COM_IRQHandler(void);
void TIM20_CC_IRQHandler(void);
void FPU_IRQHandler(void);
void I2C4_EV_IRQHandler(void);
void I2C4_ER_IRQHandler(void);
void SPI4_IRQHandler(void);
void AES_IRQHandler(void);
void FDCAN2_IT0_IRQHandler(void);
void FDCAN2_IT1_IRQHandler(void);
void FDCAN3_IT0_IRQHandler(void);
void FDCAN3_IT1_IRQHandler(void);
void RNG_IRQHandler(void);
void LPUART_IRQHandler(void);
void I2C3_EV_IRQHandler(void);
void I2C3_ER_IRQHandler(void);
void DMAMUX_OVR_IRQHandler(void);
void QUADSPI_IRQHandler(void);
void DMA1_CH8_IRQHandler(void);
void DMA2_CH6_IRQHandler(void);
void DMA2_CH7_IRQHandler(void);
void DMA2_CH8_IRQHandler(void);
void Cordic_IRQHandler(void);
void FMAC_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif

/*** EOF ***/

