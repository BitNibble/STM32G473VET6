/******************************************************************************
	rtc_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "stm32x_irq.h"
#include <stm32g4xx.h>

void RTC_Alarm_IRQHandler(void)
{
    uint32_t sr = RTC->SR;

    /* Alarm A / Alarm B */
    if (sr & (RTC_SR_ALRAF | RTC_SR_ALRBF))
    {
        RTC->SCR = (sr & (RTC_SR_ALRAF | RTC_SR_ALRBF));
        (void)RTC->SR;

        if (irq()->rtc->Alarm != NULL)
        {
            irq()->rtc->Alarm();
        }
        else
        {
            rtc_alarm_callback();
        }
    }
}

void RTC_WKUP_IRQHandler(void)
{
    if (RTC->SR & RTC_SR_WUTF)
    {
        RTC->SCR = RTC_SCR_CWUTF;
        (void)RTC->SR;

        if (irq()->rtc->WakeUp != NULL)
        {
            irq()->rtc->WakeUp();
        }
        else
        {
            rtc_wakeup_callback();
        }
    }
}

void RTC_TAMP_LSECSS_IRQHandler(void)
{
    uint32_t rtc_sr  = RTC->SR;
    uint32_t tamp_sr = TAMP->SR;

    /* TimeStamp Overrun (check before clearing TSF) */
    if (rtc_sr & RTC_SR_TSOVF)
    {
        RTC->SCR = RTC_SCR_CTSOVF;
        (void)RTC->SR;

        if (irq()->rtc->Overrun != NULL)
        {
            irq()->rtc->Overrun();
        }
        else
        {
            rtc_overrun_callback();
        }
    }

    /* TimeStamp */
    if (rtc_sr & RTC_SR_TSF)
    {
        RTC->SCR = RTC_SCR_CTSF;
        (void)RTC->SR;

        if (irq()->rtc->TimeStamp != NULL)
        {
            irq()->rtc->TimeStamp();
        }
        else
        {
            rtc_timestamp_callback();
        }
    }

    /* Tamper (TAMP1 / TAMP2 / TAMP3) */
    if (tamp_sr & (TAMP_SR_TAMP1F | TAMP_SR_TAMP2F | TAMP_SR_TAMP3F))
    {
        TAMP->SCR = (tamp_sr & (TAMP_SR_TAMP1F | TAMP_SR_TAMP2F | TAMP_SR_TAMP3F));
        (void)TAMP->SR;

        if (irq()->rtc->Tamper != NULL)
        {
            irq()->rtc->Tamper();
        }
        else
        {
            rtc_tamper_callback();
        }
    }
}

/*** EOF ***/
