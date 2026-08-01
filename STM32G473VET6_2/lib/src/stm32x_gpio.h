/******************************************************************************
	stm32x_gpio.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*******************************************************************************/
#ifndef STM32X_GPIO_H
	#define STM32X_GPIO_H

#include <stm32g4xx.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** DEV V-TABLE ***/
typedef const struct {
	void (*clock)(GPIO_TypeDef* GPIO, uint8_t enable);
	void (*moder)( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode );
	void (*otype)( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype );
	void (*ospeed)( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed );
	void (*pupd)( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd );
	void (*hmoder)( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t mode );
	void (*hotype)( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t otype );
	void (*hospeed)( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t ospeed );
	void (*hpupd)( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t pupd );
	void (*lck)(GPIO_TypeDef* GPIO, uint16_t hpin);
	void (*af)( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af );
	void (*haf)( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t af );
	void (*set_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*clear_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*toggle_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*set_pin)(GPIO_TypeDef* reg, uint8_t pin);
	void (*clear_pin)(GPIO_TypeDef* reg, uint8_t pin);
} GPIO_Handle;

GPIO_Handle* gpio(void);

#endif

/*** EOF ***/

