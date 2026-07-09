/******************************************************************************
	STM32G473 RTC Source Library
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
Date:     08/06/2026
*******************************************************************************/
#include "stm32gxxx_rtc.h"

/*** Validation Limits ***/
#define MAX_HOUR              23
#define MAX_MINUTE            59
#define MAX_SECOND            59
#define MAX_YEAR              99
#define MAX_MONTH             12
#define MIN_MONTH             1
#define MAX_WEEKDAY           7
#define MIN_WEEKDAY           1
#define MAX_DAY               31
#define MIN_DAY               1
#define RTC_INIT_TIMEOUT      200000U

#define RTCSEL_NONE           0x00U
#define RTCSEL_LSE            0x01U
#define RTCSEL_LSI            0x02U
#define RTCSEL_HSE            0x03U

/*** Private Declarations ***/
static void RTC_Write_enable(void);
static void RTC_Write_disable(void);
static void RTC_Reg_unlock(void);
static void RTC_Wait_sync(void);
static void RTC_Set_tr(uint32_t value);
static void RTC_Set_dr(uint32_t value);
static uint8_t _rtc_bcd2dec(uint8_t num);
static uint8_t _rtc_dec2bcd(uint8_t num);

/*** Procedure & Function Definition ***/

static uint8_t RTC_get_year(void) {
    RTC_Wait_sync();
    uint32_t dr = RTC->DR;
    uint8_t t = (uint8_t)get_field_value(dr, RTC_DR_YT_Msk, RTC_DR_YT_Pos);
    uint8_t u = (uint8_t)get_field_value(dr, RTC_DR_YU_Msk, RTC_DR_YU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static uint8_t RTC_get_month(void) {
    RTC_Wait_sync();
    uint32_t dr = RTC->DR;
    uint8_t t = (uint8_t)get_field_value(dr, RTC_DR_MT_Msk, RTC_DR_MT_Pos);
    uint8_t u = (uint8_t)get_field_value(dr, RTC_DR_MU_Msk, RTC_DR_MU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static uint8_t RTC_get_weekday(void) {
    RTC_Wait_sync();
    return (uint8_t)get_field_value(RTC->DR, RTC_DR_WDU_Msk, RTC_DR_WDU_Pos);
}

static uint8_t RTC_get_day(void) {
    RTC_Wait_sync();
    uint32_t dr = RTC->DR;
    uint8_t t = (uint8_t)get_field_value(dr, RTC_DR_DT_Msk, RTC_DR_DT_Pos);
    uint8_t u = (uint8_t)get_field_value(dr, RTC_DR_DU_Msk, RTC_DR_DU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static uint8_t RTC_get_hour(void) {
    RTC_Wait_sync();
    uint32_t tr = RTC->TR;
    uint8_t t = (uint8_t)get_field_value(tr, RTC_TR_HT_Msk, RTC_TR_HT_Pos);
    uint8_t u = (uint8_t)get_field_value(tr, RTC_TR_HU_Msk, RTC_TR_HU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static uint8_t RTC_get_minute(void) {
    RTC_Wait_sync();
    uint32_t tr = RTC->TR;
    uint8_t t = (uint8_t)get_field_value(tr, RTC_TR_MNT_Msk, RTC_TR_MNT_Pos);
    uint8_t u = (uint8_t)get_field_value(tr, RTC_TR_MNU_Msk, RTC_TR_MNU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static uint8_t RTC_get_second(void) {
    RTC_Wait_sync();
    uint32_t tr = RTC->TR;
    uint8_t t = (uint8_t)get_field_value(tr, RTC_TR_ST_Msk, RTC_TR_ST_Pos);
    uint8_t u = (uint8_t)get_field_value(tr, RTC_TR_SU_Msk, RTC_TR_SU_Pos);
    return (_rtc_bcd2dec(t) * 10) + _rtc_bcd2dec(u);
}

static void RTC_set_day(uint8_t day) {
    if (day < MIN_DAY || day > MAX_DAY) return;
    uint32_t dr = RTC->DR;
    dr &= ~(RTC_DR_DT | RTC_DR_DU);
    dr |= (uint32_t)((_rtc_dec2bcd(day / 10) << RTC_DR_DT_Pos) | (_rtc_dec2bcd(day % 10) << RTC_DR_DU_Pos));
    RTC_Set_dr(dr);
}

static void RTC_set_month(uint8_t month) {
    if (month < MIN_MONTH || month > MAX_MONTH) return;
    uint32_t dr = RTC->DR;
    dr &= ~(RTC_DR_MT | RTC_DR_MU);
    dr |= (uint32_t)((_rtc_dec2bcd(month / 10) << RTC_DR_MT_Pos) | (_rtc_dec2bcd(month % 10) << RTC_DR_MU_Pos));
    RTC_Set_dr(dr);
}

static void RTC_set_weekday(uint8_t weekday) {
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) return;
    uint32_t dr = RTC->DR;
    write_field_value(&dr, RTC_DR_WDU_Msk, RTC_DR_WDU_Pos, weekday);
    RTC_Set_dr(dr);
}

static void RTC_set_year(uint8_t year) {
    if (year > MAX_YEAR) return;
    uint32_t dr = RTC->DR;
    dr &= ~(RTC_DR_YT | RTC_DR_YU);
    dr |= (uint32_t)((_rtc_dec2bcd(year / 10) << RTC_DR_YT_Pos) | (_rtc_dec2bcd(year % 10) << RTC_DR_YU_Pos));
    RTC_Set_dr(dr);
}

static void RTC_set_hour(uint8_t hour) {
    if (hour > MAX_HOUR) return;
    uint32_t tr = RTC->TR;
    tr &= ~(RTC_TR_HT | RTC_TR_HU);
    tr |= (uint32_t)((_rtc_dec2bcd(hour / 10) << RTC_TR_HT_Pos) | (_rtc_dec2bcd(hour % 10) << RTC_TR_HU_Pos));
    RTC_Set_tr(tr);
}

static void RTC_set_minute(uint8_t minute) {
    if (minute > MAX_MINUTE) return;
    uint32_t tr = RTC->TR;
    tr &= ~(RTC_TR_MNT | RTC_TR_MNU);
    tr |= (uint32_t)((_rtc_dec2bcd(minute / 10) << RTC_TR_MNT_Pos) | (_rtc_dec2bcd(minute % 10) << RTC_TR_MNU_Pos));
    RTC_Set_tr(tr);
}

static void RTC_set_second(uint8_t second) {
    if (second > MAX_SECOND) return;
    uint32_t tr = RTC->TR;
    tr &= ~(RTC_TR_ST | RTC_TR_SU);
    tr |= (uint32_t)((_rtc_dec2bcd(second / 10) << RTC_TR_ST_Pos) | (_rtc_dec2bcd(second % 10) << RTC_TR_SU_Pos));
    RTC_Set_tr(tr);
}

static uint32_t RTC_dr(void)
{
	return RTC->DR;
}

static void RTC_dr2vec(char* rtc_vect)
{
    uint32_t dr = RTC->DR;

    // YT
    rtc_vect[0] = _rtc_bcd2dec((dr >> RTC_DR_YT_Pos) & 0x0F);
    // YU
    rtc_vect[1] = _rtc_bcd2dec((dr >> RTC_DR_YU_Pos) & 0x0F);
    // WDU
    rtc_vect[2] = _rtc_bcd2dec((dr >> RTC_DR_WDU_Pos) & 0x07);
    // MT
    rtc_vect[3] = _rtc_bcd2dec((dr >> RTC_DR_MT_Pos) & 0x01);
    // MU
    rtc_vect[4] = _rtc_bcd2dec((dr >> RTC_DR_MU_Pos) & 0x0F);
    // DT
    rtc_vect[5] = _rtc_bcd2dec((dr >> RTC_DR_DT_Pos) & 0x03);
    // DU
    rtc_vect[6] = _rtc_bcd2dec(dr & RTC_DR_DU);
}

static uint32_t RTC_tr(void)
{
	return RTC->TR;
}

static void RTC_tr2vec(char* rtc_vect)
{
    uint32_t tr = RTC->TR;

    // ht
    rtc_vect[0] = _rtc_bcd2dec((tr >> RTC_TR_HT_Pos) & 0x03);
    // hu
    rtc_vect[1] = _rtc_bcd2dec((tr >> RTC_TR_HU_Pos) & 0x0F);
    // mnt
    rtc_vect[2] = _rtc_bcd2dec((tr >> RTC_TR_MNT_Pos) & 0x07);
    // mnu
    rtc_vect[3] = _rtc_bcd2dec((tr >> RTC_TR_MNU_Pos) & 0x0F);
    // st
    rtc_vect[4] = _rtc_bcd2dec((tr >> RTC_TR_ST_Pos) & 0x07);
    // su
    rtc_vect[5] = _rtc_bcd2dec(tr & RTC_TR_SU);
}

static void bkp_write(uint8_t registerIndex, uint32_t data) {
    if (registerIndex >= 32) return;
    RTC_Write_enable();
    volatile uint32_t* bkp_reg = &(TAMP->BKP0R);
    *(bkp_reg + registerIndex) = data;
    RTC_Write_disable();
}

static uint32_t bkp_read(uint8_t registerIndex) {
    if (registerIndex >= 32) return 0;
    volatile uint32_t* bkp_reg = &(TAMP->BKP0R);
    return *(bkp_reg + registerIndex);
}

static uint16_t RTC_get_ss(void) {
    RTC_Wait_sync();
    return (uint16_t)(RTC->SSR & RTC_SSR_SS_Msk);
}

static void pwr_clock_enable(void) {
	set_reg(&(dev()->sys->rcc->APB1ENR1), RCC_APB1ENR1_PWREN);
}

static void pwr_clock_disable(void) {
	clear_reg(&(dev()->sys->rcc->APB1ENR1), RCC_APB1ENR1_PWREN);
}

static void RTC_clock_enable(void) {
    RTC_Write_enable();
    set_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_RTCEN);
    RTC_Write_disable();
}

static void RTC_clock_disable(void) {
    RTC_Write_enable();
    clear_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_RTCEN);
    RTC_Write_disable();
}

static void RTC_nvic_config(uint8_t config) {
    switch(config) {
        case RTC_ENABLE_WAKEUP:  NVIC_EnableIRQ(RTC_WKUP_IRQn);   break;
        case RTC_ENABLE_ALARM:   NVIC_EnableIRQ(RTC_Alarm_IRQn);  break;
        case RTC_DISABLE_WAKEUP: NVIC_DisableIRQ(RTC_WKUP_IRQn);  break;
        case RTC_DISABLE_ALARM:  NVIC_DisableIRQ(RTC_Alarm_IRQn); break;
    }
}

static void RTC_irq_enable(uint8_t type) {
    RTC_Write_enable();
    RTC_Reg_unlock();
    switch (type) {
        case RTC_IRQ_ALARM:  set_reg(&(RTC->CR), RTC_CR_ALRAIE); break;
        case RTC_IRQ_WAKEUP: set_reg(&(RTC->CR), RTC_CR_WUTIE);  break;
        case RTC_IRQ_TS:     set_reg(&(RTC->CR), RTC_CR_TSIE);   break;
        case RTC_IRQ_TAMPER: set_reg(&(TAMP->IER), TAMP_IER_TAMP1IE); break;
    }
    RTC_Write_disable();
}

static void RTC_irq_disable(uint8_t type) {
    RTC_Write_enable();
    RTC_Reg_unlock();
    switch (type) {
        case RTC_IRQ_ALARM:  clear_reg(&(RTC->CR), RTC_CR_ALRAIE); break;
        case RTC_IRQ_WAKEUP: clear_reg(&(RTC->CR), RTC_CR_WUTIE);  break;
        case RTC_IRQ_TS:     clear_reg(&(RTC->CR), RTC_CR_TSIE);   break;
        case RTC_IRQ_TAMPER: clear_reg(&(TAMP->IER), TAMP_IER_TAMP1IE); break;
    }
    RTC_Write_disable();
}

/*** LSE ***/
static void RTC_inic(void) {
    pwr_clock_enable();
    RTC_Write_enable();

    if (get_field_value(dev()->sys->rcc->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos) == RTCSEL_NONE) {
        set_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_BDRST);
        clear_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_BDRST);
        
        set_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_LSEON);
        uint32_t timeout = RTC_INIT_TIMEOUT;
        while(!get_field_value(dev()->sys->rcc->BDCR, RCC_BDCR_LSERDY_Msk, RCC_BDCR_LSERDY_Pos) && --timeout);

        if (timeout == 0) { 
            set_reg(&(dev()->sys->rcc->CSR), RCC_CSR_LSION);
            while(!get_field_value(dev()->sys->rcc->CSR, RCC_CSR_LSIRDY_Msk, RCC_CSR_LSIRDY_Pos));
            write_field_value(&(dev()->sys->rcc->BDCR), RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos, RTCSEL_LSI);
        } else {
            write_field_value(&(dev()->sys->rcc->BDCR), RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos, RTCSEL_LSE);
        }
    }
    
    RTC_clock_enable();
    RTC_Wait_sync();
}


/*** LSI ***
static void RTC_inic(void) {
    pwr_clock_enable();          // Turn on PWR interface clock
    RTC_Write_enable();    // Unprotect the backup domain registers (PWR->CR1 |= PWR_CR1_DBP)

    // Force a clean, deterministic Backup Domain Reset to unlock the routing multiplexer
    set_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_BDRST);
    clear_reg(&(dev()->sys->rcc->BDCR), RCC_BDCR_BDRST);

    // Turn on the internal LSI (Safe, stable internal clock source)
    set_reg(&(dev()->sys->rcc->CSR), RCC_CSR_LSION);
    while(!get_reg_field_value(dev()->sys->rcc->CSR, RCC_CSR_LSIRDY_Msk, RCC_CSR_LSIRDY_Pos));

    // Route RTC to use LSI (0x02)
    write_reg_field_value(&(dev()->sys->rcc->BDCR), RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_Pos, 0x02U);

    // Enable the RTC peripheral clock
    RTC_clock_enable();        // (RCC->BDCR |= RCC_BDCR_RTCEN)

    RTC_Write_disable();   // Re-lock backup protection structures
    RTC_Wait_sync();       // Clear and sync calendar shadow registers
}
***/

/*** Under-The-Hood Private Utilities ***/

static void RTC_Write_enable(void) {
    set_reg(&(dev()->sys->pwr->CR1), PWR_CR1_DBP);
}

static void RTC_Write_disable(void) {
    clear_reg(&(dev()->sys->pwr->CR1), PWR_CR1_DBP);
}

static void RTC_Reg_unlock(void) {
    RTC->WPR = RTC_KEY1;
    RTC->WPR = RTC_KEY2;
}

/**
static void RTC_Wait_sync(void) {
    clear_reg(&(RTC->ICSR), RTC_ICSR_RSF); 
    while(!get_reg_field_value(RTC->ICSR, RTC_ICSR_RSF_Msk, RTC_ICSR_RSF_Pos));
}
**/

static void RTC_Wait_sync(void) {
    clear_reg(&(RTC->ICSR), RTC_ICSR_RSF);
    volatile uint32_t timeout = 50000U; // Hardware safety counter
    while(!get_field_value(RTC->ICSR, RTC_ICSR_RSF_Msk, RTC_ICSR_RSF_Pos) && --timeout);
}

static void RTC_Set_tr(uint32_t value) {
    RTC_Write_enable();
    RTC_Reg_unlock();
    
    set_reg(&(RTC->ICSR), RTC_ICSR_INIT);
    uint32_t timeout = RTC_INIT_TIMEOUT;
    while(!get_field_value(RTC->ICSR, RTC_ICSR_INITF_Msk, RTC_ICSR_INITF_Pos) && --timeout);
    
    if (timeout > 0) {
        RTC->TR = value;
    }
    
    clear_reg(&(RTC->ICSR), RTC_ICSR_INIT);
    RTC_Write_disable();
}

static void RTC_Set_dr(uint32_t value) {
    RTC_Write_enable();
    RTC_Reg_unlock();
    
    set_reg(&(RTC->ICSR), RTC_ICSR_INIT);
    uint32_t timeout = RTC_INIT_TIMEOUT;
    while(!get_field_value(RTC->ICSR, RTC_ICSR_INITF_Msk, RTC_ICSR_INITF_Pos) && --timeout);
    
    if (timeout > 0) {
        RTC->DR = value;
    }
    
    clear_reg(&(RTC->ICSR), RTC_ICSR_INIT);
    RTC_Write_disable();
}

static uint8_t _rtc_bcd2dec(uint8_t num) {
    return (num >> 4) * 10 + (num & 0x0F);
}

static uint8_t _rtc_dec2bcd(uint8_t num) {
    return ((num / 10) << 4) | (num % 10);
}

/*** RTC GET ***/
static RTC_get get_setup = {
	.year = RTC_get_year,
	.month = RTC_get_month,
	.weekday = RTC_get_weekday,
	.day = RTC_get_day,
	.hour = RTC_get_hour,
	.minute = RTC_get_minute,
	.second = RTC_get_second,
	.ss = RTC_get_ss,
	.dr = RTC_dr,
	.tr = RTC_tr
};
/*** RTC SET ***/
static RTC_set set_setup = {
	.year = RTC_set_year,
	.month = RTC_set_month,
	.weekday = RTC_set_weekday,
	.day = RTC_set_day,
	.hour = RTC_set_hour,
	.minute = RTC_set_minute,
	.second = RTC_set_second
};
/*** RTC V-TABLE ***/
static RTC_run run_setup = {
	.dr2vec = RTC_dr2vec,
	.tr2vec = RTC_tr2vec,
	.bkp_write = bkp_write,
	.bkp_read = bkp_read,
	.pwr_clock_enable = pwr_clock_enable,
	.pwr_clock_disable = pwr_clock_disable,
	.clock_enable = RTC_clock_enable,
	.clock_disable = RTC_clock_disable,
	.inic = RTC_inic,
	.nvic = RTC_nvic_config,
	.irq_enable = RTC_irq_enable,
	.irq_disable = RTC_irq_disable,
};
/*** RTC CALLBACK ***/
static RTC_callback callback_setup = {NULL, NULL, NULL, NULL, NULL};
/*** RTC HANDLER ***/
static STM32G473_RTC_Handler rtc_instance =
{
	.get = &get_setup,
	.set = &set_setup,
	.run = &run_setup,
	.callback = &callback_setup
};
/*** RTC ACCESSOR FUNCTION ***/
STM32G473_RTC_Handler* rtc(void) { return (STM32G473_RTC_Handler*)&rtc_instance; }

const char* WeekDay_String(uint8_t weekday_n)
{
	static const char* days[] = {"N/A", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	return (weekday_n <= 7) ? days[weekday_n] : days[0];
}

/*** Modern Vector Routing Mappings ***/
void RTC_WKUP_IRQHandler(void)
{
	if (RTC->SR & RTC_SR_WUTF) {
		if(rtc_instance.callback->WakeUp) 
			rtc_instance.callback->WakeUp();
		RTC->SCR = RTC_SCR_CWUTF;
	}
}
void RTC_Alarm_IRQHandler(void)
{
	if (RTC->SR & RTC_SR_ALRAF)
	{
		if(rtc_instance.callback->Alarm) 
			rtc_instance.callback->Alarm();
		RTC->SCR = RTC_SCR_CALRAF;
	}
}

