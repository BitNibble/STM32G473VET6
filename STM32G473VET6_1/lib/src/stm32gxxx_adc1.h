/******************************************************************************
	STM32 GXXX ADC1
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-GXXX
Date: 02072026
*******************************************************************************/
#ifndef STM32GXXXADC1_H
	#define STM32GXXXADC1_H

/*** LIBRARY ***/
#include "stm32g473vet6.h"
#include "stm32xtool.h"

/*** adc1 PARAMETER ***/
typedef struct {
	uint8_t var_1;
	uint8_t var_2;
}adc1_par;
/*** adc1 CALLBACK ***/
typedef struct {
 void (*callback_1)(void);
 void (*callback_2)(void);
}adc1_irq;
/*** adc1 V-TABLE ***/
typedef const struct {
	void (*_init)(void);
	void (*_cal_single)(void);
	void (*_cal_differential)(void);
	void (*_enable)(void);
	int (*_disable)(void);
	void (*temp_init)(void);
	uint16_t (*temp_read_raw)(void);
	float (*temp_to_celsius)(uint16_t raw);
	float (*temp_read_celsius)(void);
}adc1_run;
/*** adc1 HANDLER ***/
typedef const struct {
	adc1_par* par;
	adc1_irq* irq;
	adc1_run* run;
}adc1_handler;
/*** ACCESSOR FUNCTION ***/
adc1_handler* adc1(void);

#endif
/*** EOF ***/

