/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     05062026
Comment:
	
*******************************************************************************/
#include "timer_irq.h"
#include "stm32_irq.h"
#include <stm32g4xx.h>

/********************************************************************
 * TIM1
 ********************************************************************/

void tim1_u_callback(void) {}
void tim1_cc1_callback(void) {}
void tim1_cc2_callback(void) {}
void tim1_cc3_callback(void) {}
void tim1_cc4_callback(void) {}
void tim1_trg_callback(void) {}
void tim1_brk_callback(void) {}
void tim1_brk2_callback(void) {}
void tim1_com_callback(void) {}
void tim1_rep_callback(void) {}
void tim1_dma_callback(void) {}

/********************************************************************
 * TIM8
 ********************************************************************/

void tim8_u_callback(void) {}
void tim8_cc1_callback(void) {}
void tim8_cc2_callback(void) {}
void tim8_cc3_callback(void) {}
void tim8_cc4_callback(void) {}
void tim8_trg_callback(void) {}
void tim8_brk_callback(void) {}
void tim8_com_callback(void) {}
void tim8_rep_callback(void) {}
void tim8_dma_callback(void) {}

/********************************************************************
 * TIM2–TIM5 (GENERAL PURPOSE)
 ********************************************************************/

void tim2_u_callback(void) {}
void tim2_cc1_callback(void) {}
void tim2_cc2_callback(void) {}
void tim2_cc3_callback(void) {}
void tim2_cc4_callback(void) {}

void tim3_u_callback(void) {}
void tim3_cc1_callback(void) {}
void tim3_cc2_callback(void) {}
void tim3_cc3_callback(void) {}
void tim3_cc4_callback(void) {}

void tim4_u_callback(void) {}
void tim4_cc1_callback(void) {}
void tim4_cc2_callback(void) {}
void tim4_cc3_callback(void) {}
void tim4_cc4_callback(void) {}

void tim5_u_callback(void) {}
void tim5_cc1_callback(void) {}
void tim5_cc2_callback(void) {}
void tim5_cc3_callback(void) {}
void tim5_cc4_callback(void) {}

/********************************************************************
 * TIM6–TIM7 (BASIC TIMERS)
 ********************************************************************/

void tim6_u_callback(void) {}
void tim7_u_callback(void) {}

/********************************************************************
 * TIM15–TIM17 (LOW POWER TIMERS)
 ********************************************************************/

void tim15_u_callback(void) {}
void tim16_u_callback(void) {}
void tim17_u_callback(void) {}

/********************************************************************
 * TIM20 (ADVANCED / HIGH RESOLUTION)
 ********************************************************************/

void tim20_u_callback(void) {}
void tim20_cc1_callback(void) {}
void tim20_cc2_callback(void) {}
void tim20_cc3_callback(void) {}
void tim20_cc4_callback(void) {}
void tim20_trg_callback(void) {}
void tim20_brk_callback(void) {}
void tim20_com_callback(void) {}
void tim20_rep_callback(void) {}
void tim20_dma_callback(void) {}

/********************************************************************
 * TIM1 (ADVANCED TIMER)
 ********************************************************************/
void TIM1_BRK_TIM15_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    /* Break */
    if (sr & TIM_SR_BIF)
    {
        CLEAR_BIT(TIM1->SR, TIM_SR_BIF);

        if (irq()->tim->tim1->break_event != NULL)
        {
            irq()->tim->tim1->break_event();
        }
        else
        {
            tim1_brk_callback();
        }
    }

    /* Break 2 (STM32G4 uses B2IF) */
    if (sr & TIM_SR_B2IF)
    {
        CLEAR_BIT(TIM1->SR, TIM_SR_B2IF);

        if (irq()->tim->tim1->break2 != NULL)
        {
            irq()->tim->tim1->break2();
        }
        else
        {
            tim1_brk2_callback();
        }
    }

    /* Commutation */
    if (sr & TIM_SR_COMIF)
    {
        CLEAR_BIT(TIM1->SR, TIM_SR_COMIF);

        if (irq()->tim->tim1->commutation != NULL)
        {
            irq()->tim->tim1->commutation();
        }
        else
        {
            tim1_com_callback();
        }
    }

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM1->SR, TIM_SR_UIF);

        if (irq()->tim->tim1->update != NULL)
        {
            irq()->tim->tim1->update();
        }
        else
        {
            tim1_u_callback();
        }
    }
}

void TIM1_UP_TIM16_IRQHandler(void)
{
    if (TIM1->SR & TIM_SR_UIF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_UIF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->update != NULL)
        {
            irq()->tim->tim1->update();
        }
        else
        {
            tim1_u_callback();
        }
    }
}

void TIM1_TRG_COM_TIM17_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    /* Trigger */
    if (sr & TIM_SR_TIF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_TIF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->trigger != NULL)
        {
            irq()->tim->tim1->trigger();
        }
        else
        {
            tim1_trg_callback();
        }
    }

    /* Commutation */
    if (sr & TIM_SR_COMIF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_COMIF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->commutation != NULL)
        {
            irq()->tim->tim1->commutation();
        }
        else
        {
            tim1_com_callback();
        }
    }
}

