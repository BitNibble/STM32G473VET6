/**********************************************************************
	L293D
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date    12/08/2025
**********************************************************************/
#include "l293d.h"
#include <stddef.h>

/*** Internal ***/
void l293d_en(L293D_par *par);
void l293d_dis(L293D_par *par);
void l293d_forward(L293D_par *par);
void l293d_reverse(L293D_par *par);
void l293d_stop(L293D_par *par);
/*** V-table ***/
static L293D_run run_setup = {
	.enable = l293d_en,
	.disable = l293d_dis,
	.forward = l293d_forward,
	.reverse = l293d_reverse,
	.stop = l293d_stop,
	.pwm_forward = NULL,
	.pwm_reverse = NULL,
	.pwm_stop = NULL
};
/*** Instance ***/
L293D_Handler l293d_enable(volatile IO_var *ddr, volatile IO_var *port, uint8_t pin1, uint8_t pin2, uint8_t en_pin) {
    L293D_Handler l293d = {
        .par = {
            .DDR = ddr,
            .PORT = port,
			.TIM_GPIO = GPIOA,
			.TIM = TIM3,
			.tim_af = 2,
            .pin1 = pin1,
            .pin2 = pin2,
            .en_pin = en_pin
        },
		.run = &run_setup
    };

	#if defined(STM32F4) || defined(STM32G4)
        *ddr &= ~((3 << (pin1 * 2)) | (3 << (pin2 * 2)) | (3 << (en_pin * 2)));
        *ddr |=  ((1 << (pin1 * 2)) | (1 << (pin2 * 2)) | (1 << (en_pin * 2)));
    #else
        *ddr |= ((1 << pin1) | (1 << pin2) | (1 << en_pin));
    #endif

    *port &= ~((1 << pin1) | (1 << pin2) | (1 << en_pin));

    GPIO_clock(l293d.par.TIM_GPIO, ONE);
    GPIO_moder(l293d.par.TIM_GPIO, 6, MODE_AF);
    GPIO_moder(l293d.par.TIM_GPIO, 7, MODE_AF);

    GPIO_af(l293d.par.TIM_GPIO, 6, l293d.par.tim_af); // AF2 -> TIM3_CH1
    GPIO_af(l293d.par.TIM_GPIO, 7, l293d.par.tim_af); // AF2 -> TIM3_CH2

    return l293d;
}

/*** Function ***/
void l293d_en(L293D_par *par) {
	*par->PORT |= (1 << par->en_pin);
}
void l293d_dis(L293D_par *par) {
	*par->PORT &= ~(1 << par->en_pin);
}
void l293d_forward(L293D_par *par) {
	*par->PORT |= (1 << par->pin1);
	*par->PORT &= ~(1 << par->pin2);
}
void l293d_reverse(L293D_par *par) {
	*par->PORT &= ~(1 << par->pin1);
	*par->PORT |= (1 << par->pin2);
}
void l293d_stop(L293D_par *par) {
	*par->PORT &= ~((1 << par->pin1) | (1 << par->pin2));
}

/***
void l293d_pwm_forward(...)
{
    CCR1 = 0;
    CCR2 = duty;
    set_pin(IN1);
}
Forward
TIM3->CCR1 = TIM3->ARR + ONE;   // IN1 permanently HIGH
TIM3->CCR2 = duty;        // IN2 PWM sink
Reverse
TIM3->CCR1 = duty;        // IN1 PWM sink
TIM3->CCR2 = TIM3->ARR + ONE;   // IN2 permanently HIGH

***/

/*** EOF ***/

