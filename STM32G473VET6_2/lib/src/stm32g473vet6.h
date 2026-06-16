/**********************************************************************
Family:   STM32G4xx Universal Accessor Library
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Fits entire STM32G4 Family (G431, G441, G471, G473, G474, etc.)
Date:     04062026
**********************************************************************/
#ifndef STM32G4XX_FAMILY_H
#define STM32G4XX_FAMILY_H

#include <stm32g4xx.h>
#include "custom_hal_def.h"
#include "stm32xtool.h"

/****************************************/
/*******   1 -> HSI    2->HSE   *********/
#define H_Clock_Source 2
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 1
/****************************************/

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
    DWT_Type* const dwt;
    ITM_Type* const itm;
    TPI_Type* const tpi;
    MPU_Type* const mpu;
    CoreDebug_Type* const coredebug;
} CORE_Block;

typedef struct {
    RCC_TypeDef* const rcc;
    FLASH_TypeDef* const flash;
    PWR_TypeDef* const pwr;
    SYSCFG_TypeDef* const syscfg;
    CRS_TypeDef* const crs;
} SYSTEM_Block;

typedef struct {
    GPIO_TypeDef* const a;
    GPIO_TypeDef* const b;
    GPIO_TypeDef* const c;
#ifdef GPIOD
    GPIO_TypeDef* const d;
#endif
#ifdef GPIOE
    GPIO_TypeDef* const e;
#endif
#ifdef GPIOF
    GPIO_TypeDef* const f;
#endif
#ifdef GPIOG
    GPIO_TypeDef* const g;
#endif
#ifdef GPIOH
    GPIO_TypeDef* const h;
#endif
} GPIO_Block;

typedef struct {
	/* Advanced */
	TIM_TypeDef* const tim1;
#ifdef TIM8
	TIM_TypeDef* const tim8;
#endif
#ifdef TIM20
	TIM_TypeDef* const tim20;
#endif

	/* General purpose */
	TIM_TypeDef* const tim2;
	TIM_TypeDef* const tim3;
#ifdef TIM4
	TIM_TypeDef* const tim4;
#endif
#ifdef TIM5
	TIM_TypeDef* const tim5;
#endif

	/* Basic */
	TIM_TypeDef* const tim6;
	TIM_TypeDef* const tim7;

	/* Lite */
	TIM_TypeDef* const tim15;
	TIM_TypeDef* const tim16;
	TIM_TypeDef* const tim17;
} TIM_Block;

typedef struct {
    DMA_TypeDef* const dma1;
    DMA_Channel_TypeDef* const dma1_ch1;
    DMA_Channel_TypeDef* const dma1_ch2;
    DMA_Channel_TypeDef* const dma1_ch3;
    DMA_Channel_TypeDef* const dma1_ch4;
    DMA_Channel_TypeDef* const dma1_ch5;
    DMA_Channel_TypeDef* const dma1_ch6;
#ifdef DMA1_Channel7
    DMA_Channel_TypeDef* const dma1_ch7;
#endif

#ifdef DMA2
    DMA_TypeDef* const dma2;
    DMA_Channel_TypeDef* const dma2_ch1;
    DMA_Channel_TypeDef* const dma2_ch2;
    DMA_Channel_TypeDef* const dma2_ch3;
    DMA_Channel_TypeDef* const dma2_ch4;
    DMA_Channel_TypeDef* const dma2_ch5;
    DMA_Channel_TypeDef* const dma2_ch6;
#ifdef DMA2_Channel7
    DMA_Channel_TypeDef* const dma2_ch7;
#endif
#endif

    DMAMUX_Channel_TypeDef* const dmamux1;
    DMAMUX_Channel_TypeDef* const dmamux1_ch1;
    DMAMUX_Channel_TypeDef* const dmamux1_ch2;
    DMAMUX_Channel_TypeDef* const dmamux1_ch3;
    DMAMUX_Channel_TypeDef* const dmamux1_ch4;
    DMAMUX_Channel_TypeDef* const dmamux1_ch5;
    DMAMUX_Channel_TypeDef* const dmamux1_ch6;
#ifdef DMAMUX1_Channel7
    DMAMUX_Channel_TypeDef* const dmamux1_ch7;
#endif
} DMA_Block;

