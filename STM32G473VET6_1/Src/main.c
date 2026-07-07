/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
	ST8879
SCL - PC10
SDA - PC12
RST - PC9
DC - PC8
CS - PC7
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

// Retrieve global reference to layout instance
static const USARTG4_Handle* Serial1;
char* token[4];

char usart_1[USART1_RX_SIZE];
uint8_t str[32];
char* ptr = NULL;

void tim1_blink_setup(void)
{
    tim1()->run->init_by_ticks(119,1999999);
    tim1()->run->nvic_u_enable(2);
    tim1()->run->start();
}
void tim1_u_callback(void)
{
	toggle_hpin(dev()->gpio->f, 1 << 2);
}

void application_init(void)
{
    // Define target pins for TIM1 CH1, CH2, CH3 (PA8 | PA9 | PA10)
    uint16_t tim1_pins = (1UL << 8) | (1UL << 9) | (1UL << 10);
    // 1. Fire up the clock gating blocks through the accessors
    GPIO_clock(dev()->gpio->a, 1);
    // 2. Multi-pin batch setup: Mode = Alternate Function (0x02)
    GPIO_hmoder(dev()->gpio->a, tim1_pins, MODE_AF);
    // 3. Speed selection: Very High Speed (0x03) for crisp PWM edges
    GPIO_hospeed(dev()->gpio->a, tim1_pins, 3);
    // 4. Batch assign Alternate Function 6 (AF6 = TIM1) across your target array
    GPIO_haf(dev()->gpio->a, tim1_pins, 6);
    // 5. Initialize TIM1 to fire at a clean 20kHz target using your frequency tool
    tim1()->run->init_by_freq(0, 20000);
    // 6. Set initial 50% duty cycle pulses (assuming ARR configured via auto calculation)
    tim1()->run->config_pwm(TIM1_CH1, PWM_MODE_1, 2000);
    tim1()->run->config_pwm(TIM1_CH2, PWM_MODE_1, 2000);
    tim1()->run->config_pwm(TIM1_CH3, PWM_MODE_1, 2000);

    // 7. Fire up execution tracking!
    tim1()->run->start();
}

int main(void)
{
	rcc()->run->inic();
	fpu_enable();
	rtc()->run->inic();

	//char str[32];
	//char vecD[8]; // for calendar date
	//char vecT[8]; // for calendar time

	GPIO_clock( dev()->gpio->f, 1 );
	GPIO_hmoder( dev()->gpio->f, 1 << 2, MODE_OUTPUT );

	//clear_pin(dev()->gpio->f, 1 << 2);

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	Serial1 = usart1();

	Serial1->run->init();

	// 2. CRITICAL: Turn on the receiver engine and enable the DMA stream!
	Serial1->run->start_rx();

	Serial1->run->send((uint8_t *) "Received:", 10);

	lcd1.run->start(&lcd1.par);
	lcd1.run->draw_circle(&lcd1.par,200,80,15,ST77XX_CYAN);
	lcd1.run->draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);

	lcd1.run->stop(&lcd1.par);

	tim1_blink_setup();
	tim1()->irq->u = tim1_u_callback;

	while(1)
	{
		lcd1.run->start(&lcd1.par);
		lcd1.run->drawstring16x24_size(&lcd1.par,"LeD ON",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.run->stop(&lcd1.par);
		_delay_ms(500);
		//toggle_hpin( dev()->gpio->f, 1 << 2 );
		lcd1.run->start(&lcd1.par);
		lcd1.run->drawstring16x24_size(&lcd1.par,"LED OFF",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.run->drawstring24x48_size( &lcd1.par, func()->ui32toa(get_sysclk()), 10, 100, ST77XX_MAGENTA, BG_colour, 10 );
		//lcd1.run->drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_source()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		//lcd1.run->drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_vco_out()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		lcd1.run->stop(&lcd1.par);
		_delay_ms(500);
		//toggle_hpin( dev()->gpio->f, 1 << 2 );

		lcd1.run->start(&lcd1.par);
		//func()->format_string(str,32,"%u", 60);
		//ptr = function_ui16toa(60);
		//ptr = func()->ui16toa(60);
		ptr = func()->ui16toa(rtc()->get_par->second());
		lcd1.run->drawstring16x24_size(&lcd1.par,ptr,10,200,ST77XX_RED,BG_colour,2);
		//lcd1.drawstring16x24(&lcd1.par,"hello",10,200,ST77XX_RED,ST77XX_GREEN);
		lcd1.run->stop(&lcd1.par);

		/***
		rtc()->run->dr2vec(vecD);
		rtc()->run->tr2vec(vecT);

		lcd1.run->start(&lcd1.par);
		func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
		lcd1.run->drawstring16x24(&lcd1.par,str,10,150,ST77XX_BLACK,ST77XX_GREEN);

		lcd1.run->drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,200,ST77XX_BLACK,ST77XX_GREEN,7);

		func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
		lcd1.run->drawstring24x48_size(&lcd1.par,str,15,70,ST77XX_RED,ST77XX_GREEN,8);
		lcd1.run->stop(&lcd1.par);
		***/

		if (Serial1->run->read_str_size(usart_1, sizeof(usart_1)) > 0) {
			// Clear prior pointers to avoid parsing contamination
			memset(token, 0, sizeof(token));

			// Extract command fragments based on carriage return sequences
			func()->parse_string(usart_1, 4, token, "\r\n");

			// Confirm token[0] was successfully parsed before utilizing it
			if (token[0] != NULL) {
				lcd1.run->start(&lcd1.par);
				lcd1.run->drawstring16x24_size(&lcd1.par, token[0], 10, 160, ST77XX_RED, BG_colour, 12);
				lcd1.run->stop(&lcd1.par);

				// Safe command structure execution context
				if (strcmp(token[0], "s00") == 0) {
					toggle_hpin(dev()->gpio->f, 1 << 2);
					Serial1->run->send((uint8_t *) "ACK: Pin Toggled\r\n", 18);
				}
			}
		}

	}
}

