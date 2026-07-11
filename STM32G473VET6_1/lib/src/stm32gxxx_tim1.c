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
    exe()->set_reg(&dev()->sys->rcc->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_clk_di(void) {
    exe()->clear_reg(&dev()->sys->rcc->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_init_by_ticks(uint16_t prescaler, uint32_t autoreload) {
    t1_clk_en();

    dev()->timer->tim1->PSC = prescaler;
    dev()->timer->tim1->ARR = autoreload;
    t1_par.prescaler = prescaler;
    t1_par.autoreload = autoreload;

    exe()->set_reg(&dev()->timer->tim1->BDTR, TIM_BDTR_MOE);
    exe()->set_reg(&dev()->timer->tim1->EGR, TIM_EGR_UG);
    exe()->clear_reg(&dev()->timer->tim1->SR, TIM_SR_UIF);

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

static void t1_nvic_u_en(uint8_t p) {
    exe()->set_reg(&dev()->timer->tim1->DIER, TIM_DIER_UIE);
    uint32_t irq = (uint32_t)TIM1_UP_TIM16_IRQn;
    
    dev()->core->nvic->IP[irq] = (uint8_t)(p << 4U);
    exe()->set_reg(&dev()->core->nvic->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_u_di(void) {
    exe()->clear_reg(&dev()->timer->tim1->DIER, TIM_DIER_UIE);
    uint32_t irq = (uint32_t)TIM1_UP_TIM16_IRQn;
    exe()->set_reg(&dev()->core->nvic->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_t_en(uint8_t p) {
    exe()->set_reg(&dev()->timer->tim1->DIER, TIM_DIER_TIE);
    uint32_t irq = (uint32_t)TIM1_TRG_COM_TIM17_IRQn;

    dev()->core->nvic->IP[irq] = (uint8_t)(p << 4U);
    exe()->set_reg(&dev()->core->nvic->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_t_di(void) {
    exe()->clear_reg(&dev()->timer->tim1->DIER, TIM_DIER_TIE);
    uint32_t irq = (uint32_t)TIM1_TRG_COM_TIM17_IRQn;
    exe()->set_reg(&dev()->core->nvic->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_cc_en(uint8_t p) {
    exe()->set_reg(&dev()->timer->tim1->DIER, (TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE));
    uint32_t irq = (uint32_t)TIM1_CC_IRQn;

    dev()->core->nvic->IP[irq] = (uint8_t)(p << 4U);
    exe()->set_reg(&dev()->core->nvic->ISER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_nvic_cc_di(void) {
    exe()->clear_reg(&dev()->timer->tim1->DIER, (TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE));
    uint32_t irq = (uint32_t)TIM1_CC_IRQn;
    exe()->set_reg(&dev()->core->nvic->ICER[irq >> 5U], (1U << (irq & 0x1FU)));
}

static void t1_start(void) { 
    exe()->set_reg(&TIM1->CR1, TIM_CR1_CEN);
}

static void t1_stop(void)  { 
    exe()->clear_reg(&TIM1->CR1, TIM_CR1_CEN);
}

static void t1_config_pwm(tim1_ch_t ch, pwm_mode_t mode, uint32_t pulse_width) {
    exe()->clear_reg(&dev()->timer->tim1->CCER, (TIM_CCER_CC1E << (ch * 4U)));

    volatile uint32_t* ccmr = (ch < TIM1_CH3) ? &dev()->timer->tim1->CCMR1 : &dev()->timer->tim1->CCMR2;
    uint32_t shift = (ch == TIM1_CH1 || ch == TIM1_CH3) ? 0U : 8U;

    uint32_t ccmr_mask = (0xFFU << shift);
    uint32_t ccmr_val  = ((mode << 4U) | (1U << 3U)) << shift;

    uint32_t tmp = *ccmr;
    *ccmr = (tmp & ~ccmr_mask) | ccmr_val;

    *(&dev()->timer->tim1->CCR1 + ch) = pulse_width;
    exe()->set_reg(&dev()->timer->tim1->CCER, (TIM_CCER_CC1E << (ch * 4U)));
}

static void t1_enable_complementary(tim1_ch_t ch, uint8_t enable_main, uint8_t enable_comp) {
    uint32_t target_bits = 0;
    uint32_t clear_bits  = 0;
    uint32_t shift       = (ch * 4U);

    if (enable_main) target_bits |= TIM_CCER_CC1E;  else clear_bits |= TIM_CCER_CC1E;
    if (enable_comp) target_bits |= TIM_CCER_CC1NE; else clear_bits |= TIM_CCER_CC1NE;

    exe()->clear_reg(&dev()->timer->tim1->CCER, (clear_bits << shift));
    exe()->set_reg(&dev()->timer->tim1->CCER, (target_bits << shift));
}

static void t1_config_deadtime(uint8_t deadtime_value) {
    exe()->write_field_value(&dev()->timer->tim1->BDTR, TIM_BDTR_DTG, 0U, deadtime_value);
}

static void t1_set_pulse(tim1_ch_t ch, uint32_t pulse_width) {
    *(&dev()->timer->tim1->CCR1 + ch) = pulse_width;
}

/* --- Input Capture Implementation --- */

static void t1_config_capture(tim1_ch_t ch, ic_edge_t edge) {
    exe()->clear_reg(&dev()->timer->tim1->CCER, (TIM_CCER_CC1E << (ch * 4U)));

    volatile uint32_t* ccmr = (ch < TIM1_CH3) ? &dev()->timer->tim1->CCMR1 : &dev()->timer->tim1->CCMR2;
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

    exe()->clear_reg(&dev()->timer->tim1->CCER, ((TIM_CCER_CC1P | TIM_CCER_CC1NP) << ccer_shift));
    exe()->set_reg(&dev()->timer->tim1->CCER, (polarity_bits << ccer_shift));
    exe()->set_reg(&dev()->timer->tim1->CCER, (TIM_CCER_CC1E << ccer_shift));
}

static uint32_t t1_get_capture(tim1_ch_t ch) {
    return *(&dev()->timer->tim1->CCR1 + ch);
}

static tim1_run t1_run = {
	.init_by_ticks        = t1_init_by_ticks,
	.init_by_freq         = t1_init_by_freq,
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

static tim1_irq t1_irq = {0};

TIM1_Handler t1_instance = {
	.par = &t1_par,
	.run = &t1_run,
    .irq = &t1_irq
};

TIM1_Handler* tim1(void) { 
    return (TIM1_Handler*)&t1_instance; 
}

