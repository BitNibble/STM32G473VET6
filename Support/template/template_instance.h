/************************************************************************
	TEMPLATE SYNTAX MULTI INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU (Highly optimizable)
Date:     02/07/2026
************************************************************************/
#ifndef TEMPLATE_INSTANCE_H
	#define TEMPLATE_INSTANCE_H
/*** LIBRARY ***/
#include "stm32g473vet6.h"
/*** INSTANCE PARAMETER ***/
typedef struct {
	GPIO_TypeDef* gpio;
	uint8_t af;
	uint8_t var_1;
	uint8_t var_2;
	void* handler;
}instance_par;
/*** INSTANCE V-TABLE ***/
typedef const struct {
	void (*init)(instance_par* par);
	void (*proc_1)(instance_par* par);
	void (*proc_2)(instance_par* par);
	void (*func_1)(instance_par* par,uint32_t a);
	void (*func_2)(instance_par* par,uint32_t a,uint32_t b);
}instance_run;
/*** INSTANCE HANDLER ***/
typedef struct {
	instance_par par;
	instance_run* run;
}instance_handler;
/*** INSTANCE INITIALIZE ***/
instance_handler instance_enable(void);
#endif

/*** EOF ***/

