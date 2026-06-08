/************************************************************************
	ARMFUNCTION
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     18062023
Update:   07012024
Comment:
	Tested ->  Atemga128, Atmega328, Atmega32U4, Atmega324, Atmega8535, Atmega88, STM32F446RE
	Very Stable
************************************************************************/
#ifndef _ARMFUNCTION_H_
	#define _ARMFUNCTION_H_

/*** Global Library ***/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/*** Global Define & Macro ***/
#define FUNCSTRSIZE 33
/*** Typedef ***/
typedef struct {
    unsigned int Numerator;   // The numerator of the fraction
    unsigned int Denominator; // The denominator of the fraction
    unsigned int Quotient;    // The integer part of the real number
    unsigned int Remainder;   // The remainder part after division
    unsigned int Precision;   // The number of decimal points
    double Number;            // The input number
    double Fpart;             // The fractional part as a double
    int sign;                 // The sign of the number (-1 for negative, 1 for positive)
} RealNum_TypeDef;

/*** PROCEDURE & FUNCTION TypeDef ***/
typedef struct
{
	// PROTOTYPES VTABLE
	/******/
	uint16_t (*SwapByte)(uint16_t num);
	/******/
	unsigned int (*power)(unsigned int x, unsigned int y);
	RealNum_TypeDef (*divide)(int numerator, int denominator);
	RealNum_TypeDef (*realnumber)(double real, unsigned int decimal);
	int (*stringlength)(const char string[]);
	void (*reverse)(char* str);
	unsigned int (*mayia)(unsigned int xi, unsigned int xf, uint8_t nbits);
	void (*swap)(long *px, long *py);
	void (*copy)(char to[], const char from[], size_t to_size);
	void (*squeeze)(char s[], char c);
	void (*shellsort)(int v[], int n);
	char* (*resizestr)(char *string, int size);
	int (*trim)(char s[]);
	/******/
	uint8_t (*bcd2dec)(uint8_t num);
	uint8_t (*dec2bcd)(uint8_t num);
	char* (*dectohex)(int32_t num);
	uint8_t (*bcd2bin)(uint8_t val);
	int (*twocomptoint8bit)(int twoscomp);
	int (*twocomptoint10bit)(int twoscomp);
	int (*twocomptointnbit)(int twoscomp, uint8_t nbits);
	/******/
	int (*format_string)(char *buffer, size_t size, const char *format, ...);
	char* (*print_binary)(unsigned int n_bits, unsigned int number);
	/*******/
	char* (*i16toa)(int16_t n);
	char* (*ui16toa)(uint16_t n);
	char* (*i32toa)(int32_t n);
	char* (*ui32toa)(uint32_t n);
	char* (*ftoa)(double num, unsigned int decimal);
	/*******/
	int (*strToInt)(const char string[]);
	/*******/
	long (*trimmer)(long x, long in_min, long in_max, long out_min, long out_max);
	int (*pmax)(int a1, int a2);
	int (*gcd_v1)(uint32_t a, uint32_t b);
	long (*gcd_v2)(long a, long b);
	void (*trim_whitespace)(char* str);
	/******/
	int (*tokenize_string)(char *input, char *tokens[], int max_tokens, const char *delimiters);
	void (*nullify_last_n_chars)(char *str, int n);
	/******/
	uint32_t (*triggerA)(uint32_t hllh_io, uint8_t pin, uint32_t counter);
	uint32_t (*triggerB)(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
	uint32_t (*value)(void);
}FUNC_Handler;

const FUNC_Handler* func(void);

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

