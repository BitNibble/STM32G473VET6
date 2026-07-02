/******************************************************************************
	STM32 XXX systick
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Update:   16012024
*******************************************************************************/
#ifndef ARMSYSTICK_H_
	#define ARMSYSTICK_H_

/*** File Library ***/
#include <stdint.h>
#include <inttypes.h>
/*** SysTick Constants ***/
void systick_configure(void);
/*** SysTick Polling ***/
void _delay_us(uint32_t us);
void _delay_10us(uint32_t dez_us);
void _delay_ms(uint32_t ms);

#endif

/*** EOF ***/

