/**********************************************************************
	stm32g4_dev.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4 Family
**********************************************************************/
#ifndef STM32G4_DEV_H
	#define STM32G4_DEV_H

#include <stm32g4xx.h>
#include "custom_hal_def.h"

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

/*** DEV PARAMETER ***/
typedef const struct {
    NVIC_Type* nvic;
    SCB_Type* scb;
    SysTick_Type* systick;
    DWT_Type* dwt;
    ITM_Type* itm;
    TPI_Type* tpi;
    MPU_Type* mpu;
    CoreDebug_Type* coredebug;
} CORE_Block;

typedef const struct {
    RCC_TypeDef* rcc;
    FLASH_TypeDef* flash;
    PWR_TypeDef* pwr;
    SYSCFG_TypeDef* syscfg;
    CRS_TypeDef* crs;
} SYSTEM_Block;

typedef const struct {
    GPIO_TypeDef* a;
    GPIO_TypeDef* b;
    GPIO_TypeDef* c;
#ifdef GPIOD
    GPIO_TypeDef* d;
#endif
#ifdef GPIOE
    GPIO_TypeDef* e;
#endif
#ifdef GPIOF
    GPIO_TypeDef* f;
#endif
#ifdef GPIOG
    GPIO_TypeDef* g;
#endif
#ifdef GPIOH
    GPIO_TypeDef* h;
#endif
} GPIO_Block;

typedef const struct {
	/* Advanced */
	TIM_TypeDef* tim1;
#ifdef TIM8
	TIM_TypeDef* tim8;
#endif
#ifdef TIM20
	TIM_TypeDef* tim20;
#endif

	/* General purpose */
	TIM_TypeDef* tim2;
	TIM_TypeDef* tim3;
#ifdef TIM4
	TIM_TypeDef* tim4;
#endif
#ifdef TIM5
	TIM_TypeDef* tim5;
#endif

	/* Basic */
	TIM_TypeDef* tim6;
	TIM_TypeDef* tim7;

	/* Lite */
	TIM_TypeDef* tim15;
	TIM_TypeDef* tim16;
	TIM_TypeDef* tim17;
} TIM_Block;

typedef const struct {
    DMA_TypeDef* dma1;
    DMA_Channel_TypeDef* dma1_ch1;
    DMA_Channel_TypeDef* dma1_ch2;
    DMA_Channel_TypeDef* dma1_ch3;
    DMA_Channel_TypeDef* dma1_ch4;
    DMA_Channel_TypeDef* dma1_ch5;
    DMA_Channel_TypeDef* dma1_ch6;
#ifdef DMA1_Channel7
    DMA_Channel_TypeDef* dma1_ch7;
#endif

#ifdef DMA2
    DMA_TypeDef*  dma2;
    DMA_Channel_TypeDef* dma2_ch1;
    DMA_Channel_TypeDef* dma2_ch2;
    DMA_Channel_TypeDef* dma2_ch3;
    DMA_Channel_TypeDef* dma2_ch4;
    DMA_Channel_TypeDef* dma2_ch5;
    DMA_Channel_TypeDef* dma2_ch6;
#ifdef DMA2_Channel7
    DMA_Channel_TypeDef* dma2_ch7;
#endif
#endif

    DMAMUX_Channel_TypeDef* dmamux1;
    DMAMUX_Channel_TypeDef* dmamux1_ch1;
    DMAMUX_Channel_TypeDef* dmamux1_ch2;
    DMAMUX_Channel_TypeDef* dmamux1_ch3;
    DMAMUX_Channel_TypeDef* dmamux1_ch4;
    DMAMUX_Channel_TypeDef* dmamux1_ch5;
    DMAMUX_Channel_TypeDef* dmamux1_ch6;
#ifdef DMAMUX1_Channel7
    DMAMUX_Channel_TypeDef* dmamux1_ch7;
#endif
} DMA_Block;

typedef const struct {
    ADC_TypeDef* adc1;
#ifdef ADC2
    ADC_TypeDef* adc2;
#endif
#ifdef ADC3
    ADC_TypeDef* adc3;
#endif
#ifdef ADC4
    ADC_TypeDef* adc4;
#endif
#ifdef ADC5
    ADC_TypeDef* adc5;
#endif

    ADC_Common_TypeDef* adc12_common;
#ifdef ADC345_COMMON
    ADC_Common_TypeDef* adc345_common;
#endif

    DAC_TypeDef* dac1;
#ifdef DAC2
    DAC_TypeDef* dac2;
#endif
#ifdef DAC3
    DAC_TypeDef* dac3;
#endif
#ifdef DAC4
    DAC_TypeDef* dac4;
#endif
    COMP_TypeDef* comp;
    OPAMP_TypeDef* opamp;
} ANALOG_Block;

typedef const struct {
    USART_TypeDef* usart1;
    USART_TypeDef* usart2;
#ifdef USART3
    USART_TypeDef* usart3;
#endif
#ifdef UART4
    USART_TypeDef* uart4;
#endif
#ifdef UART5
    USART_TypeDef* uart5;
#endif
    USART_TypeDef* lpuart1;

    SPI_TypeDef* spi1;
    SPI_TypeDef* spi2;
#ifdef SPI3
    SPI_TypeDef* spi3;
#endif
#ifdef SPI4
    SPI_TypeDef* spi4;
#endif

    I2C_TypeDef* i2c1;
    I2C_TypeDef* i2c2;
#ifdef I2C3
    I2C_TypeDef* i2c3;
#endif
#ifdef I2C4
    I2C_TypeDef* i2c4;
#endif

#ifdef FDCAN1
    FDCAN_GlobalTypeDef* fdcan1;
#endif
#ifdef FDCAN2
    FDCAN_GlobalTypeDef* fdcan2;
#endif
#ifdef FDCAN3
    FDCAN_GlobalTypeDef* fdcan3;
#endif

#ifdef SAI1
    SAI_TypeDef* sai1;
#endif

#ifdef QUADSPI
    QUADSPI_TypeDef* qspi;
#endif
} COMM_Block;

