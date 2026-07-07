/**********************************************************************
	L293D
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
Date    04/07/2026
	TIM3
CH1 - PA6 - M1.1 PWM Forward
CH2 - PA7 - M1.2 PWM Reverse
**********************************************************************/
#include "l293d.h"
#include <stddef.h>
#include "arm_systick.h"

/*** Function ***/
void l293d_en(L293D_par *par) {
	par->EN_GPIO->ODR |= 1 << par->en_pin;
}
void l293d_dis(L293D_par *par) {
	par->EN_GPIO->ODR &= ~(1 << par->en_pin);
}

// Fixed-speed shortcuts map directly onto the valid PWM timing logic
void l293d_forward(L293D_par *par) {
	l293d_en(par);
	par->TIM->CCR2 = par->TIM->ARR + ONE;
	par->TIM->CCR1 = 0; // ARR - ARR = 0 (100% full speed duty cycle)
}

void l293d_reverse(L293D_par *par) {
	l293d_en(par);
	par->TIM->CCR1 = par->TIM->ARR + ONE;
	par->TIM->CCR2 = 0; // ARR - ARR = 0 (100% full speed duty cycle)
}

// Forward with variable speed (0 to ARR) using +V reference locking
void l293d_pwm_forward(L293D_par *par, uint16_t speed) {
	l293d_en(par);
    if (speed > par->TIM->ARR) {
        speed = par->TIM->ARR; // Clamp safety
    }
    par->TIM->CCR2 = par->TIM->ARR + ONE;  // Lock CH2 HIGH (+V reference) [1]
    par->TIM->CCR1 = par->TIM->ARR - speed; // Invert duty cycle so higher speed = more LOW time [1]
}

// Reverse with variable speed (0 to ARR) using +V reference locking
void l293d_pwm_reverse(L293D_par *par, uint16_t speed) {
	l293d_en(par);
    if (speed > par->TIM->ARR) {
        speed = par->TIM->ARR; // Clamp safety
    }
    par->TIM->CCR1 = par->TIM->ARR + ONE;  // Lock CH1 HIGH (+V reference) [1]
    par->TIM->CCR2 = par->TIM->ARR - speed; // Invert duty cycle so higher speed = more LOW time [1]
}

// PWM Stop using +V reference locking (Fast Hardware Brake)
void l293d_pwm_stop(L293D_par *par) {
    par->TIM->CCR1 = par->TIM->ARR + ONE;  // Lock CH1 HIGH (+V reference) [1]
    par->TIM->CCR2 = par->TIM->ARR + ONE;  // Lock CH2 HIGH (+V reference) [1]
    _delay_ms(500);
    l293d_dis(par);
}

void l293d_pwm_stop_coast(L293D_par *par) {
    // 1. Turn off the H-bridge outputs entirely (Motor freewheels/coasts)
    l293d_dis(par);
    // 2. Safely clear the timers
    par->TIM->CCR1 = 0;
    par->TIM->CCR2 = 0;
}

/*** V-table ***/
static L293D_run run_setup = {
	.enable = l293d_en,
	.disable = l293d_dis,
	.forward = l293d_forward,
	.reverse = l293d_reverse,
	.pwm_forward = l293d_pwm_forward,
	.pwm_reverse = l293d_pwm_reverse,
	.stop = l293d_pwm_stop,
	.stop_coast = l293d_pwm_stop_coast,
	.pwm_stop = l293d_pwm_stop,
	.pwm_stop_coast = l293d_pwm_stop_coast
};
/*** Instance ***/
L293D_Handler l293d_enable(GPIO_TypeDef *port, uint8_t en_pin) {
    L293D_Handler l293d = {
        .par = {
        	.EN_GPIO = port,
			.TIM_GPIO = GPIOA,
			.TIM = TIM3,
			.tim_af = 2,
			.tim_psc = 0,
			.tim_arr = 2181,
            .en_pin = en_pin
        },
		.run = &run_setup
    };
    dev()->run->gpio_clock(l293d.par.EN_GPIO, ONE);
    dev()->run->gpio_moder(l293d.par.EN_GPIO, l293d.par.en_pin, MODE_OUTPUT);

    dev()->run->gpio_clock(l293d.par.TIM_GPIO, ONE);
    dev()->run->gpio_moder(l293d.par.TIM_GPIO, 6, MODE_AF);
    dev()->run->gpio_moder(l293d.par.TIM_GPIO, 7, MODE_AF);

    dev()->run->gpio_af(l293d.par.TIM_GPIO, 6, l293d.par.tim_af); // AF2 -> TIM3_CH1
    dev()->run->gpio_af(l293d.par.TIM_GPIO, 7, l293d.par.tim_af); // AF2 -> TIM3_CH2

    dev()->run->gpio_hospeed(l293d.par.TIM_GPIO, (1 << 6) | (1 << 7), GPIO_SPEED_FREQ_HIGH);

    // Enable TIM3 Clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM3EN;
    // Set Frequency timing parameters
    l293d.par.TIM->PSC = l293d.par.tim_psc;
    l293d.par.TIM->ARR = l293d.par.tim_arr;
    // Configure Channel 1 (PA6) and Channel 2 (PA7) in PWM Mode 1
    // CCMR1 bits 4:6 for CH1, bits 12:14 for CH2. Also enable preload registers (bit 3 and 11).
    l293d.par.TIM->CCMR1 &= ~(TIM_CCMR1_OC1M | TIM_CCMR1_OC2M);
    l293d.par.TIM->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos) | TIM_CCMR1_OC1PE;
    l293d.par.TIM->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos) | TIM_CCMR1_OC2PE;
    // Initialize to +V reference brake state (Both HIGH = completely stopped)
    l293d.par.TIM->CCR1 = l293d.par.TIM->ARR + ONE;
    l293d.par.TIM->CCR2 = l293d.par.TIM->ARR + ONE;
    // Enable outputs in Capture/Compare Enable Register
    l293d.par.TIM->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);
    // Enable the main counter
    l293d.par.TIM->CR1 |= TIM_CR1_CEN;

    return l293d;
}

/*** EOF ***/

