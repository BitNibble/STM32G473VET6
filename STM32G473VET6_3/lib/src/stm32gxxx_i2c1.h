/************************************************************************
	STM32GXXX_I2C1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4
Date:     02/07/2026
************************************************************************/
#ifndef STM32GXXX_I2C1_H
	#define STM32GXXX_I2C1_H
/*** LIBRARY ***/
#include "stm32g473vet6.h"

#define PCF8563   0x51

/*** i2c1 PARAMETER ***/
typedef struct {
	GPIO_TypeDef* gpio;
	uint8_t af;
	uint8_t pin_1;
	uint8_t pin_2;
	uint8_t var_1;
	uint8_t var_2;
}i2c1_par;
/*** i2c1 GET ***/
typedef const struct {
	uint8_t (*get_1)(void);
	uint8_t (*get_2)(void);
}i2c1_get;
/*** i2c1 SET ***/
typedef const struct {
	void (*set_1)(uint8_t value);
	void (*set_2)(uint8_t value);
}i2c1_set;
/*** i2c1 V-TABLE ***/
typedef const struct {
	void (*init)(void);
	void (*proc_1)(void);
	void (*proc_2)(void);
	void (*func_1)(uint32_t a);
	void (*func_2)(uint32_t a,uint32_t b);
}i2c1_run;
/*** i2c1 CALLBACK ***/
typedef struct {
 void (*callback_1)(void);
 void (*callback_2)(void);
}i2c1_irq;
/*** i2c1 HANDLER ***/
typedef const struct {
	i2c1_par* par;
	i2c1_get* get;
	i2c1_set* set;
	i2c1_irq* irq;
	i2c1_run* run;
}i2c1_handler;
/*** i2c1 ACCESSOR FUNCTION ***/
i2c1_handler* i2c1(void);
#endif

/*** EOF ***/

