/************************************************************************
	74HC595
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: 74HC595
Date:     25/10/2020
Comment:
	tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RET
************************************************************************/
#ifndef _74HC595_H_
	#define _74HC595_H_

/*** File Library ***/
#include <inttypes.h>
/*** Global Constant & Macro ***/
#define STM32F4XXX

#ifdef STM32F4XXX
	#define IO_var uint32_t
#else
	#define IO_var uint8_t
#endif
/*** File TypeDef ***/
typedef struct{
	uint8_t HC595_datapin;
	uint8_t HC595_clkpin;
	uint8_t HC595_outpin;
	volatile IO_var *hc595_DDR;
	volatile IO_var *hc595_PORT;
}hc595_par;
/*** 74HC595 TypeDef ***/
typedef struct
{
	hc595_par par;
	/******/
	void (*shift_bit)(hc595_par* par, uint8_t state);
	void (*shift_ibyte)(hc595_par* par, uint8_t byte);
	void (*shift_byte)(hc595_par* par, uint8_t byte);
	void (*ibyte)(hc595_par* par, uint8_t byte);
	void (*byte)(hc595_par* par, uint8_t byte);
	void (*out)(hc595_par* par);
}HC595_Handler;

HC595_Handler hc595_enable(volatile IO_var *ddr, volatile IO_var *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin);

#endif

/***EOF***/

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

