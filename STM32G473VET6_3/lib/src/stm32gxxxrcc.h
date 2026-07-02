/******************************************************************************
	STM32 GXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-GXXX
Date: 04062026
*******************************************************************************/
#ifndef STM32GXXXRCC_H
	#define STM32GXXXRCC_H
/*** Library ***/
#include "stm32g473vet6.h"
// RCC -> PLL
typedef const struct
{
	void (*division)(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq, uint8_t pllr);
	void (*enable)(void);
}STM32GXXX_RCC_PLL;
/*** RCC TypeDef ***/
typedef const struct
{
	STM32GXXX_RCC_PLL* pll;

	void (*inic)(void);
	void (*henable)(uint8_t hclock);
	void (*hselect)(uint8_t sysclk);
	void (*lenable)(uint8_t lclock);
	void (*lselect)(uint8_t lclock);
	void (*prescaler)(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2);
}STM32GXXX_RCC_HANDLER;

STM32GXXX_RCC_HANDLER* rcc(void);

/*** INTERRUPT HEADER ***/
void RCC_IRQHandler(void);

#endif

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

