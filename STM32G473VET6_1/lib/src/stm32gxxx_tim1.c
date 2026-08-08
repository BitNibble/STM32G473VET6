/**********************************************************************
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4 Family
Date:     21062026
**********************************************************************/
#include "stm32gxxx_tim1.h"

static tim1_par t1_par = { // Default
	.prescaler = 119,
	.autoreload = 1999999
};

static void t1_clk_en(void) {
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_clk_di(void) {
    CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_init_by_ticks(uint16_t prescaler, uint32_t autoreload) {
    t1_clk_en();

    TIM1->PSC = prescaler;
    TIM1->ARR = autoreload;
    t1_par.prescaler = prescaler;
    t1_par.autoreload = autoreload;

    SET_BIT(TIM1->BDTR, TIM_BDTR_MOE);
    SET_BIT(TIM1->EGR, TIM_EGR_UG);
    CLEAR_BIT(TIM1->SR, TIM_SR_UIF);

    (void)TIM1->SR; // Sync barrier
}

static void t1_init_by_freq(uint16_t prescaler, uint32_t target_freq_hz) {
    // Query your dynamic clock system architecture to get exact bus metrics
    uint32_t tim_input_clk = dev()->get->timclk2();

    // Formula calculation logic layout: ARR = (TIM_CLK / ((PSC + 1) * Target_Freq)) - 1
    uint32_t clock_step = tim_input_clk / (prescaler + 1U);
    uint32_t calculated_arr = (clock_step / target_freq_hz) - 1U;

    t1_init_by_ticks(prescaler, calculated_arr);
    t1_par.prescaler = prescaler;
    t1_par.autoreload = calculated_arr;
}

void t1_init_freq(uint32_t target_freq_hz) {
	if (target_freq_hz == 0U) return;

	uint32_t tim_input_clk = dev()->get->timclk2();

	if (target_freq_hz > tim_input_clk) {
	    target_freq_hz = tim_input_clk; // Limita ao máximo do hardware
	}

	uint32_t best_psc = 0;
	uint32_t best_arr = 0;
	uint32_t min_error = 0xFFFFFFFF;

	// Se a diferença de precisão for menor que 1 Hz, priorizamos o maior ARR
	const uint32_t ERROR_TOLERANCE_HZ = 1U;

	for (uint32_t psc_test = 0; psc_test <= 65535U; psc_test++) {
	    // Usar uint64_t previne overflow em clocks muito altos acima de 4GHz
	    uint64_t denominator = (uint64_t)(psc_test + 1U) * target_freq_hz;

	    if (denominator > tim_input_clk) {
	        break;
	    }

	    uint32_t ideal_arr_plus_1 = (tim_input_clk + (denominator / 2U)) / denominator;
	    uint32_t arr_test = (ideal_arr_plus_1 > 0U) ? (ideal_arr_plus_1 - 1U) : 0U;

	    if (arr_test > 65535U) {
	        continue;
	    }

	    uint32_t actual_freq = tim_input_clk / ((psc_test + 1U) * (arr_test + 1U));
	    uint32_t error = (actual_freq > target_freq_hz) ? (actual_freq - target_freq_hz) : (target_freq_hz - actual_freq);

	    // CRITÉRIO DE ESCOLA:
	    // 1. Se o erro for estritamente menor, aceitamos logo.
	    // 2. Se o erro for equivalente (dentro da tolerância), mas o ARR for maior, trocamos para ter mais resolução.
	    if ((error < min_error) ||
	        ((error <= min_error + ERROR_TOLERANCE_HZ) && (arr_test > best_arr))) {

	        min_error = error;
	        best_psc = psc_test;
	        best_arr = arr_test;

	        if (error == 0U) {
	            break; // Perfeito matemático encontrado com o maior ARR possível!
	        }
	    }
	}

	t1_init_by_ticks(best_psc, best_arr);
	t1_par.prescaler = best_psc;
	t1_par.autoreload = best_arr;
}

static void t1_nvic_u_en(uint8_t p) {
    SET_BIT(TIM1->DIER, TIM_DIER_UIE);
    uint32_t irq = (uint32_t)TIM1_UP_TIM16_IRQn;
    
    NVIC->IP[irq] = (uint8_t)(p << 4U);
    SET_BIT(NVIC->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_u_di(void) {
    CLEAR_BIT(TIM1->DIER, TIM_DIER_UIE);
    uint32_t irq = (uint32_t)TIM1_UP_TIM16_IRQn;
    SET_BIT(NVIC->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_t_en(uint8_t p) {
    SET_BIT(TIM1->DIER, TIM_DIER_TIE);
    uint32_t irq = (uint32_t)TIM1_TRG_COM_TIM17_IRQn;

    NVIC->IP[irq] = (uint8_t)(p << 4U);
    SET_BIT(NVIC->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_t_di(void) {
    CLEAR_BIT(TIM1->DIER, TIM_DIER_TIE);
    uint32_t irq = (uint32_t)TIM1_TRG_COM_TIM17_IRQn;
    SET_BIT(NVIC->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_cc_en(uint8_t p) {
    SET_BIT(TIM1->DIER, (TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE));
    uint32_t irq = (uint32_t)TIM1_CC_IRQn;

    NVIC->IP[irq] = (uint8_t)(p << 4U);
    SET_BIT(NVIC->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_cc_di(void) {
    CLEAR_BIT(TIM1->DIER, (TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE));
    uint32_t irq = (uint32_t)TIM1_CC_IRQn;
    SET_BIT(NVIC->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_start(void) { 
    SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

static void t1_stop(void)  { 
    CLEAR_BIT(TIM1->CR1, TIM_CR1_CEN);
}

static void t1_config_pwm(tim1_ch_t ch, pwm_mode_t mode, uint32_t pulse_width) {
    CLEAR_BIT(TIM1->CCER, (TIM_CCER_CC1E << (ch * 4U)));

    volatile uint32_t* ccmr = (ch < TIM1_CH3) ? &TIM1->CCMR1 : &TIM1->CCMR2;
    uint32_t shift = (ch == TIM1_CH1 || ch == TIM1_CH3) ? 0U : 8U;

    uint32_t ccmr_mask = (0xFFU << shift);
    uint32_t ccmr_val  = ((mode << 4U) | (1U << 3U)) << shift;

    uint32_t tmp = *ccmr;
    *ccmr = (tmp & ~ccmr_mask) | ccmr_val;

    *(&TIM1->CCR1 + ch) = pulse_width;
    SET_BIT(TIM1->CCER, (TIM_CCER_CC1E << (ch * 4U)));
}

static void t1_enable_complementary(tim1_ch_t ch, uint8_t enable_main, uint8_t enable_comp) {
    uint32_t target_bits = 0;
    uint32_t clear_bits  = 0;
    uint32_t shift       = (ch * 4U);

    if (enable_main) target_bits |= TIM_CCER_CC1E;  else clear_bits |= TIM_CCER_CC1E;
    if (enable_comp) target_bits |= TIM_CCER_CC1NE; else clear_bits |= TIM_CCER_CC1NE;

    CLEAR_BIT(TIM1->CCER, (clear_bits << shift));
    SET_BIT(TIM1->CCER, (target_bits << shift));
}

static void t1_config_deadtime(uint8_t deadtime_value) {
    exe()->write_field(&TIM1->BDTR, TIM_BDTR_DTG, 0U, deadtime_value);
}

static void t1_set_pulse(tim1_ch_t ch, uint32_t pulse_width) {
    *(&TIM1->CCR1 + ch) = pulse_width;
}

/* --- Input Capture Implementation --- */

static void t1_config_capture(tim1_ch_t ch, ic_edge_t edge) {
    CLEAR_BIT(TIM1->CCER, (TIM_CCER_CC1E << (ch * 4U)));

    volatile uint32_t* ccmr = (ch < TIM1_CH3) ? &TIM1->CCMR1 : &TIM1->CCMR2;
    uint32_t shift = (ch == TIM1_CH1 || ch == TIM1_CH3) ? 0U : 8U;

    uint32_t ccmr_mask = (0xFFU << shift);
    uint32_t ccmr_val  = (0x01U << shift); // CCxS = 01 (Direct input mapping)

    uint32_t tmp = *ccmr;
    *ccmr = (tmp & ~ccmr_mask) | ccmr_val;

    uint32_t ccer_shift = (ch * 4U);
    uint32_t polarity_bits = 0U;

    if (edge == IC_FALLING) {
        polarity_bits |= TIM_CCER_CC1P;
    } else if (edge == IC_BOTH) {
        polarity_bits |= (TIM_CCER_CC1P | TIM_CCER_CC1NP);
    }

    CLEAR_BIT(TIM1->CCER, ((TIM_CCER_CC1P | TIM_CCER_CC1NP) << ccer_shift));
    SET_BIT(TIM1->CCER, (polarity_bits << ccer_shift));
    SET_BIT(TIM1->CCER, (TIM_CCER_CC1E << ccer_shift));
}

static uint32_t t1_get_capture(tim1_ch_t ch) {
    return *(&TIM1->CCR1 + ch);
}

static tim1_run t1_run = {
	.init_by_ticks        = t1_init_by_ticks,
	.init_by_freq         = t1_init_by_freq,
	.init_freq            = t1_init_freq,
	.clock_enable         = t1_clk_en,
	.clock_disable        = t1_clk_di,
	.nvic_u_enable        = t1_nvic_u_en,
	.nvic_u_disable       = t1_nvic_u_di,
	.nvic_t_enable        = t1_nvic_t_en,
	.nvic_t_disable       = t1_nvic_t_di,
	.nvic_cc_enable       = t1_nvic_cc_en,
	.nvic_cc_disable      = t1_nvic_cc_di,
	.start                = t1_start,
	.stop                 = t1_stop,
    .config_pwm           = t1_config_pwm,
	.enable_complementary = t1_enable_complementary,
	.config_deadtime      = t1_config_deadtime,
	.set_pulse            = t1_set_pulse,
	.config_capture       = t1_config_capture,
	.get_capture          = t1_get_capture
};

TIM1_Handler t1_instance = {
	.par = &t1_par,
	.run = &t1_run,
};

TIM1_Handler* tim1(void) { 
    return (TIM1_Handler*)&t1_instance; 
}

/*** EOF ***/