void TIM1_CC_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_CC1IF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->cc1 != NULL)
        {
            irq()->tim->tim1->cc1();
        }
        else
        {
            tim1_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_CC2IF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->cc2 != NULL)
        {
            irq()->tim->tim1->cc2();
        }
        else
        {
            tim1_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_CC3IF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->cc3 != NULL)
        {
            irq()->tim->tim1->cc3();
        }
        else
        {
            tim1_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
    	CLEAR_BIT(TIM1->SR, TIM_SR_CC4IF);

        /* Bus synchronization barrier */
        (void)TIM1->SR;

        if (irq()->tim->tim1->cc4 != NULL)
        {
            irq()->tim->tim1->cc4();
        }
        else
        {
            tim1_cc4_callback();
        }
    }
}

/********************************************************************
 * TIM8 (ADVANCED TIMER)
 ********************************************************************/
void TIM8_BRK_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    /* Break */
    if (sr & TIM_SR_BIF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_BIF);

        if (irq()->tim->tim8->break_event != NULL)
        {
            irq()->tim->tim8->break_event();
        }
        else
        {
            tim8_brk_callback();
        }
    }

    /* Commutation */
    if (sr & TIM_SR_COMIF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_COMIF);

        if (irq()->tim->tim8->commutation != NULL)
        {
            irq()->tim->tim8->commutation();
        }
        else
        {
            tim8_com_callback();
        }
    }
}

void TIM8_UP_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_UIF);

        if (irq()->tim->tim8->update != NULL)
        {
            irq()->tim->tim8->update();
        }
        else
        {
            tim8_u_callback();
        }
    }
}

void TIM8_TRG_COM_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    /* Trigger */
    if (sr & TIM_SR_TIF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_TIF);

        if (irq()->tim->tim8->trigger != NULL)
        {
            irq()->tim->tim8->trigger();
        }
        else
        {
            tim8_trg_callback();
        }
    }

    /* Commutation */
    if (sr & TIM_SR_COMIF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_COMIF);

        if (irq()->tim->tim8->commutation != NULL)
        {
            irq()->tim->tim8->commutation();
        }
        else
        {
            tim8_com_callback();
        }
    }
}

void TIM8_CC_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim8->cc1 != NULL)
        {
            irq()->tim->tim8->cc1();
        }
        else
        {
            tim8_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim8->cc2 != NULL)
        {
            irq()->tim->tim8->cc2();
        }
        else
        {
            tim8_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim8->cc3 != NULL)
        {
            irq()->tim->tim8->cc3();
        }
        else
        {
            tim8_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM8->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim8->cc4 != NULL)
        {
            irq()->tim->tim8->cc4();
        }
        else
        {
            tim8_cc4_callback();
        }
    }
}

/********************************************************************
 * TIM2–TIM5 (GENERAL PURPOSE TIMERS)
 ********************************************************************/
void TIM2_IRQHandler(void)
{
    uint32_t sr = TIM2->SR;

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM2->SR, TIM_SR_UIF);

        if (irq()->tim->tim2->update != NULL)
        {
            irq()->tim->tim2->update();
        }
        else
        {
            tim2_u_callback();
        }
    }

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM2->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim2->cc1 != NULL)
        {
            irq()->tim->tim2->cc1();
        }
        else
        {
            tim2_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM2->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim2->cc2 != NULL)
        {
            irq()->tim->tim2->cc2();
        }
        else
        {
            tim2_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM2->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim2->cc3 != NULL)
        {
            irq()->tim->tim2->cc3();
        }
        else
        {
            tim2_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM2->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim2->cc4 != NULL)
        {
            irq()->tim->tim2->cc4();
        }
        else
        {
            tim2_cc4_callback();
        }
    }
}

void TIM3_IRQHandler(void)
{
    uint32_t sr = TIM3->SR;

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_UIF);

        if (irq()->tim->tim3->update != NULL)
        {
            irq()->tim->tim3->update();
        }
        else
        {
            tim3_u_callback();
        }
    }

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim3->cc1 != NULL)
        {
            irq()->tim->tim3->cc1();
        }
        else
        {
            tim3_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim3->cc2 != NULL)
        {
            irq()->tim->tim3->cc2();
        }
        else
        {
            tim3_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim3->cc3 != NULL)
        {
            irq()->tim->tim3->cc3();
        }
        else
        {
            tim3_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim3->cc4 != NULL)
        {
            irq()->tim->tim3->cc4();
        }
        else
        {
            tim3_cc4_callback();
        }
    }
}

void TIM4_IRQHandler(void)
{
    uint32_t sr = TIM4->SR;

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM4->SR, TIM_SR_UIF);

        if (irq()->tim->tim4->update != NULL)
        {
            irq()->tim->tim4->update();
        }
        else
        {
            tim4_u_callback();
        }
    }

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM4->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim4->cc1 != NULL)
        {
            irq()->tim->tim4->cc1();
        }
        else
        {
            tim4_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM4->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim4->cc2 != NULL)
        {
            irq()->tim->tim4->cc2();
        }
        else
        {
            tim4_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM4->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim4->cc3 != NULL)
        {
            irq()->tim->tim4->cc3();
        }
        else
        {
            tim4_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM4->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim4->cc4 != NULL)
        {
            irq()->tim->tim4->cc4();
        }
        else
        {
            tim4_cc4_callback();
        }
    }
}

