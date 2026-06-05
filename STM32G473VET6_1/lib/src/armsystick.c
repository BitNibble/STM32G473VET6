/******************************************************************************
	STM32 XXX systick
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Update:   16012024
*******************************************************************************/
#include "armsystick.h"
#include "stm32g473vet6.h"

/******/
#define SYSTICK_ENABLE (1 << 0)
#define SYSTICK_TICKINT (1 << 1)
#define SYSTICK_CLKSOURCE (1 << 2)
/******/
static uint32_t systick_us = 0;
static uint32_t systick_10us = 0;
static uint32_t systick_100us = 0;
static uint32_t systick_ms = 0;
volatile uint32_t DelayCounter_0 = 0;
/******/
static inline uint32_t get_systick_clk(void)
{
    return (SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) ? get_hclk() : (get_hclk() / 8U);
}
static inline uint32_t calc_tick(uint32_t systick_clock, uint32_t div)
{
    uint32_t tmp = systick_clock / div;
    return (tmp > 0U) ? (tmp - 1U) : 70U;
}
void delay_Configure(void)
{
	uint32_t systick_clock = get_systick_clk();
    systick_us    = calc_tick(systick_clock, 1000000U);
    systick_10us  = calc_tick(systick_clock, 100000U);
    systick_100us = calc_tick(systick_clock, 10000U);
    systick_ms    = calc_tick(systick_clock, 1000U);
}
/*** SysTick Constants ***/
inline uint32_t get_systick_us(void)
{
	return systick_us;
}
inline uint32_t get_systick_10us(void)
{
	return systick_10us;
}
inline uint32_t get_systick_ms(void)
{
	return systick_ms;
}
/*** Count Polling ***/
void delayMiliseconds(unsigned int ms) {
    volatile unsigned int count = ms * get_systick_ms( );
    while (count--);
}
void delayMicroseconds(unsigned int us) {
    volatile unsigned int count = us * get_systick_us( );
    while (count--);
}
void delayAsmMicroseconds(unsigned int us) {
    // Adjust the loop count accordingly
    unsigned int count = us * get_systick_us( ); // Rough estimate for timing

    __asm volatile (
        "1: \n"                    // Label 1
        "subs %[count], %[count], #1 \n" // Decrement count
        "bne 1b \n"                // Branch to label 1 if count is not zero
        : [count] "+r" (count)     // Input/output operand
    );
}
/*** SysTick Polling ***/
void _delay_us(uint32_t us)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < us; );
}
void _delay_10us(uint32_t dez_us)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_10us( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < dez_us; );
}
void _delay_ms(uint32_t ms)
{
	SysTick->CTRL &= (uint32_t) ~SYSTICK_ENABLE;
	SysTick->LOAD = get_systick_ms( );
	for( DelayCounter_0 = 0, SysTick->CTRL |= SYSTICK_ENABLE; DelayCounter_0 < ms; );
}
/*** SysTick Initializer ***/
void systick_inic(void)
{
	delay_Configure( );
	/******/
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SYSTICK_TICKINT | SYSTICK_CLKSOURCE);
	SysTick->CTRL |= SYSTICK_ENABLE;
}
/*** SysTick Helper ***/
void SysTick_Inc(void)
{
	DelayCounter_0++;
}
/**** Interrupt Handler ****/
void SysTick_Handler(void)
{
  DelayCounter_0++;
}

/******
Load does not accept values below 70
Note 'us' only work for high frequency clocks.
******/

/*** EOF ***/

