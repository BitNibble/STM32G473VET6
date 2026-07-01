/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
************************************************************************/
#include "stm32gxxxrcc.h"
#include "armsystick.h"
#include "stm32gxxx_tim1.h"
#include "st7789.h"
#include "armfunction.h"
#include "stm32gxxxrtc.h"
#include "explode.h"
#include<string.h>

#define BG_colour 0x0000

// Define a unified bitmask for PD8, PD9, PD10, PD11, PD12, and PD13
// Binary: 0011 1111 0000 0000 -> Hex: 0x3F00
#define BTN_ALL_PINS_MASK    (0x3FU << 8)

// Map operations to their isolated bits for processing
#define BTN_MODE_PIN         (1UL << 8)   // PD8
#define BTN_UP_PIN           (1UL << 9)   // PD9
#define BTN_DOWN_PIN         (1UL << 10)  // PD10
#define BTN_SAVE_PIN         (1UL << 11)  // PD11

typedef enum {
    CFG_IDLE = 0,
    CFG_HOUR,
    CFG_MINUTE,
    CFG_DAY,
    CFG_MONTH,
    CFG_YEAR,
    CFG_WEEKDAY,
    CFG_MAX
} ui_state_t;

static ui_state_t ui_state = CFG_IDLE;
static EXPLODE_Handler btn_engine;

void rtc_ui_init(void);
void select_mode(EXPLODE_Handler active_press);
void adjust_active_field(EXPLODE_Handler active_press);

static inline void _adc1_init(void);
static inline void _adc1_cal_single(void);
static inline void _adc1_cal_differential(void);
static inline void _adc1_enable(void);
static inline int _adc1_disable(void);
void adc1_temp_init(void);
uint16_t adc1_temp_read_raw(void);
float adc1_temp_to_celsius(uint16_t raw);
float adc1_temp_read_celsius(void);

int main(void)
{
	rcc()->inic();
	fpu_enable();
	rtc()->inic();

	char str[32];
	char vecD[8]; // for calendar date
	char vecT[8]; // for calendar time

	GPIO_clock( dev()->gpio->f, 1 );
	GPIO_hmoder( dev()->gpio->f, 1 << 2, 1 );
	rtc_ui_init();

	adc1_temp_init();

	EXPLODE_Handler seconds = EXPLODE_enable();

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	lcd1.start(&lcd1.par);
	lcd1.draw_circle(&lcd1.par,220,300,15,ST77XX_CYAN);
	lcd1.draw_star5(&lcd1.par,220,300,15,5,ST77XX_GOLD);
	lcd1.stop(&lcd1.par);

	while(1)
	{
		if(btn_engine.run->update(&btn_engine.par, dev()->gpio->d->IDR & BTN_ALL_PINS_MASK)) {
			select_mode(btn_engine);
			adjust_active_field(btn_engine);

			switch(ui_state){
			case CFG_IDLE:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Relogio",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_HOUR:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Hora",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_MINUTE:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Minuto",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_DAY:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Dia",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_MONTH:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Mes",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_YEAR:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Ano",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_WEEKDAY:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"Semana",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			case CFG_MAX:
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par,"MAX",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.stop(&lcd1.par);
				break;
			default: break;
			};
		}

		/***/
		rtc()->dr2vec(vecD);
		rtc()->tr2vec(vecT);

		if (seconds.run->update(&seconds.par, vecT[5])) {
			toggle_hpin(dev()->gpio->f, 1 << 2);

			func()->float_to_string(adc1_temp_read_celsius(),str,32);
			strcat(str, " C");
			lcd1.drawstring16x24_size(&lcd1.par,str,15,200,ST77XX_BLUE,BG_colour,8);

			func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
			lcd1.drawstring24x48_size(&lcd1.par,str,15,80,ST77XX_RED,BG_colour,8);
			lcd1.stop(&lcd1.par);

			lcd1.start(&lcd1.par);
			func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
			lcd1.drawstring16x24(&lcd1.par,str,10,240,ST77XX_GREEN,BG_colour);

			lcd1.drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,300,ST77XX_WHITE,BG_colour,10);
		}
	}
}

void rtc_ui_init(void)
{
    // Enable GPIO Port D Clock via your helper
    GPIO_clock(dev()->gpio->d, 1);

    // Batch set PD8-PD13 to Input Mode (0)
    GPIO_hmoder(dev()->gpio->d, BTN_ALL_PINS_MASK, 0);

    // Batch set PD8-PD13 to internal Pull-Up (1)
    GPIO_hpupd(dev()->gpio->d, BTN_ALL_PINS_MASK, 1);

    // Initialize the edge detector tracking instance
    btn_engine = EXPLODE_enable();
}

