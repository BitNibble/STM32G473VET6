/************************************************************************
	TEMPLATE SINGLETON
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#ifndef TEMPLATE_SINGLETON_H
	#define TEMPLATE_SINGLETON_H
/*** LIBRARY ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
/*** SINGLETON PARAMETER ***/
typedef struct {
	uint8_t var_1;
	uint8_t var_2;
}singleton_par;
/*** SINGLETON CALLBACK ***/
typedef struct {
 void (*callback_1)(void);
 void (*callback_2)(void);
}singleton_irq;
/*** SINGLETON V-TABLE ***/
typedef const struct {
	void (*config)(singleton_par par);
	void (*init)(void);
	void (*proc_1)(void);
	void (*proc_2)(void);
	void (*func_1)(uint32_t a);
	void (*func_2)(uint32_t a,uint32_t b);
}singleton_run;
/*** SINGLETON HANDLER ***/
typedef const struct {
	singleton_par* par;
	singleton_irq* irq;
	singleton_run* run;
}singleton_handler;
/*** ACCESSOR FUNCTION ***/
singleton_handler* singleton(void);
#endif
/*** EOF ***/

