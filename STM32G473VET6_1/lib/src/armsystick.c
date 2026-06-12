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
static uint32_t systick_us = 0;
static uint32_t systick_10us = 0;
static uint32_t systick_100us = 0;
static uint32_t systick_ms = 0;
volatile uint32_t DelayCounter_0 = 0;
/******/
static inline uint32_t calc_tick(uint32_t div)
{
    uint32_t tmp = get_hclk() / div;
    return (tmp > 1U) ? (tmp - 1U) : 1U;
}
void systick_Configure(void)
{
    systick_us    = calc_tick(1000000U);
    systick_10us  = calc_tick(100000U);
    systick_100us = calc_tick(10000U);
    systick_ms    = calc_tick(1000U);
}
/*** SysTick Constants ***/
uint32_t get_systick_us(void)
{
	return systick_us;
}
uint32_t get_systick_10us(void)
{
	return systick_10us;
}
uint32_t get_systick_ms(void)
{
	return systick_ms;
}
/*** SysTick Polling ***/
void _delay_us(uint32_t us)
{
    SysTick->CTRL = 0;

    SysTick->LOAD = get_systick_us();
    SysTick->VAL  = 0U;

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;

    for (uint32_t i = 0; i < us; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U);
    }

    SysTick->CTRL = 0;
}
void _delay_10us(uint32_t dez_us)
{
    SysTick->CTRL = 0;

    SysTick->LOAD = get_systick_10us();
    SysTick->VAL  = 0U;

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;

    for (uint32_t i = 0; i < dez_us; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U);
    }

    SysTick->CTRL = 0;
}

void _delay_ms(uint32_t ms)
{
    SysTick->CTRL = 0;

    SysTick->LOAD = get_systick_ms();
    SysTick->VAL  = 0U;

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_ENABLE_Msk;

    for (uint32_t i = 0; i < ms; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U);
    }

    SysTick->CTRL = 0;
}

void systick_inic(void)
{
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
  //HAL_IncTick(); // Updates the global time base
}

/*** EOF ***/

