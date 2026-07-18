/************************************************************************
	TEMPLATE SYNTAX SINGLETON
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU (Highly optimizable)
Date:     02/07/2026
************************************************************************/
#ifndef TEMPLATE_SINGLETON_H
	#define TEMPLATE_SINGLETON_H
/*** LIBRARY ***/
#include "stm32g473vet6.h"
/*** SINGLETON PARAMETER ***/
typedef struct {
	GPIO_TypeDef* gpio;
	uint8_t af;
	uint8_t pin_1;
	uint8_t pin_2;
	uint8_t var_1;
	uint8_t var_2;
}singleton_par;
/*** SINGLETON GET ***/
typedef const struct {
	uint8_t (*get_1)(void);
	uint8_t (*get_2)(void);
}singleton_get;
/*** SINGLETON SET ***/
typedef const struct {
	void (*set_1)(uint8_t value);
	void (*set_2)(uint8_t value);
}singleton_set;
/*** SINGLETON V-TABLE ***/
typedef const struct {
	void (*init)(void);
	void (*proc_1)(void);
	void (*proc_2)(void);
	void (*func_1)(uint32_t a);
	void (*func_2)(uint32_t a,uint32_t b);
}singleton_run;
/*** SINGLETON CALLBACK ***/
typedef struct {
 void (*callback_1)(void);
 void (*callback_2)(void);
}singleton_irq;
/*** SINGLETON HANDLER ***/
typedef const struct {
	singleton_par* par;
	singleton_get* get;
	singleton_set* set;
	singleton_irq* irq;
	singleton_run* run;
}singleton_handler;
/*** SINGLETON ACCESSOR FUNCTION ***/
singleton_handler* singleton(void);
#endif

/*** EOF ***/

