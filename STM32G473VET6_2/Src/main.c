/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License

Button1 - PD8
Button2 - PD9
Button3 - PD10
Button4 - PD11
Button5 - PD12
Button6 - PD13
	ST8879V
SCL - PC10
SDA - PC12
RST - PC9
DC - PC8
CS - PC7
	L293D
IN1 M1.1 - PA6
IN2 M1.2 - PA7
EN - PE0
************************************************************************/
#include "stm32gxxx_rcc.h"
#include "arm_systick.h"
#include "stm32gxxx_tim1.h"
#include "st7789.h"
#include "function.h"
#include "stm32gxxx_rtc.h"
#include "explode.h"
#include "stm32gxxx_adc1.h"
#include "l293d.h"
#include <string.h>

#define BG_colour 0x0000

// Define a unified bitmask for PD8, PD9, PD10, PD11, PD12, and PD13
// Binary: 0011 1111 0000 0000 -> Hex: 0x3F00
#define BTN_ALL_PINS_MASK    (0x3FU << 8)

// Map operations to their isolated bits for processing
#define BTN_MODE_PIN         (1UL << 8)   // PD8
#define BTN_UP_PIN           (1UL << 9)   // PD9
#define BTN_DOWN_PIN         (1UL << 10)  // PD10
#define BTN_FW_PIN           (1UL << 11)  // PD11
#define BTN_RV_PIN           (1UL << 12)  // PD12
#define BTN_SP_PIN           (1UL << 13)  // PD13

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
static L293D_Handler drive;
static uint16_t speed;

void rtc_ui_init(void);
void select_mode(EXPLODE_Handler active_press);
void adjust_active_field(EXPLODE_Handler active_press);
void inc(void);

