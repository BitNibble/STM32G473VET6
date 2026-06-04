/**********************************************************************
	STM32G473VET6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
Date:     04062026
**********************************************************************/
#ifndef STM32G473VET6_H
#define STM32G473VET6_H

#include <stm32g4xx.h>
#include <stm32g4xx_hal.h>
#include "stm32xtool.h"

/****************************************/
typedef union{
	struct UN8bit{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
	}par;
	uint8_t var;
}U_byte;

typedef union{
	struct UN16byte{
		uint8_t l;
		uint8_t h;
	}par;
	uint16_t var;
}U_word;

typedef union{
	struct UN32word{
		uint16_t l;
		uint16_t h;
	}par;
	uint32_t var;
}U_dword;

typedef union{
	struct UN64dword{
		uint32_t l;
		uint32_t h;
	}par;
	uint64_t var;
}U_qword;

/******************************************************************
 * CORE
 ******************************************************************/
typedef struct {
    NVIC_Type* const nvic;
    SCB_Type* const scb;
    SysTick_Type* const systick;
    ITM_Type* const itm;
    DWT_Type* const dwt;
    TPI_Type* const tpi;
    MPU_Type* const mpu;
    CoreDebug_Type* const coredebug;
} STM32G473_CORE;

/******************************************************************
 * DEVICE
 ******************************************************************/
typedef const struct {

    STM32G473_CORE* core;

    /* SYSTEM */
    RCC_TypeDef* const rcc;
    FLASH_TypeDef* const flash;
    PWR_TypeDef* const pwr;
    SYSCFG_TypeDef* const syscfg;
    CRS_TypeDef* const crs;

    /* GPIO */
    GPIO_TypeDef* const gpioa;
    GPIO_TypeDef* const gpiob;
    GPIO_TypeDef* const gpioc;
    GPIO_TypeDef* const gpiod;
    GPIO_TypeDef* const gpioe;
    GPIO_TypeDef* const gpiof;
    GPIO_TypeDef* const gpiog;

    /* DMA + DMAMUX (CRITICAL DIFFERENCE vs F4) */
    DMA_TypeDef* const dma1;
    DMA_TypeDef* const dma2;

    DMA_Channel_TypeDef* const dma1_ch1;
    DMA_Channel_TypeDef* const dma1_ch2;
    DMA_Channel_TypeDef* const dma1_ch3;
    DMA_Channel_TypeDef* const dma1_ch4;
    DMA_Channel_TypeDef* const dma1_ch5;
    DMA_Channel_TypeDef* const dma1_ch6;
    DMA_Channel_TypeDef* const dma1_ch7;

    DMA_Channel_TypeDef* const dma2_ch1;
    DMA_Channel_TypeDef* const dma2_ch2;
    DMA_Channel_TypeDef* const dma2_ch3;
    DMA_Channel_TypeDef* const dma2_ch4;
    DMA_Channel_TypeDef* const dma2_ch5;
    DMA_Channel_TypeDef* const dma2_ch6;
    DMA_Channel_TypeDef* const dma2_ch7;

    DMAMUX_Channel_TypeDef* const dmamux1_ch1;
    DMAMUX_Channel_TypeDef* const dmamux1_ch2;
    DMAMUX_Channel_TypeDef* const dmamux1_ch3;
    DMAMUX_Channel_TypeDef* const dmamux1_ch4;
    DMAMUX_Channel_TypeDef* const dmamux1_ch5;
    DMAMUX_Channel_TypeDef* const dmamux1_ch6;
    DMAMUX_Channel_TypeDef* const dmamux1_ch7;

    /* TIMERS */
    TIM_TypeDef* const tim1;
    TIM_TypeDef* const tim2;
    TIM_TypeDef* const tim3;
    TIM_TypeDef* const tim4;
    TIM_TypeDef* const tim5;
    TIM_TypeDef* const tim6;
    TIM_TypeDef* const tim7;
    TIM_TypeDef* const tim8;
    TIM_TypeDef* const tim15;
    TIM_TypeDef* const tim16;
    TIM_TypeDef* const tim17;

    /* ANALOG */
    ADC_TypeDef* const adc1;
    ADC_TypeDef* const adc2;
    ADC_TypeDef* const adc3;

    ADC_Common_TypeDef* const adc12_common;
    ADC_Common_TypeDef* const adc345_common;

    DAC_TypeDef* const dac1;

    COMP_TypeDef* const comp;
    OPAMP_TypeDef* const opamp;

    /* COMMUNICATION */
    USART_TypeDef* const usart1;
    USART_TypeDef* const usart2;
    USART_TypeDef* const usart3;
    USART_TypeDef* const uart4;
    USART_TypeDef* const uart5;
    USART_TypeDef* const lpuart1;

    SPI_TypeDef* const spi1;
    SPI_TypeDef* const spi2;
    SPI_TypeDef* const spi3;

    I2C_TypeDef* const i2c1;
    I2C_TypeDef* const i2c2;
    I2C_TypeDef* const i2c3;

    /* WATCHDOG */
    IWDG_TypeDef* const iwdg;
    WWDG_TypeDef* const wwdg;

    /* USB FS DEVICE (G4 correct model) */
    USB_TypeDef* const usb_fs;

} STM32G473_DEVICE;

const STM32G473_DEVICE* dev(void);

/************************** CLOCK QUERY ****************************/
uint32_t get_pll_source(void);
uint8_t get_pllm(void);
uint16_t get_plln(void);
uint8_t get_pllp(void);
uint8_t get_pllq(void);
uint8_t get_pllr(void);
uint32_t get_pll_vco_in(void);
uint32_t get_pll_vco_out(void);
uint32_t get_pllclk(void);
uint32_t get_sysclk(void);
uint32_t get_hclk(void);
uint32_t get_pclk1(void);
uint32_t get_pclk2(void);
uint32_t get_timclk1(void);
uint32_t get_timclk2(void);

/************************** GPIO UTILS *****************************/
void GPIO_clock( GPIO_TypeDef* GPIO, uint8_t enable );
void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode );
void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype );
void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed );
void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd );
void GPIO_lck( GPIO_TypeDef* GPIO, uint16_t hpins );
void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af );
void set_hpins(GPIO_TypeDef* reg, uint16_t hpins);
void clear_hpins(GPIO_TypeDef* reg, uint16_t hpins);
void set_pin(GPIO_TypeDef* reg, uint8_t pin);
void clear_pin(GPIO_TypeDef* reg, uint8_t pin);

/************************** FPU ENABLE *****************************/
void fpu_enable(void);

#endif

