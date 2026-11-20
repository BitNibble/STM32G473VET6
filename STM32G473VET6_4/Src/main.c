/************************************************************************
	MAIN - CORDIC Generative Art Canvas
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6 + ST7789 (SPI3) + HC-05 (USART1)
************************************************************************/
#include "stm32gxxx_rcc.h"
#include "arm_systick.h"
#include "stm32gxxx_tim1.h"
#include "st7789.h"
#include "function.h"
#include "stm32gxxx_rtc.h"
#include "stm32gxxx_usart1.h"
#include <string.h>

#define BG_colour 0x0000

static const USARTG4_Handle* Serial1;
char* token[4];
char usart_1[USART1_RX_SIZE];
char str[32];

static volatile uint32_t phase = 0;

/* Canvas state */
static uint32_t t_a = 0, t_b = 0;
static uint32_t step_a = 14316557U;   // 2:3 Lissajous default
static uint32_t step_b = 21474836U;
static int16_t  prev_x = -1, prev_y = -1;
static uint8_t  line_mode = 1;        // 1 = connected lines, 0 = dots
static uint8_t  color_idx = 0;

static const uint16_t palette[] = {
    ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_GOLD, ST77XX_GREEN, ST77XX_ORANGE, ST77XX_RED
};
#define PALETTE_LEN (sizeof(palette) / sizeof(palette[0]))

void tim1_blink_setup(void)
{
    tim1()->run->init_by_ticks(23, 19999); // 100 Hz
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM1->CR2   &= ~TIM_CR2_CCPC;
    TIM1->CR1   |= TIM_CR1_ARPE;
    tim1()->run->nvic_u_enable(2);
    tim1()->run->nvic_cc1_enable(2);
    tim1()->run->start();
}

void tim_u_callback(void)
{
    phase += 21474837U;
    cordic()->q31(CORDIC_SIN, (cordic_arg){ .arg_1 = phase });
    int32_t sine = cordic()->par->out_1;
    TIM1->CCR1 = exe()->q31_to_pwm(sine, TIM1->ARR);
    gpio()->set_hpin(GPIOF, 1 << 2);
}

void tim_cc1_callback(void)
{
    gpio()->clear_hpin(GPIOF, 1 << 2);
}

static void draw_hud(ST7789 *lcd)
{
    lcd->run->start(&lcd->par);
    lcd->run->drawstring8x12(&lcd->par, "CMD: clr | col | line | f1..f3", 0, 6, ST77XX_WHITE, BG_colour);
    lcd->run->stop(&lcd->par);
}

int main(void)
{
    rcc()->run->init();
    dev()->run->enable_fpu();
    rtc()->run->init();

    /* Enable CORDIC BEFORE starting TIM1 ISR */
    dev()->enable_peripheral(CORDIC);

    dev()->enable_peripheral(GPIOF);
    gpio()->hmoder(GPIOF, MODE_OUTPUT, 1 << 2);
    gpio()->clear_pin(GPIOF, 2);

    ST7789 lcd1 = st7789_enable(SPI3, 7, 8, 9, NULL);

    Serial1 = usart1();
    Serial1->run->init(Serial1->par);
    Serial1->run->start_rx();
    Serial1->run->send((uint8_t *)"Canvas Ready\r\n", 14);

    tim1_blink_setup();
    irq()->timer->tim1->update = tim_u_callback;
    irq()->timer->tim1->cc1    = tim_cc1_callback;

    draw_hud(&lcd1);

    uint8_t time[10];
    uint8_t last_sec = 0xFF;

    while (1)
    {
        /* 1. Plot 12 CORDIC parametric steps per loop */
        lcd1.run->start(&lcd1.par);
        for (uint8_t k = 0; k < 12; k++)
        {
            t_a += step_a;
            t_b += step_b;

            NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
            cordic()->q31(CORDIC_COS, (cordic_arg){ .arg_1 = t_a });
            int32_t x_q31 = cordic()->par->out_1;

            cordic()->q31(CORDIC_SIN, (cordic_arg){ .arg_1 = t_b });
            int32_t y_q31 = cordic()->par->out_1;
            NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

            int16_t px = 120 + (int16_t)(((int64_t)x_q31 * 95) >> 31);
            int16_t py = 165 + (int16_t)(((int64_t)y_q31 * 95) >> 31);

            if (line_mode && prev_x >= 0) {
                lcd1.run->draw_line(&lcd1.par, prev_x, prev_y, px, py, palette[color_idx]);
            } else {
                lcd1.run->draw_pixel(&lcd1.par, px, py, palette[color_idx]);
            }

            prev_x = px;
            prev_y = py;
        }
        lcd1.run->stop(&lcd1.par);

        /* 2. Update RTC clock header once per second (zero flicker) */
        rtc()->run->tr2vec(time);
        if (time[5] != last_sec) {
            last_sec = time[5];
            func()->format_string(str, 32, "%d%d:%d%d:%d%d",
                time[0], time[1], time[2], time[3], time[4], time[5]);
            lcd1.run->start(&lcd1.par);
            lcd1.run->drawstring16x24_size(&lcd1.par, str, 56, 26, ST77XX_GOLD, BG_colour, 8);
            lcd1.run->stop(&lcd1.par);
        }

        /* 3. Instant HC-05 Bluetooth command handling */
        if (Serial1->run->read_str_size(usart_1, sizeof(usart_1)) > 0)
        {
            memset(token, 0, sizeof(token));
            func()->parse_string(usart_1, 4, token, "\r\n");

            if (token[0] != NULL)
            {
                if (strcmp(token[0], "clr") == 0) {
                    lcd1.run->fill_screen(&lcd1.par, BG_colour);
                    prev_x = -1;
                    draw_hud(&lcd1);
                    Serial1->run->send((uint8_t *)"Cleared\r\n", 9);
                }
                else if (strcmp(token[0], "col") == 0) {
                    color_idx = (color_idx + 1) % PALETTE_LEN;
                    Serial1->run->send((uint8_t *)"Color changed\r\n", 15);
                }
                else if (strcmp(token[0], "line") == 0) {
                    line_mode ^= 1;
                    prev_x = -1;
                    Serial1->run->send((uint8_t *)"Mode toggled\r\n", 14);
                }
                else if (strcmp(token[0], "f1") == 0) {
                    step_a = 14316557U; step_b = 21474836U; prev_x = -1; // 2:3
                }
                else if (strcmp(token[0], "f2") == 0) {
                    step_a = 10737418U; step_b = 25053975U; prev_x = -1; // 3:7
                }
                else if (strcmp(token[0], "f3") == 0) {
                    step_a = 17895697U; step_b = 21474836U; prev_x = -1; // 5:6
                }
            }
        }
    }
}

/*** EOF ***/
