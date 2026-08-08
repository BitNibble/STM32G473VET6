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

/*** DEV RUN ***/
typedef const struct {
	void (*fpu)(void);
	void (*battery_charging)(void);
	void (*disable_fpu)(void);
	void (*disable_battery_charging)(void);
	void (*enable_opamp_clock)(void);
	void (*enable_comp_clock)(void);
	void (*disable_opamp_clock)(void);
	void (*disable_comp_clock)(void);
}DEV_run;

/*** DEV HANDLER ***/
typedef const struct {
	DEV_get* get;
	void (*enable)(const void *peripheral_base);
	void (*disable)(const void *peripheral_base);
	DEV_run* run;
} STM32_DEVICE;

/*** DEV ACCESSOR FUNCTION ***/
STM32_DEVICE* dev(void);

#endif

/*** EOF ***/

