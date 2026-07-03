/************************************************************************
	TEMPLATE MULTI INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#ifndef TEMPLATE_INSTANCE_H
	#define TEMPLATE_INSTANCE_H
/*** LIBRARY ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
/*** INSTANCE PARAMETER ***/
typedef struct {
	uint8_t var_1;
	uint8_t var_2;
}instance_par;
/*** INSTANCE CALLBACK ***/
typedef struct {
 void (*callback_1)(void);
 void (*callback_2)(void);
}instance_irq;
/*** INSTANCE V-TABLE ***/
typedef const struct {
	void (*proc_1)(instance_par* par);
	void (*proc_2)(instance_par* par);
	void (*func_1)(instance_par* par,uint32_t a);
	void (*func_2)(instance_par* par,uint32_t a,uint32_t b);
}instance_run;
/*** INSTANCE HANDLER ***/
typedef struct {
	instance_par par;
	instance_irq irq;
	instance_run* run;
}instance_handler;
/*** INSTANCE INITIALIZE ***/
instance_handler instance_enable(instance_par par);
#endif
/*** EOF ***/

