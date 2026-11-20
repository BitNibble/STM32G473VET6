/******************************************************************************
	exti_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "stm32x_irq.h"
#include <stm32g4xx.h>

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR1 & EXTI_PR1_PIF0)
    {
        EXTI->PR1 = EXTI_PR1_PIF0;
        (void)EXTI->PR1;

        if (irq()->exti->line0 != NULL)
        {
            irq()->exti->line0();
        }
        else
        {
            exti_line0_callback();
        }
    }
}

void EXTI1_IRQHandler(void)
{
    if (EXTI->PR1 & EXTI_PR1_PIF1)
    {
        EXTI->PR1 = EXTI_PR1_PIF1;
        (void)EXTI->PR1;

        if (irq()->exti->line1 != NULL)
        {
            irq()->exti->line1();
        }
        else
        {
            exti_line1_callback();
        }
    }
}

void EXTI2_IRQHandler(void)
{
    if (EXTI->PR1 & EXTI_PR1_PIF2)
    {
        EXTI->PR1 = EXTI_PR1_PIF2;
        (void)EXTI->PR1;

        if (irq()->exti->line2 != NULL)
        {
            irq()->exti->line2();
        }
        else
        {
            exti_line2_callback();
        }
    }
}

void EXTI3_IRQHandler(void)
{
    if (EXTI->PR1 & EXTI_PR1_PIF3)
    {
        EXTI->PR1 = EXTI_PR1_PIF3;
        (void)EXTI->PR1;

        if (irq()->exti->line3 != NULL)
        {
            irq()->exti->line3();
        }
        else
        {
            exti_line3_callback();
        }
    }
}

void EXTI4_IRQHandler(void)
{
    if (EXTI->PR1 & EXTI_PR1_PIF4)
    {
        EXTI->PR1 = EXTI_PR1_PIF4;
        (void)EXTI->PR1;

        if (irq()->exti->line4 != NULL)
        {
            irq()->exti->line4();
        }
        else
        {
            exti_line4_callback();
        }
    }
}

void EXTI9_5_IRQHandler(void)
{
    uint32_t mask = (EXTI_PR1_PIF5 | EXTI_PR1_PIF6 | EXTI_PR1_PIF7 | EXTI_PR1_PIF8 | EXTI_PR1_PIF9);
    uint32_t pr = EXTI->PR1 & mask;

    if (pr != 0U)
    {
        EXTI->PR1 = pr;
        (void)EXTI->PR1;

        if (irq()->exti->line5_9 != NULL)
        {
            irq()->exti->line5_9();
        }
        else
        {
            exti_line5_9_callback();
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    uint32_t mask = (EXTI_PR1_PIF10 | EXTI_PR1_PIF11 | EXTI_PR1_PIF12 | EXTI_PR1_PIF13 | EXTI_PR1_PIF14 | EXTI_PR1_PIF15);
    uint32_t pr = EXTI->PR1 & mask;

    if (pr != 0U)
    {
        EXTI->PR1 = pr;
        (void)EXTI->PR1;

        if (irq()->exti->line10_15 != NULL)
        {
            irq()->exti->line10_15();
        }
        else
        {
            exti_line10_15_callback();
        }
    }
}

/*** EOF ***/
