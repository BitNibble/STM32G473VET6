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
#define ONE 1
#define TWO 2
#define NIBBLE_BITS 4
#define BYTE_BITS 8
#define WORD_BITS 16
#define DWORD_BITS 32
#define QWORD_BITS 64

/*******************************************************************/
/***************************** ToolSet *****************************/
/*******************************************************************/
uint32_t _block_pos(uint32_t size_block, uint32_t block_n);
void set_reg(volatile uint32_t* reg, uint32_t hbits);
void clear_reg(volatile uint32_t* reg, uint32_t hbits);

uint32_t get_reg_field_value(uint32_t reg, uint32_t Msk, uint32_t Pos);
void set_reg_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData);
void write_reg_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
void set_reg_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);

uint32_t get_reg_block_value(uint32_t reg, uint8_t size_block, uint8_t Pos);
void write_reg_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
void set_reg_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);

uint32_t get_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos);
void set_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
/****************************************/
/*** NULL Check ***/
int isPtrNull(void* ptr);
int isCharPtrFlush(void* ptr);
/*** ADC ***/
float CalculateTemperature(uint16_t adc_value);
/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*execute)(void));
void ftdelayReset(uint8_t ID);

/*** EOF ***/

