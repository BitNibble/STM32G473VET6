/******************************************************************************
	stm32x_gpio.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*******************************************************************************/
#include "stm32x_gpio.h"

#ifndef TWO
	#define TWO 2UL
#endif
#ifndef NIBBLE_BITS
	#define NIBBLE_BITS 4UL
#endif
#ifndef WORD_BITS
	#define WORD_BITS 16UL
#endif
#ifndef DWORD_BITS
	#define DWORD_BITS 32UL
#endif

void GPIO_clock(GPIO_TypeDef* GPIO, uint8_t enable)
{
    uint32_t mask = 0;

    if (GPIO == GPIOA)      mask = RCC_AHB2ENR_GPIOAEN;
    else if (GPIO == GPIOB) mask = RCC_AHB2ENR_GPIOBEN;
    else if (GPIO == GPIOC) mask = RCC_AHB2ENR_GPIOCEN;
    else if (GPIO == GPIOD) mask = RCC_AHB2ENR_GPIODEN;
    else if (GPIO == GPIOE) mask = RCC_AHB2ENR_GPIOEEN;
    else if (GPIO == GPIOF) mask = RCC_AHB2ENR_GPIOFEN;
#ifdef GPIOG
    else if (GPIO == GPIOG) mask = RCC_AHB2ENR_GPIOGEN;
#endif
#ifdef GPIOH
    else if (GPIO == GPIOH) mask = RCC_AHB2ENR_GPIOHEN;
#endif
    else return;

    if (enable)
        RCC->AHB2ENR |= mask;
    else
    	RCC->AHB2ENR &= ~mask;
}

void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = pin * BLOCK_SIZE;

		uint32_t temp = GPIO->MODER;
		temp &= ~(BLOCK << Pos);
		temp |= ((uint32_t)mode << Pos);
		GPIO->MODER = temp;
	}
}

void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype )
{
    if(pin < WORD_BITS && otype < TWO){
        uint32_t temp = GPIO->OTYPER;
    	temp &= ~(1UL << pin);
    	temp |= ( (uint32_t)otype << pin );
    	GPIO->OTYPER = temp;
    }
}

void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed )
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = (pin * BLOCK_SIZE);

		uint32_t temp = GPIO->OSPEEDR;
		temp &= ~( BLOCK << Pos );
		temp |= ( (uint32_t)ospeed << Pos );
		GPIO->OSPEEDR = temp;
	}
}

void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd )
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = (pin * BLOCK_SIZE);

		uint32_t temp = GPIO->PUPDR;
		temp &= ~( BLOCK << Pos );
		temp |= ( (uint32_t)pupd << Pos );
		GPIO->PUPDR = temp;
	}
}

void GPIO_hmoder( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t mode )
{
	if(mode < NIBBLE_BITS) {
		uint32_t hmoder = GPIO->MODER;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for (uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				uint8_t Pos = pin * BLOCK_SIZE;
				hmoder &= ~(BLOCK << Pos);
				hmoder |= ((uint32_t)mode << Pos);
			}
		}
		GPIO->MODER = hmoder;
	}
}

void GPIO_hotype( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t otype )
{
	if(otype < TWO) {
		uint32_t hotype = GPIO->OTYPER;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if(hpin & (1UL << pin)) {
				hotype &= ~(1UL << pin);
				hotype |= ( (uint32_t)otype << pin );
			}
		}
		GPIO->OTYPER = hotype;
	}
}

void GPIO_hospeed( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t ospeed )
{
	if(ospeed < NIBBLE_BITS) {
		uint32_t hospeed = GPIO->OSPEEDR;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				uint8_t Pos = (pin * BLOCK_SIZE);
				hospeed &= ~( BLOCK << Pos );
				hospeed |= ( (uint32_t)ospeed << Pos );
			}
		}
		GPIO->OSPEEDR = hospeed;
	}
}

void GPIO_hpupd( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t pupd )
{
	if(pupd < NIBBLE_BITS){
		uint32_t hpupd = GPIO->PUPDR;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				const uint8_t Pos = (pin * BLOCK_SIZE);
				hpupd &= ~( BLOCK << Pos );
				hpupd |= ( (uint32_t)pupd << Pos );
			}
		}
		GPIO->PUPDR = hpupd;
	}
}

void GPIO_lck(GPIO_TypeDef* GPIO, uint16_t hpin)
{
    uint32_t tmp;

    GPIO->LCKR = hpin | (1UL << 16);
    GPIO->LCKR = hpin;
    GPIO->LCKR = hpin | (1UL << 16);

    tmp = GPIO->LCKR;
    (void)tmp;

    tmp = GPIO->LCKR;
    (void)tmp;
}

void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af )
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    	const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
    	const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
    	const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

    	if(index < TWO){
    	    uint32_t temp = GPIO->AFR[index];
    		temp &= ~( BLOCK << Pos );
    		temp |= ( ((uint32_t)af & BLOCK) << Pos );
    		GPIO->AFR[index] = temp;
    	}
	}
}

void GPIO_haf( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t af )
{
    if(af < WORD_BITS) {
        const uint8_t BLOCK_SIZE = NIBBLE_BITS;
        const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;

        // Cache both AFR array masks to run modifications locally before write back
        uint32_t hafr[2] = { GPIO->AFR[0], GPIO->AFR[1] };

        for(uint8_t pin = 0; pin < WORD_BITS; pin++)
        {
            if(hpin & (1UL << pin)) {
                const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
                const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

                hafr[index] &= ~( BLOCK << Pos );
                hafr[index] |= ( ((uint32_t)af & BLOCK) << Pos );
            }
        }

        // Atomic memory block write updates the physical GPIO hardware register layout
        GPIO->AFR[0] = hafr[0];
        GPIO->AFR[1] = hafr[1];
    }
}

static inline void SET_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    reg->BSRR = hpin;
}
static inline void CLEAR_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    // Cast hpin to 32-bit first, then safely shift into the upper 16 bits
    reg->BSRR = ((uint32_t)hpin << WORD_BITS);
}
static inline void TOGGLE_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    reg->ODR ^= hpin;
}
static inline void SET_pin(GPIO_TypeDef* reg, uint8_t pin) {
    // 1UL guarantees safe, unsigned 32-bit shifting
    reg->BSRR = (1UL << pin);
}
static inline void CLEAR_pin(GPIO_TypeDef* reg, uint8_t pin) {
    // Directly shift 1UL to its final destination in the upper BRy half (pin + 16)
    reg->BSRR = (1UL << (pin + WORD_BITS));
}

/*** DEV V-TABLE ***/
static GPIO_Handle gpio_setup = {
	.clock = GPIO_clock,
	.moder = GPIO_moder,
	.otype = GPIO_otype,
	.ospeed = GPIO_ospeed,
	.pupd = GPIO_pupd,
	.hmoder = GPIO_hmoder,
	.hotype = GPIO_hotype,
	.hospeed = GPIO_hospeed,
	.hpupd = GPIO_hpupd,
	.lck = GPIO_lck,
	.af = GPIO_af,
	.haf = GPIO_haf,
	.set_hpin = SET_hpin,
	.clear_hpin = CLEAR_hpin,
	.toggle_hpin = TOGGLE_hpin,
	.set_pin = SET_pin,
	.clear_pin = CLEAR_pin
};

GPIO_Handle* gpio(void) { return &gpio_setup; }

/*** EOF ***/

