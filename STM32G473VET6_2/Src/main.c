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

// Unified bitmask for PD8 through PD13 (0x3F00)
#define BTN_ALL_PINS_MASK    (0x3FU << 8)

// Pin isolation maps
#define BTN_MODE_PIN         (1UL << 8)   // PD8
#define BTN_UP_PIN           (1UL << 9)   // PD9
#define BTN_DOWN_PIN         (1UL << 10)  // PD10
#define BTN_FW_PIN           (1UL << 11)  // PD11
#define BTN_RV_PIN           (1UL << 12)  // PD12
#define BTN_SP_PIN           (1UL << 13)  // PD13

// Toggle indices assigned cleanly to prevent overlapping array index writes
#define TOGGLE_INDEX     0U

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

static const char *state_name[] = {
    "Relogio",
    "Hora",
    "Minuto",
    "Dia",
    "Mes",
    "Ano",
    "Semana",
    "MAX"
};

static ui_state_t ui_state = CFG_IDLE;
static EXPLODE_Handler btn_engine;
static L293D_Handler drive;
static uint16_t speed;

void rtc_ui_init(void);
void select_mode(EXPLODE_Handler active_press);
void adjust_active_field(EXPLODE_Handler active_press);
void speed_inc(void);
void blink(void);

int main(void)
{
    rcc()->run->inic();
    dev()->enable->fpu();
    dev()->enable->battery_charging();
    rtc()->run->inic();

    char str[32];
    char vecD[8]; // calendar date
    char vecT[8]; // calendar time
    speed = 530;
    uint16_t idle_colour = 0x0000;

    dev()->enable->gpiof();
    gpio()->moder(GPIOF, MODE_OUTPUT, 2);

    rtc_ui_init();
    adc1()->run->temp_init();

    EXPLODE_Handler tr = EXPLODE_enable();
    EXPLODE_Handler dr = EXPLODE_enable();

    ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
    (void) lcd1;

    drive = l293d_enable(GPIOE, ZERO);

    dev()->enable->tim1();
    tim1()->par->prescaler = 119;
    tim1()->par->autoreload = 1999999;
    tim1()->run->init_by_ticks(tim1()->par->prescaler, tim1()->par->autoreload);
    tim1()->run->nvic_u_enable(3);
    irq()->timer->tim1->update = blink;
    //tim1()->run->start();

    lcd1.run->start(&lcd1.par);
    lcd1.run->draw_circle(&lcd1.par, 220, 300, 15, ST77XX_CYAN);
    lcd1.run->draw_star5(&lcd1.par, 220, 300, 15, 5, ST77XX_GOLD);
    lcd1.run->stop(&lcd1.par);

    while(1)
    {
        // 1. Process Button Transitions & Display Configuration Mode
        if(btn_engine.run->update(&btn_engine.par, dev()->gpio->d->IDR & BTN_ALL_PINS_MASK)) {
            select_mode(btn_engine);
            adjust_active_field(btn_engine);

            lcd1.run->start(&lcd1.par);
            lcd1.run->drawstring16x24_size(&lcd1.par, (char*)state_name[ui_state], 10, 10, ST77XX_WHITE, BG_colour, 7);
            lcd1.run->stop(&lcd1.par);
        }

        // 2. Forward Motor Drive Trigger (Uses dedicated Toggle index 0)
        if(btn_engine.par.HL & BTN_FW_PIN) {
            if(exe()->toggle(TOGGLE_INDEX)){
                drive.run->pwm_forward(&drive.par, speed);
            }else{
                drive.run->stop(&drive.par);
            }
        }

        // 3. Reverse Motor Drive Trigger (Uses dedicated Toggle index 1 to prevent collision)
        if(btn_engine.par.HL & BTN_RV_PIN) {
            if(exe()->toggle(TOGGLE_INDEX)){
                drive.run->pwm_reverse(&drive.par, speed);
            }else{
                drive.run->stop(&drive.par);
            }
        }

        // 4. Safe Fall-Through Delay for Incremental Speed Adjustments
        if(btn_engine.par.LL & BTN_SP_PIN) {
            if(exe()->ftdelayCycles(0, 2500, NULL, speed_inc)){
                lcd1.run->start(&lcd1.par);
                func()->format_string(str, 32, "speed: %d", speed);
                lcd1.run->drawstring12x16_size(&lcd1.par, str, 15, 170, ST77XX_ORANGE, BG_colour, 14);
                lcd1.run->stop(&lcd1.par);
                exe()->ftdelayReset(0);
            }
        }

        // 5. Update Calendar Data & On-Screen Instrumentation
        if (tr.run->update(&tr.par, rtc()->get->tr()) || dr.run->update(&dr.par, rtc()->get->dr())) {
            rtc()->run->dr2vec(vecD);
            rtc()->run->tr2vec(vecT);

            if(!ui_state) {
                lcd1.run->start(&lcd1.par);
                lcd1.run->drawstring16x24_size(&lcd1.par, (char*)state_name[ui_state], 10, 10, idle_colour++, BG_colour, 7);
                lcd1.run->stop(&lcd1.par);
            }

            lcd1.run->start(&lcd1.par);

            func()->format_string(str, 32, "%d%d:%d%d:%d%d", vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
            lcd1.run->drawstring24x48_size(&lcd1.par, str, 15, 80, ST77XX_RED, BG_colour, 8);

            func()->float_to_string(adc1()->run->temp_read_celsius(), str, 32);
            strcat(str, " C");
            lcd1.run->drawstring16x24_size(&lcd1.par, str, 15, 200, ST77XX_BLUE, BG_colour, 8);

            func()->format_string(str, 32, "%d%d-%d%d-20%d%d", vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
            lcd1.run->drawstring16x24(&lcd1.par, str, 10, 240, ST77XX_GREEN, BG_colour);

            lcd1.run->drawstring12x16_size(&lcd1.par, (char*)WeekDay_String(vecD[2]), 10, 300, ST77XX_WHITE, BG_colour, 10);

            lcd1.run->stop(&lcd1.par);
        }

        uint16_t a = 5025;
        uint8_t b = ((U_word)a).par.l;
        (void)b;
    }
}

void rtc_ui_init(void)
{
    gpio()->clock(dev()->gpio->d, 1);
    gpio()->hmoder(dev()->gpio->d, 0, BTN_ALL_PINS_MASK);
    gpio()->hpupd(dev()->gpio->d, 1, BTN_ALL_PINS_MASK);
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
    uint8_t current_val; // Re-use single memory register to optimize the switch-case pipeline

    if (active_press.par.HL & BTN_UP_PIN) {
        switch (ui_state) {
            case CFG_HOUR:
                current_val = rtc()->get->hour();
                rtc()->set->hour(LIMIT_INC(current_val, 23, 0));
                break;
            case CFG_MINUTE:
                current_val = rtc()->get->minute();
                rtc()->set->minute(LIMIT_INC(current_val, 59, 0));
                break;
            case CFG_DAY:
                current_val = rtc()->get->day();
                rtc()->set->day(LIMIT_INC(current_val, 31, 1));
                break;
            case CFG_MONTH:
                current_val = rtc()->get->month();
                rtc()->set->month(LIMIT_INC(current_val, 12, 1));
                break;
            case CFG_YEAR:
                current_val = rtc()->get->year();
                rtc()->set->year(LIMIT_INC(current_val, 99, 0));
                break;
            case CFG_WEEKDAY:
                current_val = rtc()->get->weekday();
                rtc()->set->weekday(LIMIT_INC(current_val, 7, 1));
                break;
            default: break;
        }
    } else if (active_press.par.HL & BTN_DOWN_PIN) {
        switch (ui_state) {
            case CFG_HOUR:
                current_val = rtc()->get->hour();
                rtc()->set->hour(LIMIT_DEC(current_val, 23, 0));
                break;
            case CFG_MINUTE:
                current_val = rtc()->get->minute();
                rtc()->set->minute(LIMIT_DEC(current_val, 59, 0));
                break;
            case CFG_DAY:
                current_val = rtc()->get->day();
                rtc()->set->day(LIMIT_DEC(current_val, 31, 1));
                break;
            case CFG_MONTH:
                current_val = rtc()->get->month();
                rtc()->set->month(LIMIT_DEC(current_val, 12, 1));
                break;
            case CFG_YEAR:
                current_val = rtc()->get->year();
                rtc()->set->year(LIMIT_DEC(current_val, 99, 0));
                break;
            case CFG_WEEKDAY:
                current_val = rtc()->get->weekday();
                rtc()->set->weekday(LIMIT_DEC(current_val, 7, 1));
                break;
            default: break;
        }
    }
}

void speed_inc(void) {
    exe()->increment(&speed, 530, drive.par.tim_arr);
}

void blink(void){
    // Keep interrupt linear and lightweight
    gpio()->toggle_hpin(dev()->gpio->f, 1 << 2);
}

/*** EOF ***/

