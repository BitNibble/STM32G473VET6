/******************************************************************************
	STM32 GXXX ADC1
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-GXXX
Date: 02072026
*******************************************************************************/
#ifndef STM32GXXXADC1_H
	#define STM32GXXXADC1_H

/*** Libraries ***/
#include "stm32g473vet6.h"
#include "stm32xtool.h"

void _adc1_init(void);
void _adc1_cal_single(void);
void _adc1_cal_differential(void);
void _adc1_enable(void);
int _adc1_disable(void);

void adc1_temp_init(void);
uint16_t adc1_temp_read_raw(void);
float adc1_temp_to_celsius(uint16_t raw);
float adc1_temp_read_celsius(void);

#endif
/*** EOF ***/

