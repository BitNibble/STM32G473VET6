/***************************************************
	STM32 TOOL
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
Update:   15/11/2025
****************************************************/
#pragma once

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Define & Macro ***/
#define ZERO 0
#define ONE 1UL
#define TWO 2UL
#define NIBBLE_BITS 4UL
#define BYTE_BITS 8UL
#define WORD_BITS 16UL
#define DWORD_BITS 32UL
#define QWORD_BITS 64UL

/*******************************************************************/
/***************************** ToolSet *****************************/
/*******************************************************************/
uint32_t _block_pos(uint32_t size_block, uint32_t block_n);
uint32_t _mask(uint32_t var, uint32_t Msk);
uint32_t _imask(uint32_t var, uint32_t Msk);

void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);

uint32_t get_field_value(uint32_t reg, uint32_t Msk, uint32_t Pos);
void write_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
void set_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
void set_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData);

uint32_t get_block_value(uint32_t reg, uint8_t size_block, uint8_t Pos);
void write_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
void set_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);

uint32_t get_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos);
void write_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
void set_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
/****************************************/
void increment(uint16_t* value, uint16_t min, uint16_t max);
uint8_t toggle(uint8_t n);
/*** NULL Check ***/
int isPtrNull(void* ptr);
int isCharPtrFlush(void* ptr);
/*** ADC ***/
float CalculateTemperature(uint16_t adc_value);
/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*init)(void), void (*term)(void));
void ftdelayReset(uint8_t ID);
void ftdelayTerm(uint8_t ID);

/*** EOF ***/

