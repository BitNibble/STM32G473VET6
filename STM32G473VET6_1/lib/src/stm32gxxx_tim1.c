#include "stm32gxxx_tim1.h"

static void t1_clk_en(void) {
    set_reg(&RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_clk_di(void) {
    clear_reg(&RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
}

static void t1_init(uint16_t prescaler, uint32_t autoreload) {
    t1_clk_en();
    
    TIM1->PSC = prescaler;
    TIM1->ARR = autoreload;
    
    set_reg(&TIM1->BDTR, TIM_BDTR_MOE);
    
    set_reg(&TIM1->EGR, TIM_EGR_UG);
    clear_reg(&TIM1->SR, TIM_SR_UIF);
    (void)TIM1->SR; // Sync barrier
}

static void t1_nvic_u_en(uint8_t p) {
    // 1. Enable Update flag inside the timer device layout
    set_reg(&TIM1->DIER, TIM_DIER_UIE);
    
    // 2. STMicroelectronics defines the G473 combined vector macro as:
    uint32_t irq_num = (uint32_t)TIM1_UP_TIM16_IRQn;

    // 3. Set priority directly via byte indexing (Bypassing 32-bit toolset mismatch)
    NVIC->IP[irq_num] = (uint8_t)(p << 4U);

    // 4. Calculate proper NVIC array register slot index (irq_num / 32)
    uint32_t bank = irq_num >> 5U;
    uint32_t bit  = irq_num & 0x1FU;

    // Pass the exact address of that array bank to your set_reg tool
    set_reg(&NVIC->ISER[bank], (1U << bit));
}

static void t1_nvic_u_di(void) {
    // Match the same combined macro signature
    uint32_t irq_num = (uint32_t)TIM1_UP_TIM16_IRQn;
    
    clear_reg(&TIM1->DIER, TIM_DIER_UIE);

    // Calculate bank index for disabling
    uint32_t bank = irq_num >> 5U;
    uint32_t bit  = irq_num & 0x1FU;

    set_reg(&NVIC->ICER[bank], (1U << bit));
}

static void t1_nvic_t_en(uint8_t p) {
    // 1. Enable Trigger Interrupt inside the timer register map
    set_reg(&TIM1->DIER, TIM_DIER_TIE);

    // 2. COMPLIANCE FIX: Swap to the official shared TIM17 vector macro
    uint32_t irq_num = (uint32_t)TIM1_TRG_COM_TIM17_IRQn;

    // 3. Process direct byte-priority mapping
    NVIC->IP[irq_num] = (uint8_t)(p << 4U);

    // 4. Index the proper NVIC array bank
    uint32_t bank = irq_num >> 5U;
    uint32_t bit  = irq_num & 0x1FU;
    set_reg(&NVIC->ISER[bank], (1U << bit));
}

static void t1_start(void) { 
    set_reg(&TIM1->CR1, TIM_CR1_CEN); 
}

static void t1_stop(void)  { 
    clear_reg(&TIM1->CR1, TIM_CR1_CEN); 
}

static tim1_callback t1_callbacks = {0};

static const TIM1_Handler t1_instance = {
    .init           = t1_init,
    .clock_enable   = t1_clk_en,   
    .clock_disable  = t1_clk_di,
    .nvic_u_enable  = t1_nvic_u_en, 
    .nvic_u_disable = t1_nvic_u_di,
	.nvic_t_enable  = t1_nvic_t_en,
    .start          = t1_start,           
    .stop           = t1_stop,
    .callback       = &t1_callbacks
};

TIM1_Handler* tim1(void) { 
    return (TIM1_Handler*)&t1_instance; 
}