typedef struct {
    ADC_TypeDef* const adc1;
#ifdef ADC2
    ADC_TypeDef* const adc2;
#endif
#ifdef ADC3
    ADC_TypeDef* const adc3;
#endif
#ifdef ADC4
    ADC_TypeDef* const adc4;
#endif
#ifdef ADC5
    ADC_TypeDef* const adc5;
#endif

    ADC_Common_TypeDef* const adc12_common;
#ifdef ADC345_COMMON
    ADC_Common_TypeDef* const adc345_common;
#endif

    DAC_TypeDef* const dac1;
#ifdef DAC2
    DAC_TypeDef* const dac2;
#endif
#ifdef DAC3
    DAC_TypeDef* const dac3;
#endif
#ifdef DAC4
    DAC_TypeDef* const dac4;
#endif
    COMP_TypeDef* const comp;
    OPAMP_TypeDef* const opamp;
} ANALOG_Block;

typedef struct {
    USART_TypeDef* const usart1;
    USART_TypeDef* const usart2;
#ifdef USART3
    USART_TypeDef* const usart3;
#endif
#ifdef UART4
    USART_TypeDef* const uart4;
#endif
#ifdef UART5
    USART_TypeDef* const uart5;
#endif
    USART_TypeDef* const lpuart1;

    SPI_TypeDef* const spi1;
    SPI_TypeDef* const spi2;
#ifdef SPI3
    SPI_TypeDef* const spi3;
#endif
#ifdef SPI4
    SPI_TypeDef* const spi4;
#endif

    I2C_TypeDef* const i2c1;
    I2C_TypeDef* const i2c2;
#ifdef I2C3
    I2C_TypeDef* const i2c3;
#endif
#ifdef I2C4
    I2C_TypeDef* const i2c4;
#endif

#ifdef FDCAN1
    FDCAN_GlobalTypeDef* const fdcan1;
#endif
#ifdef FDCAN2
    FDCAN_GlobalTypeDef* const fdcan2;
#endif
#ifdef FDCAN3
    FDCAN_GlobalTypeDef* const fdcan3;
#endif

#ifdef SAI1
    SAI_TypeDef* const sai1;
#endif

#ifdef QUADSPI
    QUADSPI_TypeDef* const qspi;
#endif
} COMM_Block;

typedef struct {
#ifdef USB
    USB_TypeDef* const usb_fs;
#endif
#ifdef RNG
    RNG_TypeDef* const rng;
#endif
} EXT_Block;

typedef struct {
    IWDG_TypeDef* const iwdg;
    WWDG_TypeDef* const wwdg;
} WD_Block;

typedef struct {
    CRC_TypeDef* const crc;
#ifdef FMC_BANK1
    FMC_Bank1_TypeDef* const fmc;
#endif
} MEMORY_Block;

typedef struct {
    EXTI_TypeDef* const exti;
    DMAMUX_Channel_TypeDef* const dmamux1;
    DMAMUX_RequestGen_TypeDef* const dmamux_rg;
} EVENT_Block;

/******************************************************************
 * DEVICE STRUCTURE
 ******************************************************************/
typedef struct {
	CORE_Block* const core;
	SYSTEM_Block* const sys;
	GPIO_Block* const gpio;
	TIM_Block* const timer;
	DMA_Block* const dma;
	ANALOG_Block* const analog;
	COMM_Block* const comm;
	EXT_Block* const ext;
	WD_Block* const wd;
	MEMORY_Block* const memory;
	EVENT_Block* const event;
} STM32_DEVICE;

const STM32_DEVICE* dev(void);

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
uint32_t get_systickclk(void);
uint32_t get_pclk1(void);
uint32_t get_pclk2(void);
uint32_t get_timclk1(void);
uint32_t get_timclk2(void);

/************************* Generic UTILS ***************************/
U_word writeHLbyte(uint16_t v);

/************************** GPIO UTILS *****************************/
void GPIO_clock(GPIO_TypeDef* GPIO, uint8_t enable);
void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode );
void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype );
void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed );
void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd );
void GPIO_hmoder( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t mode );
void GPIO_hotype( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t otype );
void GPIO_hospeed( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t ospeed );
void GPIO_hpupd( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t pupd );
void GPIO_lck(GPIO_TypeDef* GPIO, uint16_t hpin);
void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af );
void set_hpin(GPIO_TypeDef* reg, uint16_t hpin);
void clear_hpin(GPIO_TypeDef* reg, uint16_t hpin);
void toggle_hpin(GPIO_TypeDef* reg, uint16_t hpin);
void set_pin(GPIO_TypeDef* reg, uint8_t pin);
void clear_pin(GPIO_TypeDef* reg, uint8_t pin);

/************************** FPU ENABLE *****************************/
void fpu_enable(void);

#endif

