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

	EXPLODE_Handler seconds = EXPLODE_enable();

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	lcd1.start(&lcd1.par);
	lcd1.draw_circle(&lcd1.par,200,80,15,ST77XX_CYAN);
	lcd1.draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);
	lcd1.stop(&lcd1.par);

	while(1)
	{
		if(btn_engine.run->update(&btn_engine.par, dev()->gpio->d->IDR & BTN_ALL_PINS_MASK)) {
			select_mode(btn_engine);
			adjust_active_field(btn_engine);

			lcd1.start(&lcd1.par);
			lcd1.drawstring16x24(&lcd1.par,func()->ui16toa(ui_state),10,10,ST77XX_WHITE,BG_colour);
			lcd1.stop(&lcd1.par);
		}

		/***/
		rtc()->dr2vec(vecD);
		rtc()->tr2vec(vecT);


		if (seconds.run->update(&seconds.par, vecT[5])) {
			toggle_hpin(dev()->gpio->f, 1 << 2);

			lcd1.start(&lcd1.par);
			func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
			lcd1.drawstring16x24(&lcd1.par,str,10,190,ST77XX_WHITE,BG_colour);

			lcd1.drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,240,ST77XX_WHITE,BG_colour,10);

			func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
			lcd1.drawstring24x48_size(&lcd1.par,str,15,100,ST77XX_RED,BG_colour,8);
			lcd1.stop(&lcd1.par);

		}

	}
}

