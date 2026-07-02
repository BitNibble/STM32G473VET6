/******************************************************************************
	STM32 GXXX ADC1
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-GXXX
Date: 02072026
*******************************************************************************/
#include "stm32gxxx_adc1.h"
#include "arm_systick.h"

/* ============================================================
   ADC INITIALIZATION
   =========================================================== */
void adc_temp_init_v1(void) {
    /* 1. Ativar o clock do circuito do ADC no RCC */
    set_reg(&dev()->sys->rcc->AHB2ENR, RCC_AHB2ENR_ADC12EN);

    /* 2. Sair do modo Deep Power Down (Obrigatório antes de QUALQUER outra ação no ADC) */
    clear_reg(&dev()->analog->adc1->CR, ADC_CR_DEEPPWD);

    /* 3. Ativar o regulador de tensão interno */
    set_reg(&dev()->analog->adc1->CR, ADC_CR_ADVREGEN);

    /* 4. Aguardar a estabilização do regulador interno (~20us) */
    _delay_us(20);

    /* 5. SELECIONAR CLOCK SÍNCRONO (HCLK) NO REGISTO COMUM */
    // Mudamos o clock APÓS o regulador estar ativo e estável.
    // Configuramos CKMODE = 01 (HCLK/1 síncrono).
    uint32_t ccr_val = dev()->analog->adc12_common->CCR;
    ccr_val &= ~(3 << ADC_CCR_CKMODE_Pos); // Limpa bits antigos
    ccr_val |= (1 << ADC_CCR_CKMODE_Pos);  // Define HCLK/1
    set_reg(&dev()->analog->adc12_common->CCR, ccr_val);

    /* 6. Iniciar a calibração do ADC (Obrigatório antes de ligar o ADEN) */
    set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
    while (dev()->analog->adc1->CR & ADC_CR_ADCAL);

    /* 7. Ativar o canal do sensor de temperatura interno */
    set_reg(&dev()->analog->adc12_common->CCR, dev()->analog->adc12_common->CCR | ADC_CCR_VSENSESEL);

    /* 8. Garantir que o flag ADRDY está limpo antes de ligar */
    set_reg(&dev()->analog->adc1->ISR, ADC_ISR_ADRDY);

    /* 9. Ligar o ADC e aguardar o flag de pronto */
    set_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
    while (!(dev()->analog->adc1->ISR & ADC_ISR_ADRDY));
}

inline void _adc1_init(void) {
	/* Sair do modo Deep Power Down do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_DEEPPWD);
	/* Ativar o regulador de tensão interno do ADC1 */
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADVREGEN);
	/* Aguardar a estabilização do regulador interno (~20us) */
	_delay_us(20);
}

