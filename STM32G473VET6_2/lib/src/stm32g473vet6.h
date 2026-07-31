/**********************************************************************
	stm32g473vet6.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
**********************************************************************/
#ifndef STM32G4XX_FAMILY_H
	#define STM32G4XX_FAMILY_H

#include "stm32g4_dev.h"
#include "stm32x_irq.h"
#include "stm32x_tool.h"
#include "stm32x_gpio.h"

/****************************************/
/*******   1 -> HSI    2->HSE   *********/
#define H_Clock_Source 2
/****   PLL ON -> 1    PLL OFF = 0   ****/
#define PLL_ON_OFF 1
/****************************************/

// Clamping wrappers
#define LIMIT_INC(val, max, min)  ((val) >= (max) ? (min) : (val) + 1)
#define LIMIT_DEC(val, max, min)  ((val) <= (min) ? (max) : (val) - 1)

#endif

/*** EOF***/

