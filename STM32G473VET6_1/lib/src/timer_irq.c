/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     05106026
Comment:
	
*******************************************************************************/
/***************************************************
    STM32G473 TIMER IRQ SOURCE (FIXED CMSIS)
***************************************************/

#include "timer_irq.h"
#include "stm32g4xx.h"

/********************************************************************
 * HELPERS
 ********************************************************************/
#define CLEAR_FLAG(REG, MASK)   ((REG) &= ~(MASK))

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

    if (sr & TIM_SR_BIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_BIF);
        tim1_brk_callback();
    }

    /* STM32G4 uses B2IF (NOT BK2IF) */
    if (sr & TIM_SR_B2IF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_B2IF);
        tim1_brk2_callback();
    }

    if (sr & TIM_SR_COMIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_COMIF);
        tim1_com_callback();
    }

    if (sr & TIM_SR_UIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_UIF);
        tim1_u_callback();
    }
}

void TIM1_UP_TIM16_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    if (sr & TIM_SR_UIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_UIF);
        tim1_u_callback();
    }
}

void TIM1_TRG_COM_TIM17_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    if (sr & TIM_SR_TIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_TIF);
        tim1_trg_callback();
    }

    if (sr & TIM_SR_COMIF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_COMIF);
        tim1_com_callback();
    }
}

void TIM1_CC_IRQHandler(void)
{
    uint32_t sr = TIM1->SR;

    if (sr & TIM_SR_CC1IF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_CC1IF);
        tim1_cc1_callback();
    }

    if (sr & TIM_SR_CC2IF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_CC2IF);
        tim1_cc2_callback();
    }

    if (sr & TIM_SR_CC3IF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_CC3IF);
        tim1_cc3_callback();
    }

    if (sr & TIM_SR_CC4IF) {
        CLEAR_FLAG(TIM1->SR, TIM_SR_CC4IF);
        tim1_cc4_callback();
    }
}

/********************************************************************
 * TIM8 (ADVANCED TIMER)
 ********************************************************************/
void TIM8_BRK_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    if (sr & TIM_SR_BIF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_BIF);
        tim8_brk_callback();
    }

    if (sr & TIM_SR_COMIF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_COMIF);
        tim8_com_callback();
    }
}

void TIM8_UP_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    if (sr & TIM_SR_UIF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_UIF);
        tim8_u_callback();
    }
}

void TIM8_TRG_COM_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    if (sr & TIM_SR_TIF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_TIF);
        tim8_trg_callback();
    }

    if (sr & TIM_SR_COMIF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_COMIF);
        tim8_com_callback();
    }
}

void TIM8_CC_IRQHandler(void)
{
    uint32_t sr = TIM8->SR;

    if (sr & TIM_SR_CC1IF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_CC1IF);
        tim8_cc1_callback();
    }

    if (sr & TIM_SR_CC2IF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_CC2IF);
        tim8_cc2_callback();
    }

    if (sr & TIM_SR_CC3IF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_CC3IF);
        tim8_cc3_callback();
    }

    if (sr & TIM_SR_CC4IF) {
        CLEAR_FLAG(TIM8->SR, TIM_SR_CC4IF);
        tim8_cc4_callback();
    }
}

/********************************************************************
 * TIM2–TIM5 (GENERAL PURPOSE TIMERS)
 ********************************************************************/
#define TIM_GP_HANDLER(TIMx, name) \
void name##_IRQHandler(void) \
{ \
    uint32_t sr = TIMx->SR; \
    \
    if (sr & TIM_SR_UIF) { \
        CLEAR_FLAG(TIMx->SR, TIM_SR_UIF); \
        name##_u_callback(); \
    } \
    if (sr & TIM_SR_CC1IF) { \
        CLEAR_FLAG(TIMx->SR, TIM_SR_CC1IF); \
        name##_cc1_callback(); \
    } \
    if (sr & TIM_SR_CC2IF) { \
        CLEAR_FLAG(TIMx->SR, TIM_SR_CC2IF); \
        name##_cc2_callback(); \
    } \
    if (sr & TIM_SR_CC3IF) { \
        CLEAR_FLAG(TIMx->SR, TIM_SR_CC3IF); \
        name##_cc3_callback(); \
    } \
    if (sr & TIM_SR_CC4IF) { \
        CLEAR_FLAG(TIMx->SR, TIM_SR_CC4IF); \
        name##_cc4_callback(); \
    } \
}

TIM_GP_HANDLER(TIM2, tim2)
TIM_GP_HANDLER(TIM3, tim3)
TIM_GP_HANDLER(TIM4, tim4)
TIM_GP_HANDLER(TIM5, tim5)

/********************************************************************
 * TIM6–TIM7 (BASIC TIMERS)
 ********************************************************************/
/*
void TIM6_DAC_IRQHandler(void)
{
    if (TIM6->SR & TIM_SR_UIF) {
        CLEAR_FLAG(TIM6->SR, TIM_SR_UIF);
        tim6_u_callback();
        tim_u_callback();
    }
}
*/

void TIM7_IRQHandler(void)
{
    if (TIM7->SR & TIM_SR_UIF) {
        CLEAR_FLAG(TIM7->SR, TIM_SR_UIF);
        tim7_u_callback();
    }
}

/********************************************************************
 * TIM15–TIM17 (LOW POWER TIMERS)
 ********************************************************************/
void TIM15_IRQHandler(void)
{
    if (TIM15->SR & TIM_SR_UIF) {
        CLEAR_FLAG(TIM15->SR, TIM_SR_UIF);
        tim15_u_callback();
    }
}

void TIM16_IRQHandler(void)
{
    if (TIM16->SR & TIM_SR_UIF) {
        CLEAR_FLAG(TIM16->SR, TIM_SR_UIF);
        tim16_u_callback();
    }
}

void TIM17_IRQHandler(void)
{
    if (TIM17->SR & TIM_SR_UIF) {
        CLEAR_FLAG(TIM17->SR, TIM_SR_UIF);
        tim17_u_callback();
    }
}

/********************************************************************
 * TIM20 (ADVANCED TIMER - G473)
 ********************************************************************/
void TIM20_UP_IRQHandler(void)
{
    uint32_t sr = TIM20->SR;

    if (sr & TIM_SR_UIF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_UIF);
        tim20_u_callback();
    }
}

void TIM20_CC_IRQHandler(void)
{
    uint32_t sr = TIM20->SR;

    if (sr & TIM_SR_CC1IF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_CC1IF);
        tim20_cc1_callback();
    }

    if (sr & TIM_SR_CC2IF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_CC2IF);
        tim20_cc2_callback();
    }

    if (sr & TIM_SR_CC3IF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_CC3IF);
        tim20_cc3_callback();
    }

    if (sr & TIM_SR_CC4IF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_CC4IF);
        tim20_cc4_callback();
    }
}

void TIM20_TRG_IRQHandler(void)
{
    if (TIM20->SR & TIM_SR_TIF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_TIF);
        tim20_trg_callback();
    }
}

void TIM20_BRK_IRQHandler(void)
{
    if (TIM20->SR & TIM_SR_BIF) {
        CLEAR_FLAG(TIM20->SR, TIM_SR_BIF);
        tim20_brk_callback();
    }
}

/*** EOF ***/