void TIM5_IRQHandler(void)
{
    uint32_t sr = TIM5->SR;

    /* Update */
    if (sr & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM5->SR, TIM_SR_UIF);

        if (irq()->tim->tim5->update != NULL)
        {
            irq()->tim->tim5->update();
        }
        else
        {
            tim5_u_callback();
        }
    }

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM5->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim5->cc1 != NULL)
        {
            irq()->tim->tim5->cc1();
        }
        else
        {
            tim5_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM5->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim5->cc2 != NULL)
        {
            irq()->tim->tim5->cc2();
        }
        else
        {
            tim5_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM5->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim5->cc3 != NULL)
        {
            irq()->tim->tim5->cc3();
        }
        else
        {
            tim5_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM5->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim5->cc4 != NULL)
        {
            irq()->tim->tim5->cc4();
        }
        else
        {
            tim5_cc4_callback();
        }
    }
}

/********************************************************************
 * TIM6–TIM7 (BASIC TIMERS)
 ********************************************************************/
void TIM6_IRQHandler(void)
{
    if (TIM6->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM6->SR, TIM_SR_UIF);

        if (irq()->tim->tim6->update != NULL)
        {
            irq()->tim->tim6->update();
        }
        else
        {
            tim6_u_callback();
        }
    }
}

void TIM7_IRQHandler(void)
{
    if (TIM7->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM7->SR, TIM_SR_UIF);

        if (irq()->tim->tim7->update != NULL)
        {
            irq()->tim->tim7->update();
        }
        else
        {
            tim7_u_callback();
        }
    }
}

/********************************************************************
 * TIM15–TIM17 (LOW POWER TIMERS)
 ********************************************************************/
void TIM15_IRQHandler(void)
{
    if (TIM15->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM15->SR, TIM_SR_UIF);

        if (irq()->tim->tim15->update != NULL)
        {
            irq()->tim->tim15->update();
        }
        else
        {
            tim15_u_callback();
        }
    }
}

void TIM16_IRQHandler(void)
{
    if (TIM16->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM16->SR, TIM_SR_UIF);

        if (irq()->tim->tim16->update != NULL)
        {
            irq()->tim->tim16->update();
        }
        else
        {
            tim16_u_callback();
        }
    }
}

void TIM17_IRQHandler(void)
{
    if (TIM17->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM17->SR, TIM_SR_UIF);

        if (irq()->tim->tim17->update != NULL)
        {
            irq()->tim->tim17->update();
        }
        else
        {
            tim17_u_callback();
        }
    }
}

/********************************************************************
 * TIM20 (ADVANCED TIMER - G473)
 ********************************************************************/
void TIM20_UP_IRQHandler(void)
{
    if (TIM20->SR & TIM_SR_UIF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_UIF);

        if (irq()->tim->tim20->update != NULL)
        {
            irq()->tim->tim20->update();
        }
        else
        {
            tim20_u_callback();
        }
    }
}

void TIM20_CC_IRQHandler(void)
{
    uint32_t sr = TIM20->SR;

    /* Capture / Compare 1 */
    if (sr & TIM_SR_CC1IF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_CC1IF);

        if (irq()->tim->tim20->cc1 != NULL)
        {
            irq()->tim->tim20->cc1();
        }
        else
        {
            tim20_cc1_callback();
        }
    }

    /* Capture / Compare 2 */
    if (sr & TIM_SR_CC2IF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_CC2IF);

        if (irq()->tim->tim20->cc2 != NULL)
        {
            irq()->tim->tim20->cc2();
        }
        else
        {
            tim20_cc2_callback();
        }
    }

    /* Capture / Compare 3 */
    if (sr & TIM_SR_CC3IF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_CC3IF);

        if (irq()->tim->tim20->cc3 != NULL)
        {
            irq()->tim->tim20->cc3();
        }
        else
        {
            tim20_cc3_callback();
        }
    }

    /* Capture / Compare 4 */
    if (sr & TIM_SR_CC4IF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_CC4IF);

        if (irq()->tim->tim20->cc4 != NULL)
        {
            irq()->tim->tim20->cc4();
        }
        else
        {
            tim20_cc4_callback();
        }
    }
}

void TIM20_TRG_IRQHandler(void)
{
    if (TIM20->SR & TIM_SR_TIF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_TIF);

        if (irq()->tim->tim20->trigger != NULL)
        {
            irq()->tim->tim20->trigger();
        }
        else
        {
            tim20_trg_callback();
        }
    }
}

void TIM20_BRK_IRQHandler(void)
{
    if (TIM20->SR & TIM_SR_BIF)
    {
        CLEAR_BIT(TIM20->SR, TIM_SR_BIF);

        if (irq()->tim->tim20->break_event != NULL)
        {
            irq()->tim->tim20->break_event();
        }
        else
        {
            tim20_brk_callback();
        }
    }
}

/*** EOF ***/