typedef const struct {
#ifdef USB
    USB_TypeDef* usb_fs;
#endif
#ifdef RNG
    RNG_TypeDef* rng;
#endif
} EXT_Block;

typedef const struct {
    IWDG_TypeDef* iwdg;
    WWDG_TypeDef* wwdg;
} WD_Block;

typedef const struct {
    CRC_TypeDef* crc;
#ifdef FMC_BANK1
    FMC_Bank1_TypeDef* fmc;
#endif
} MEMORY_Block;

typedef const struct {
    EXTI_TypeDef* exti;
    DMAMUX_Channel_TypeDef* dmamux1;
    DMAMUX_RequestGen_TypeDef* dmamux_rg;
} EVENT_Block;

/*** DEV GET ***/
typedef const struct {
	uint32_t (*pll_source)(void);
	uint8_t (*pllm)(void);
	uint16_t (*plln)(void);
	uint8_t (*pllp)(void);
	uint8_t (*pllq)(void);
	uint8_t (*pllr)(void);
	uint32_t (*pll_vco_in)(void);
	uint32_t (*pll_vco_out)(void);
	uint32_t (*pllclk)(void);
	uint32_t (*sysclk)(void);
	uint32_t (*hclk)(void);
	uint32_t (*systickclk)(void);
	uint32_t (*pclk1)(void);
	uint32_t (*pclk2)(void);
	uint32_t (*timclk1)(void);
	uint32_t (*timclk2)(void);
	uint32_t (*adc12_hclk)(void);
	uint32_t (*adc12_ker_ck_input)(void);
	uint32_t (*adc12_ker_ck)(void);
	uint32_t (*freq_adc12)(void);
}DEV_get;

/*** DEV ENABLE ***/
typedef const struct {
    /* Core & System Configuration Controllers */
    void (*fpu)(void);
    void (*battery_charging)(void);
    void (*syscfg)(void);

    /* General Purpose Input Output Ports (AHB2 Bus Matrix) */
    void (*gpioa)(void);
    void (*gpiob)(void);
    void (*gpioc)(void);
    void (*gpiod)(void);
    void (*gpioe)(void);
    void (*gpiof)(void);
    void (*gpiog)(void);

    /* Direct Memory Access & System Accelerators (AHB1 Bus) */
    void (*dma1)(void);
    void (*dma2)(void);
    void (*dmamux)(void);
    void (*cordic)(void);
    void (*fmac)(void);
    void (*flash)(void);
    void (*crc)(void);

    /* External Memory Interfaces (AHB3 Bus) */
    void (*qspi)(void);
    void (*fmc)(void);

    /* Advanced Control & Performance Timers (APB2 Bus) */
    void (*tim1)(void);
    void (*tim8)(void);
    void (*tim15)(void);
    void (*tim16)(void);
    void (*tim17)(void);
    void (*tim20)(void);

    /* General Purpose, Basic, & Low Power Timers (APB1 Bus) */
    void (*tim2)(void);
    void (*tim3)(void);
    void (*tim4)(void);
    void (*tim5)(void);
    void (*tim6)(void);
    void (*tim7)(void);
    void (*lptim1)(void);

    /* Universal Synchronous Asynchronous Receiver Transmitters */
    void (*usart1)(void);
    void (*usart2)(void);
    void (*usart3)(void);
    void (*uart4)(void);
    void (*uart5)(void);

    /* Inter-Integrated Circuit Buses */
    void (*i2c1)(void);
    void (*i2c2)(void);
    void (*i2c3)(void);
    void (*i2c4)(void);

    /* Serial Peripheral Interfaces */
    void (*spi1)(void);
    void (*spi2)(void);
    void (*spi3)(void);
    void (*spi4)(void);

    /* Specialized Connectivity Blocks */
    void (*fdcan)(void);
    void (*crs)(void);
    void (*usb)(void);

    /* Analog-to-Digital and Digital-to-Analog Converters */
    void (*adc12)(void);
    void (*adc345)(void);
    void (*dac1)(void);
    void (*dac2)(void);
    void (*dac3)(void);
    void (*dac4)(void);

    /* Signal Conditioning & Security Modules */
    void (*opamp)(void);
    void (*comp)(void);
    void (*rng)(void);
}DEV_enable;

/*** DEV HANDLER ***/
typedef const struct {
	CORE_Block* core;
	SYSTEM_Block* sys;
	GPIO_Block* gpio;
	TIM_Block* timer;
	DMA_Block* dma;
	ANALOG_Block* analog;
	COMM_Block* comm;
	EXT_Block* ext;
	WD_Block* wd;
	MEMORY_Block* memory;
	EVENT_Block* event;
	DEV_get* get;
	DEV_enable* enable;
} STM32_DEVICE;

/*** DEV ACCESSOR FUNCTION ***/
STM32_DEVICE* dev(void);

#endif

/*** EOF ***/

