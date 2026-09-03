/******************************************************************************
	rtc_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "stm32x_irq.h"
#include <stm32g4xx.h>

/*** Modern Vector Routing Mappings ***/
void RTC_WKUP_IRQHandler(void)
{
	if (RTC->SR & RTC_SR_WUTF) {
		if(irq()->rtc->WakeUp)
			irq()->rtc->WakeUp();
		RTC->SCR = RTC_SCR_CWUTF;
	}
}
void RTC_Alarm_IRQHandler(void)
{
	if (RTC->SR & RTC_SR_ALRAF)
	{
		if(irq()->rtc->Alarm)
			irq()->rtc->Alarm();
		RTC->SCR = RTC_SCR_CALRAF;
	}
}

/*** EOF ***/

