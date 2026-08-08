/**********************************************************************
	stm32g4_dev.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4 Family
**********************************************************************/
#ifndef STM32G4_DEV_H
	#define STM32G4_DEV_H

#include "stm32g4_hw.h"
#include "custom_hal_def.h"
#include "stm32x_tool.h"

/*** DEV HANDLER ***/
typedef const struct {
	DEV_get* get;
	DEV_enable* enable;
} STM32_DEVICE;

/*** DEV ACCESSOR FUNCTION ***/
STM32_DEVICE* dev(void);

#endif

/*** EOF ***/