int main(void)
{
	rcc()->run->inic();
	fpu_enable();
	rtc()->run->inic();

	char str[32];
	char vecD[8]; // for calendar date
	char vecT[8]; // for calendar time
	speed = 530;

	GPIO_clock( dev()->gpio->f, 1 );
	GPIO_hmoder( dev()->gpio->f, 1 << 2, MODE_OUTPUT );
	rtc_ui_init();

	adc1()->run->temp_init();

	EXPLODE_Handler tr = EXPLODE_enable();
	EXPLODE_Handler dr = EXPLODE_enable();

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	drive = l293d_enable(GPIOE, ZERO);

	lcd1.run->start(&lcd1.par);
	lcd1.run->draw_circle(&lcd1.par,220,300,15,ST77XX_CYAN);
	lcd1.run->draw_star5(&lcd1.par,220,300,15,5,ST77XX_GOLD);
	lcd1.run->stop(&lcd1.par);

	while(1)
	{
		if(btn_engine.run->update(&btn_engine.par, dev()->gpio->d->IDR & BTN_ALL_PINS_MASK)) {
			select_mode(btn_engine);
			adjust_active_field(btn_engine);

			switch(ui_state){
			case CFG_IDLE:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Relogio",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_HOUR:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Hora",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_MINUTE:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Minuto",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_DAY:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Dia",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_MONTH:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Mes",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_YEAR:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Ano",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_WEEKDAY:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"Semana",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			case CFG_MAX:
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par,"MAX",10,10,ST77XX_WHITE,BG_colour,7);
				lcd1.run->stop(&lcd1.par);
				break;
			default: break;
			};
		}

		if(btn_engine.par.HL & BTN_FW_PIN) {
			if(toggle(0)){
				drive.run->pwm_forward(&drive.par,speed);
			}else{
				drive.run->stop(&drive.par);
			}
		}

		if(btn_engine.par.HL & BTN_RV_PIN) {
			if(toggle(0)){
				drive.run->pwm_reverse(&drive.par,speed);
			}else{
				drive.run->stop(&drive.par);
			}
		}

		if(btn_engine.par.LL & BTN_SP_PIN) {
			if(ftdelayCycles(1,2500,NULL,inc)){
				lcd1.run->start(&lcd1.par);
				func()->format_string(str,32,"speed: %d",speed);
				lcd1.run->drawstring12x16_size(&lcd1.par,str,15,170,ST77XX_ORANGE,BG_colour,14);
				lcd1.run->stop(&lcd1.par);
				ftdelayReset(1);
			}
		}

		/***/
		if (tr.run->update(&tr.par, rtc()->run->tr()) || dr.run->update(&dr.par, rtc()->run->dr())) {
			rtc()->run->dr2vec(vecD);
			rtc()->run->tr2vec(vecT);

			toggle_hpin(dev()->gpio->f, 1 << 2);

			lcd1.run->start(&lcd1.par);

			func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
			lcd1.run->drawstring24x48_size(&lcd1.par,str,15,80,ST77XX_RED,BG_colour,8);

			func()->float_to_string(adc1()->run->temp_read_celsius(),str,32);
			strcat(str, " C");
			lcd1.run->drawstring16x24_size(&lcd1.par,str,15,200,ST77XX_BLUE,BG_colour,8);

			func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
			lcd1.run->drawstring16x24(&lcd1.par,str,10,240,ST77XX_GREEN,BG_colour);

			lcd1.run->drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,300,ST77XX_WHITE,BG_colour,10);

			lcd1.run->stop(&lcd1.par);
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
            	t_hr = rtc()->run->get_hour();
            	t_hr   = LIMIT_INC(t_hr,   23, 0);
            	rtc()->run->set_hour(t_hr);
            	break;
            case CFG_MINUTE:
            	t_min = rtc()->run->get_minute();
            	t_min  = LIMIT_INC(t_min,  59, 0);
            	rtc()->run->set_minute(t_min);
            	break;
            case CFG_DAY:
            	t_day = rtc()->run->get_day();
            	t_day  = LIMIT_INC(t_day,  31, 1);
            	rtc()->run->set_day(t_day);
            	break;
            case CFG_MONTH:
            	t_mth = rtc()->run->get_month();
            	t_mth  = LIMIT_INC(t_mth,  12, 1);
            	rtc()->run->set_month(t_mth);
            	break;
            case CFG_YEAR:
            	t_yr = rtc()->run->get_year();
            	t_yr   = LIMIT_INC(t_yr,   99, 0);
            	rtc()->run->set_year(t_yr);
            	break;
            case CFG_WEEKDAY:
            	t_wday = rtc()->run->get_weekday();
            	t_wday = LIMIT_INC(t_wday,  7, 1);
            	rtc()->run->set_weekday(t_wday);
            	break;
            default: break;
        }
    } else if (active_press.par.HL & BTN_DOWN_PIN) {
        switch (ui_state) {
            case CFG_HOUR:
            	t_hr = rtc()->run->get_hour();
            	t_hr   = LIMIT_DEC(t_hr,   23, 0);
            	rtc()->run->set_hour(t_hr);
            	break;
            case CFG_MINUTE:
            	t_min = rtc()->run->get_minute();
            	t_min  = LIMIT_DEC(t_min,  59, 0);
            	rtc()->run->set_minute(t_min);
            	break;
            case CFG_DAY:
            	t_day = rtc()->run->get_day();
            	t_day  = LIMIT_DEC(t_day,  31, 1);
            	rtc()->run->set_day(t_day);
            	break;
            case CFG_MONTH:
            	t_mth = rtc()->run->get_month();
            	t_mth  = LIMIT_DEC(t_mth,  12, 1);
            	rtc()->run->set_month(t_mth);
            	break;
            case CFG_YEAR:
            	t_yr = rtc()->run->get_year();
            	t_yr   = LIMIT_DEC(t_yr,   99, 0);
            	rtc()->run->set_year(t_yr);
            	break;
            case CFG_WEEKDAY:
            	t_wday = rtc()->run->get_weekday();
            	t_wday = LIMIT_DEC(t_wday,  7, 1);
            	rtc()->run->set_weekday(t_wday);
            	break;
            default: break;
        }
    }
}

void inc(void) {
	increment(&speed, 530, drive.par.tim_arr);
}
