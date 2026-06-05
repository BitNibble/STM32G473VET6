/************************************************************************
	EXPLODE
Author:   <sergio.salazar.santos@gmail.com>
License:  Free beer
Hardware: all
Date:     16032021
Comment:
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
#ifndef _EXPLODE_H_
	#define _EXPLODE_H_

#include <stdint.h>
#include <inttypes.h>

#define STM32F4XXX

#ifdef STM32F4XXX
	#define IO_var uint32_t
#else
	#define IO_var uint8_t
#endif

typedef struct {
	IO_var XI;
	IO_var XF;
	IO_var HH;
	IO_var LL;
	IO_var LH;
	IO_var HL;
}explode_par;

typedef struct {
	explode_par par;
	void (*update)(explode_par* par, IO_var x);
}EXPLODE_Handler;

EXPLODE_Handler EXPLODE_enable(void);

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

