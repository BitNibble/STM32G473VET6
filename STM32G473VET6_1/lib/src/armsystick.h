/******************************************************************************
	STM32 XXX systick
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Update:   16012024
*******************************************************************************/
#ifndef _ARMSYSTICK_H_
	#define _ARMSYSTICK_H_

/*** File Library ***/
#include <stdint.h>
#include <inttypes.h>
/*** SysTick Constants ***/
uint32_t get_systick_us(void);
uint32_t get_systick_10us(void);
uint32_t get_systick_ms(void);
/*** Count Polling ***/
void delayMiliseconds(unsigned int ms);
void delayMicroseconds(unsigned int us);
void delayAsmMicroseconds(unsigned int us);
/*** SysTick Polling ***/
void _delay_us(uint32_t us);
void _delay_10us(uint32_t dez_us);
void _delay_ms(uint32_t ms);
/*** SysTick Initializer ***/
void systick_inic(void);
/*** SysTick Helper ***/
void SysTick_Inc(void);

#endif

/******
Load does not accept values below 70.
Note us only work for high frequency clocks.
******/

/*** EOF ***/

