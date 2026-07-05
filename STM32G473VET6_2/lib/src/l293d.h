/**********************************************************************
	L293D
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
Date:     04/07/2026
	TIM3
CH1 - PA6 - M1.1 PWM Forward
CH2 - PA7 - M1.2 PWM Reverse
**********************************************************************/
#ifndef L293D_H
	#define L293D_H

/*** LIBRARY ***/
#include "stm32g473vet6.h"
#include "stm32xtool.h"
#include <inttypes.h>

/*** Parameter ***/
typedef struct {
	GPIO_TypeDef *EN_GPIO;
    GPIO_TypeDef *TIM_GPIO;
    TIM_TypeDef *TIM;
    uint8_t tim_af;
    uint16_t tim_psc;
    uint16_t tim_arr;
    uint8_t en_pin;
} L293D_par;
/*** V-table ***/
typedef const struct {
	void (*enable)(L293D_par *par);
	void (*disable)(L293D_par *par);
	void (*forward)(L293D_par *par);
	void (*reverse)(L293D_par *par);
	void (*pwm_forward)(L293D_par *par, uint16_t speed);
	void (*pwm_reverse)(L293D_par *par, uint16_t speed);
	void (*stop)(L293D_par *par);
	void (*stop_coast)(L293D_par *par);
	void (*pwm_stop)(L293D_par *par);
	void (*pwm_stop_coast)(L293D_par *par);
} L293D_run;

/*** Handler ***/
typedef struct {
    L293D_par par;
    L293D_run* run;
} L293D_Handler;

L293D_Handler l293d_enable(GPIO_TypeDef *port, uint8_t en_pin);

#endif

/*** EOF ***/

