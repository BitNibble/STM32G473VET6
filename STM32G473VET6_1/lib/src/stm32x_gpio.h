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
	void (*moder)( GPIO_TypeDef* GPIO, uint8_t mode, uint8_t pin );
	void (*otype)( GPIO_TypeDef* GPIO, uint8_t otype, uint8_t pin );
	void (*ospeed)( GPIO_TypeDef* GPIO, uint8_t ospeed, uint8_t pin );
	void (*pupd)( GPIO_TypeDef* GPIO, uint8_t pupd, uint8_t pin );
	void (*hmoder)( GPIO_TypeDef* GPIO, uint8_t mode, uint16_t hpin );
	void (*hotype)( GPIO_TypeDef* GPIO, uint8_t otype, uint16_t hpin );
	void (*hospeed)( GPIO_TypeDef* GPIO, uint8_t ospeed, uint16_t hpin );
	void (*hpupd)( GPIO_TypeDef* GPIO, uint8_t pupd, uint16_t hpin );
	void (*lck)(GPIO_TypeDef* GPIO, uint16_t hpin);
	void (*af)( GPIO_TypeDef* GPIO, uint8_t af, uint8_t pin );
	void (*haf)( GPIO_TypeDef* GPIO, uint8_t af, uint16_t hpin );
	void (*set_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*clear_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*toggle_hpin)(GPIO_TypeDef* reg, uint16_t hpin);
	void (*set_pin)(GPIO_TypeDef* reg, uint8_t pin);
	void (*clear_pin)(GPIO_TypeDef* reg, uint8_t pin);
} GPIO_Handle;

GPIO_Handle* gpio(void);

#endif

/*** EOF ***/

