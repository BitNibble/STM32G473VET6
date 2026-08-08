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
#include "stm32x_tool.h"

/*** DEV CLOCK ***/
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
	DEV_get* get;
	DEV_enable* enable;
} STM32_DEVICE;

/*** DEV ACCESSOR FUNCTION ***/
STM32_DEVICE* dev(void);

#endif

/*** EOF ***/

