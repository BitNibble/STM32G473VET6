/******************************************************************************
	STM32 XXX TIM IRQ
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32-XXX
Date:     05062026
Comment:
	
*******************************************************************************/
#ifndef TIMER_IRQ_H
	#define TIMER_IRQ_H

#include <stdint.h>

/********************************************************************
 * PER-TIMER INSTANCES (semantic routing layer)
 ********************************************************************/

/*** TIM1 ***/
__attribute__((weak)) void tim1_u_callback(void);
__attribute__((weak)) void tim1_cc1_callback(void);
__attribute__((weak)) void tim1_cc2_callback(void);
__attribute__((weak)) void tim1_cc3_callback(void);
__attribute__((weak)) void tim1_cc4_callback(void);
__attribute__((weak)) void tim1_trg_callback(void);
__attribute__((weak)) void tim1_brk_callback(void);
__attribute__((weak)) void tim1_brk2_callback(void);
__attribute__((weak)) void tim1_com_callback(void);
__attribute__((weak)) void tim1_rep_callback(void);
__attribute__((weak)) void tim1_dma_callback(void);

/*** TIM8 ***/
__attribute__((weak)) void tim8_u_callback(void);
__attribute__((weak)) void tim8_cc1_callback(void);
__attribute__((weak)) void tim8_cc2_callback(void);
__attribute__((weak)) void tim8_cc3_callback(void);
__attribute__((weak)) void tim8_cc4_callback(void);
__attribute__((weak)) void tim8_trg_callback(void);
__attribute__((weak)) void tim8_brk_callback(void);
__attribute__((weak)) void tim8_com_callback(void);
__attribute__((weak)) void tim8_rep_callback(void);
__attribute__((weak)) void tim8_dma_callback(void);

/*** TIM2–TIM5 (general purpose, full CC capable) ***/
__attribute__((weak)) void tim2_u_callback(void);
__attribute__((weak)) void tim2_cc1_callback(void);
__attribute__((weak)) void tim2_cc2_callback(void);
__attribute__((weak)) void tim2_cc3_callback(void);
__attribute__((weak)) void tim2_cc4_callback(void);

__attribute__((weak)) void tim3_u_callback(void);
__attribute__((weak)) void tim3_cc1_callback(void);
__attribute__((weak)) void tim3_cc2_callback(void);
__attribute__((weak)) void tim3_cc3_callback(void);
__attribute__((weak)) void tim3_cc4_callback(void);

__attribute__((weak)) void tim4_u_callback(void);
__attribute__((weak)) void tim4_cc1_callback(void);
__attribute__((weak)) void tim4_cc2_callback(void);
__attribute__((weak)) void tim4_cc3_callback(void);
__attribute__((weak)) void tim4_cc4_callback(void);

__attribute__((weak)) void tim5_u_callback(void);
__attribute__((weak)) void tim5_cc1_callback(void);
__attribute__((weak)) void tim5_cc2_callback(void);
__attribute__((weak)) void tim5_cc3_callback(void);
__attribute__((weak)) void tim5_cc4_callback(void);

/*** TIM6–TIM7 (basic timers) ***/
__attribute__((weak)) void tim6_u_callback(void);
__attribute__((weak)) void tim7_u_callback(void);

/*** TIM15–TIM17 (low power timers) ***/
__attribute__((weak)) void tim15_u_callback(void);
__attribute__((weak)) void tim16_u_callback(void);
__attribute__((weak)) void tim17_u_callback(void);

/*** TIM20 (advanced / high resolution) ***/
__attribute__((weak)) void tim20_u_callback(void);
__attribute__((weak)) void tim20_cc1_callback(void);
__attribute__((weak)) void tim20_cc2_callback(void);
__attribute__((weak)) void tim20_cc3_callback(void);
__attribute__((weak)) void tim20_cc4_callback(void);
__attribute__((weak)) void tim20_trg_callback(void);
__attribute__((weak)) void tim20_brk_callback(void);
__attribute__((weak)) void tim20_com_callback(void);
__attribute__((weak)) void tim20_rep_callback(void);
__attribute__((weak)) void tim20_dma_callback(void);

#endif

