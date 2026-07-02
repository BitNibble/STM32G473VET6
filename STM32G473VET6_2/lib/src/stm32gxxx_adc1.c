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
inline void _adc1_init(void) {
	/* Sair do modo Deep Power Down do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_DEEPPWD);
	/* Ativar o regulador de tensão interno do ADC1 */
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADVREGEN);
	/* Aguardar a estabilização do regulador interno (~20us) */
	_delay_us(20);
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

inline void _adc1_cal_single(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	if (get_block_value(dev()->analog->adc1->CR, 1, ADC_CR_ADEN_Pos))
	    _adc1_disable();
	// Select single-ended calibration
	write_block_value( &dev()->analog->adc1->CR, 1, ADC_CR_ADCALDIF_Pos, 0 );
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

inline void _adc1_cal_differential(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	if (get_block_value(dev()->analog->adc1->CR, 1, ADC_CR_ADEN_Pos))
	    _adc1_disable();
	// Select differential calibration
	write_block_value( &dev()->analog->adc1->CR, 1, ADC_CR_ADCALDIF_Pos, 1 );
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

void adc1_temp_init(void) {
	/* Ativar o clock do circuito do ADC12 no RCC */
	set_reg(&dev()->sys->rcc->AHB2ENR, RCC_AHB2ENR_ADC12EN);

	_adc1_init();
    /* Selecionar Clock Síncrono (HCLK/1) no registo comum */
	write_field_value( &dev()->analog->adc12_common->CCR, ADC_CCR_CKMODE_Msk, ADC_CCR_CKMODE_Pos, 1 );

    _adc1_cal_single();
    /* Ativar o canal do sensor de temperatura interno (Partilhado) */
    set_reg( &dev()->analog->adc12_common->CCR, ADC_CCR_VSENSESEL );
    /* CONFIGURAR O TEMPO DE AMOSTRAGEM (CRÍTICO)
       O sensor interno do STM32G4 exige um tempo de amostragem de pelo menos 4.9 us.
       Configuramos o Canal 16 para usar o máximo de ciclos disponível (SMP2 = 111 -> 640.5 ciclos) */
    write_field_value( &dev()->analog->adc1->SMPR2, ADC_SMPR2_SMP16_Msk, ADC_SMPR2_SMP16_Pos, 7 );
    /* CONFIGURAR O SEQUENCIADOR (SQR1)
       Definimos que vamos fazer apenas 1 conversão (L = 0000) e que o
       primeiro canal a ser lido (SQ1) é o Canal 16. */
    write_field_value( &dev()->analog->adc1->SQR1, ADC_SQR1_L_Msk, ADC_SQR1_L_Pos, 0 );
    write_field_value( &dev()->analog->adc1->SQR1, ADC_SQR1_SQ1_Msk, ADC_SQR1_SQ1_Pos, 16 );

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

/******/
static inline int adc_calibrate(ADC_TypeDef *adc, uint32_t timeout)
{
    set_reg(&adc->CR, ADC_CR_ADCAL);

    while (get_block_value(adc->CR, 1, ADC_CR_ADCAL_Pos) && (--timeout));
    return (timeout == 0) ? -1 : 0;
}

static inline void adc_jstart(ADC_TypeDef *adc)
{
    set_reg(&adc->CR, ADC_CR_JADSTART);
}

static inline int adc_jstop(ADC_TypeDef *adc, uint32_t timeout)
{
    set_reg(&adc->CR, ADC_CR_JADSTP);

    while (get_block_value(adc->CR, 1, ADC_CR_JADSTP_Pos) && (--timeout));
    return (timeout == 0) ? -1 : 0;
}

static inline void adc_start(ADC_TypeDef *adc)
{
    set_reg(&adc->CR, ADC_CR_ADSTART);
}

static inline int adc_stop(ADC_TypeDef *adc, uint32_t timeout)
{
    set_reg(&adc->CR, ADC_CR_ADSTP);

    while (get_block_value(adc->CR, 1, ADC_CR_ADSTP_Pos) && (--timeout));
    return (timeout == 0) ? -1 : 0;
}

static inline uint8_t adc_is_enabled(ADC_TypeDef *adc)
{
    return get_block_value(adc->CR, 1, ADC_CR_ADEN_Pos);
}

static inline uint8_t adc_is_busy(ADC_TypeDef *adc)
{
    return get_block_value(adc->CR, 1, ADC_CR_ADSTART_Pos) |
           get_block_value(adc->CR, 1, ADC_CR_JADSTART_Pos);
}

static inline int adc_disable(ADC_TypeDef *adc, uint32_t timeout)
{
    if (adc_is_busy(adc))
        return -1;

    set_reg(&adc->CR, ADC_CR_ADDIS);

    while (adc_is_enabled(adc) && (--timeout));
    return (timeout == 0) ? -2 : 0;
}

static inline int adc_safe_disable(ADC_TypeDef *adc)
{
    uint32_t timeout = 0x1FFFFF;

    if (adc_is_busy(adc))
    {
        if (adc_stop(adc, timeout)) return -1;
        timeout = 0x1FFFFF;

        if (adc_jstop(adc, timeout)) return -2;
    }

    timeout = 0x1FFFFF;
    set_reg(&adc->CR, ADC_CR_ADDIS);

    while (adc_is_enabled(adc) && (--timeout));
    return (timeout == 0) ? -3 : 0;
}

/*** EOF ***/

