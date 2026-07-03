/**********************************************************************
	L293D
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: ALL
Date:     12082025
**********************************************************************/
#ifndef L293D_H
	#define L293D_H

/*** LIBRARY ***/
#include "stm32g473vet6.h"
#include "stm32xtool.h"
#include <inttypes.h>

/*** Constant and Macro ***/
#if defined(STM32F4) || defined(STM32G4)
    #define IO_var uint32_t
#else
    #define IO_var uint8_t
#endif

/*** Parameter ***/
typedef struct {
    volatile IO_var *DDR;
    volatile IO_var *PORT;
    GPIO_TypeDef *TIM_GPIO;
    TIM_TypeDef *TIM;
    uint8_t tim_af;
    uint8_t pin1;
    uint8_t pin2;
    uint8_t en_pin;
} L293D_par;
/*** V-table ***/
typedef const struct {
	void (*enable)(L293D_par *par);
	void (*disable)(L293D_par *par);
	void (*forward)(L293D_par *par);
	void (*reverse)(L293D_par *par);
	void (*stop)(L293D_par *par);
	void (*pwm_forward)(L293D_par *par); // setup timer output mode and dir
	void (*pwm_reverse)(L293D_par *par); // setup timer output mode and dir
	void (*pwm_stop)(L293D_par *par); // disable timer output mode and ground outputs
} L293D_run;

/*** Handler ***/
typedef struct {
    L293D_par par;
    L293D_run* run;
} L293D_Handler;

L293D_Handler l293d_enable(volatile IO_var *ddr, volatile IO_var *port, uint8_t pin1, uint8_t pin2, uint8_t en_pin);

#endif

/*** Plug In Callback Examples ***
void pwm_forward(L293D_par *par){
	*par->PORT |= (1 << par->pin1);
	tc1->compoutmodeB(3);
}

void pwm_reverse(L293D_par *par){
	*par->PORT &= ~(1 << par->pin1);
	tc1->compoutmodeB(2);
}

void pwm_stop(L293D_par *par){
	tc1->compoutmodeA(0);
	tc1->compoutmodeB(0);
	*par->PORT &= ~(1 << par->pin1);
	*par->PORT &= ~(1 << par->pin2);
}
*********************************/

/*** EOF ***/