void select_mode(EXPLODE_Handler active_press)
{
	if (active_press.par.HL & BTN_MODE_PIN) {
		ui_state = LIMIT_INC(ui_state, 7, 0);
	}
}

void adjust_active_field(EXPLODE_Handler active_press)
{
	uint8_t t_hr = ZERO;
	uint8_t t_min = ZERO;
	uint8_t t_day = ZERO;
	uint8_t t_mth = ZERO;
	uint8_t t_yr = ZERO;
	uint8_t t_wday = ZERO;

    if (active_press.par.HL & BTN_UP_PIN) {
        switch (ui_state) {
            case CFG_HOUR:
            	t_hr = rtc()->get_hour();
            	t_hr   = LIMIT_INC(t_hr,   23, 0);
            	rtc()->set_hour(t_hr);
            	break;
            case CFG_MINUTE:
            	t_min = rtc()->get_minute();
            	t_min  = LIMIT_INC(t_min,  59, 0);
            	rtc()->set_minute(t_min);
            	break;
            case CFG_DAY:
            	t_day = rtc()->get_day();
            	t_day  = LIMIT_INC(t_day,  31, 1);
            	rtc()->set_day(t_day);
            	break;
            case CFG_MONTH:
            	t_mth = rtc()->get_month();
            	t_mth  = LIMIT_INC(t_mth,  12, 1);
            	rtc()->set_month(t_mth);
            	break;
            case CFG_YEAR:
            	t_yr = rtc()->get_year();
            	t_yr   = LIMIT_INC(t_yr,   99, 0);
            	rtc()->set_year(t_yr);
            	break;
            case CFG_WEEKDAY:
            	t_wday = rtc()->get_weekday();
            	t_wday = LIMIT_INC(t_wday,  7, 1);
            	rtc()->set_weekday(t_wday);
            	break;
            default: break;
        }
    }
    else if (active_press.par.HL & BTN_DOWN_PIN) {
        switch (ui_state) {
            case CFG_HOUR:
            	t_hr = rtc()->get_hour();
            	t_hr   = LIMIT_DEC(t_hr,   23, 0);
            	rtc()->set_hour(t_hr);
            	break;
            case CFG_MINUTE:
            	t_min = rtc()->get_minute();
            	t_min  = LIMIT_DEC(t_min,  59, 0);
            	rtc()->set_minute(t_min);
            	break;
            case CFG_DAY:
            	t_day = rtc()->get_day();
            	t_day  = LIMIT_DEC(t_day,  31, 1);
            	rtc()->set_day(t_day);
            	break;
            case CFG_MONTH:
            	t_mth = rtc()->get_month();
            	t_mth  = LIMIT_DEC(t_mth,  12, 1);
            	rtc()->set_month(t_mth);
            	break;
            case CFG_YEAR:
            	t_yr = rtc()->get_year();
            	t_yr   = LIMIT_DEC(t_yr,   99, 0);
            	rtc()->set_year(t_yr);
            	break;
            case CFG_WEEKDAY:
            	t_wday = rtc()->get_weekday();
            	t_wday = LIMIT_DEC(t_wday,  7, 1);
            	rtc()->set_weekday(t_wday);
            	break;
            default: break;
        }
    }
}

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

static inline void _adc1_init(void) {
	/* Sair do modo Deep Power Down do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_DEEPPWD);
	/* Ativar o regulador de tensão interno do ADC1 */
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADVREGEN);
	/* Aguardar a estabilização do regulador interno (~20us) */
	_delay_us(20);
}

static inline void _adc1_cal_single(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	// Select single-ended calibration
	dev()->analog->adc1->CR &= ~ADC_CR_ADCALDIF;
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

static inline void _adc1_cal_differential(void) {
	uint32_t timeout = 0x1FFFFF;
	_adc1_init();
	/* Iniciar a calibração do ADC1 */
	clear_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	// Select differential calibration
	dev()->analog->adc1->CR |= ADC_CR_ADCALDIF;
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADCAL);
	while ((dev()->analog->adc1->CR & ADC_CR_ADCAL) && timeout--);
}

static inline void _adc1_enable(void) {
	uint32_t timeout = 0x1FFFFF;
	/* Garantir que o flag ADRDY está limpo antes de ligar */
	set_reg(&dev()->analog->adc1->ISR, ADC_ISR_ADRDY);

	/* Ligar o ADC e aguardar o flag de pronto */
	set_reg(&dev()->analog->adc1->CR, ADC_CR_ADEN);
	while (!(dev()->analog->adc1->ISR & ADC_ISR_ADRDY) && timeout--);
}

static inline int _adc1_disable(void)
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

