/**********************************************************************
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4 Family
Date:     21062026
**********************************************************************/
#ifndef TIM1_DRIVER_H
#define TIM1_DRIVER_H

#include "stm32g473vet6.h"

typedef enum {
    TIM1_CH1 = 0,
    TIM1_CH2,
    TIM1_CH3,
    TIM1_CH4
} tim1_ch_t;

typedef enum {
    PWM_MODE_1 = 6,
    PWM_MODE_2 = 7
} pwm_mode_t;

typedef enum {
    IC_RISING  = 0,
    IC_FALLING = 1,
    IC_BOTH    = 2
} ic_edge_t;

typedef struct {
	uint16_t prescaler;
	uint32_t autoreload;
} tim1_par;

typedef const struct {
	void (*init_by_ticks)(uint16_t prescaler, uint32_t autoreload);
	void (*init_by_freq)(uint16_t prescaler, uint32_t target_freq_hz);
	void (*clock_enable)(void);
	void (*clock_disable)(void);
	void (*nvic_u_enable)(uint8_t priority);
	void (*nvic_u_disable)(void);
	void (*nvic_t_enable)(uint8_t priority);
	void (*nvic_t_disable)(void);
	void (*nvic_cc_enable)(uint8_t priority);
	void (*nvic_cc_disable)(void);
	void (*start)(void);
	void (*stop)(void);
	void (*config_pwm)(tim1_ch_t ch, pwm_mode_t mode, uint32_t pulse_width);
	void (*enable_complementary)(tim1_ch_t ch, uint8_t enable_main, uint8_t enable_comp);
	void (*config_deadtime)(uint8_t deadtime_value);
	void (*set_pulse)(tim1_ch_t ch, uint32_t pulse_width);
	void (*config_capture)(tim1_ch_t ch, ic_edge_t edge);
	uint32_t (*get_capture)(tim1_ch_t ch);
} tim1_run;

typedef struct {
    void (*b)(void);
    void (*u)(void);
    void (*t)(void);
    void (*cc1)(void);
    void (*cc2)(void);
    void (*cc3)(void);
    void (*cc4)(void);
} tim1_irq;

typedef const struct {
	tim1_par* par;
	tim1_run* run;
    tim1_irq* irq;
} TIM1_Handler;

TIM1_Handler* tim1(void);

#endif