inline void _adc1_cal_single(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	// Select single-ended calibration
	dev()->analog->adc1->CR &= ~ADC_CR_ADCALDIF;
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

inline void _adc1_cal_differential(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	// Select differential calibration
	dev()->analog->adc1->CR |= ADC_CR_ADCALDIF;
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

inline void _adc1_enable(void) {
	uint32_t timeout = 0x1FFFFF;
	/* Garantir que o flag ADRDY está limpo antes de ligar */
	set_reg(&dev()->analog->adc1->ISR, ADC_ISR_ADRDY);
	/* Ligar o ADC e aguardar o flag de pronto */
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	while (!(dev()->analog->adc1->ISR & ADC_ISR_ADRDY) && timeout--);
}

inline int _adc1_disable(void)
{
    uint32_t timeout;
    // pointer alias for readability
    ADC_TypeDef *adc = dev()->analog->adc1;
    // Stop regular conversion if running
    if (get_block_value(adc->CR, 1, ADC_CR_ADSTART_Pos))
    {
        set_reg(&adc->CR, ADC_CR_ADSTP);

        timeout = 0x1FFFFF;
        while (get_block_value(adc->CR, 1, ADC_CR_ADSTP_Pos) && (--timeout));
        if (timeout == 0) return -1;
    }
    // Stop injected conversion if running
    if (get_block_value(adc->CR, 1, ADC_CR_JADSTART_Pos))
    {
        set_reg(&adc->CR, ADC_CR_JADSTP);

        timeout = 0x1FFFFF;
        while (get_block_value(adc->CR, 1, ADC_CR_JADSTP_Pos) && (--timeout));
        if (timeout == 0) return -2;
    }
    // Request disable
    set_reg(&adc->CR, ADC_CR_ADDIS);
    // Wait until fully disabled
    timeout = 0x1FFFFF;
    while (get_block_value(adc->CR, 1, ADC_CR_ADEN_Pos) && (--timeout));
    if (timeout == 0) return -3;

    return 0;
}

void adc1_temp_init(void) {
	/* Ativar o clock do circuito do ADC12 no RCC */
	set_reg(&dev()->sys->rcc->AHB2ENR, RCC_AHB2ENR_ADC12EN);

	_adc1_init();

    /* Selecionar Clock Síncrono (HCLK/1) no registo comum */
    uint32_t ccr_val = dev()->analog->adc12_common->CCR;
    ccr_val &= ~(3 << ADC_CCR_CKMODE_Pos);
    ccr_val |= (1 << ADC_CCR_CKMODE_Pos);
    set_reg(&dev()->analog->adc12_common->CCR, ccr_val);

    _adc1_cal_single();

    /* Ativar o canal do sensor de temperatura interno (Partilhado) */
    set_reg(&dev()->analog->adc12_common->CCR, dev()->analog->adc12_common->CCR | ADC_CCR_VSENSESEL);

    /* CONFIGURAR O TEMPO DE AMOSTRAGEM (CRÍTICO)
       O sensor interno do STM32G4 exige um tempo de amostragem de pelo menos 4.9 us.
       Configuramos o Canal 16 para usar o máximo de ciclos disponível (SMP2 = 111 -> 640.5 ciclos) */
    uint32_t smpr2_val = dev()->analog->adc1->SMPR2;
    smpr2_val &= ~(7 << ADC_SMPR2_SMP16_Pos); // Limpa bits do Canal 16
    smpr2_val |= (7 << ADC_SMPR2_SMP16_Pos);  // Define 640.5 ciclos de clock
    set_reg(&dev()->analog->adc1->SMPR2, smpr2_val);

    /* CONFIGURAR O SEQUENCIADOR (SQR1)
       Definimos que vamos fazer apenas 1 conversão (L = 0000) e que o
       primeiro canal a ser lido (SQ1) é o Canal 16. */
    uint32_t sqr1_val = dev()->analog->adc1->SQR1;
    sqr1_val &= ~(ADC_SQR1_L | (0x1F << ADC_SQR1_SQ1_Pos)); // Limpa comprimento e SQ1
    sqr1_val |= (16 << ADC_SQR1_SQ1_Pos);                   // SQ1 = Canal 16, L = 0 (1 conversão)
    set_reg(&dev()->analog->adc1->SQR1, sqr1_val);

    _adc1_enable();
}

/* ============================================================
   RAW ADC READ
   ============================================================ */
uint16_t adc1_temp_read_raw(void)
{
	uint32_t timeout = 0x1FFFFF;
    set_reg(
        &dev()->analog->adc1->CR,
        ADC_CR_ADSTART
    );

    while (!(dev()->analog->adc1->ISR & ADC_ISR_EOC) && timeout--);

    return (uint16_t)dev()->analog->adc1->DR;
}

/* ============================================================
   CALIBRATED TEMPERATURE CONVERSION
   ============================================================ */
float adc1_temp_to_celsius(uint16_t raw)
{
    // Endereços oficiais de calibração do STM32G4 (gravados a 3.0V)
    uint16_t cal1 = *(volatile uint16_t*)0x1FFF75A8; // Medido a 30 ºC
    uint16_t cal2 = *(volatile uint16_t*)0x1FFF75CA; // Medido a 130 ºC

    /*
       Ajuste de VDDA:
       Se a sua placa usa VDDA = 3.3V, o valor bruto lido deve ser escalado
       para a referência de fábrica (3.0V). Se a sua placa usar 3.0V exatos,
       mude o fator para 1.0f.
    */
    float vdda_atual = 3.3f;
    float raw_escalado = (float)raw * (vdda_atual / 3.0f);

    // Fórmula oficial do RM0440 utilizando 130 ºC para TS_CAL2_TEMP
    return 30.0f + ((raw_escalado - (float)cal1) * (130.0f - 30.0f)) / (float)(cal2 - cal1);
}

/* ============================================================
   HIGH-LEVEL API
   ============================================================ */
float adc1_temp_read_celsius(void)
{
    uint16_t raw = adc1_temp_read_raw();
    return adc1_temp_to_celsius(raw);
}

/*** EOF ***/

