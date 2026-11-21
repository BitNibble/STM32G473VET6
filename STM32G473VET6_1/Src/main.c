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
	USART
TX - GPIOA9
RX - GPIOA10
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
static const USART1_Handle* Serial1;
char* token[4];

char usart_1[USART1_RX_SIZE];
char str[32];
char* ptr = NULL;

static volatile uint32_t phase;
static volatile uint8_t capture = 0;
static volatile uint32_t val;

void tim1_blink_setup(void)
{
	dev()->enable_peripheral(TIM1);
	//50hz-(4799,199)
	//100Hz-(23,19999)
	//500Hz-(23,3999)
	//200Hz-(23,9999)
	//200HZ-(0,239999)
	//2Khz-(23,999)
    tim1()->run->init_by_ticks(23,19999);
    // 1. Enable the Output Compare 1 Preload (OC1PE)
    // This moves updates from immediate execution to buffering until the UEV.
    TIM1->CCMR1 |= TIM_CCMR1_OC1PE;

    // 2. Ensure Capture/Compare Preload Control (CCPC) is disabled in CR2
    // This guarantees that the shadow registers update on UEV, NOT on a COM (Commutation) event.
    TIM1->CR2 &= ~TIM_CR2_CCPC;

    // Enable Auto-Reload Preload (ARPE) in Control Register 1
    TIM1->CR1 |= TIM_CR1_ARPE;

    //tim1()->run->nvic_u_enable(2);
    tim1()->run->interrupt_u_enable();
    dev()->enable_irq(TIM1_UP_TIM16_IRQn);

    //tim1()->run->nvic_cc1_enable(2);
    tim1()->run->interrupt_cc1_enable();
    dev()->enable_irq(TIM1_CC_IRQn);

    tim1()->run->start();
}

void tim_u_callback(void)
{
	cordic_arg dimmer = { .arg_1 = phase };

	//50hz   -85899346U
	//100Hz  -42949673U - 1hz
	//100Hz  -21474837U  - 0.5Hz
	//500Hz  -8589935U
	//200Hz  -21474836U
	//200HZ  -10737418U
	//200Hz  -5368709U
	//2Khz   -2147484U
    phase += 21474837U ;
    cordic()->q31( CORDIC_SIN, &dimmer);
    int32_t sine = dimmer.out_1;
    TIM1->CCR1 = exe()->q31_to_pwm(sine, TIM1->ARR);

    gpio()->set_hpin(GPIOF, 1 << 2);
    //gpio()->toggle_hpin(GPIOF, 1 << 2);
}


void tim_cc1_callback(){
	//gpio()->toggle_hpin(GPIOF, 1 << 2);
	gpio()->clear_hpin(GPIOF, 1 << 2);
}

int main(void)
{
	rcc()->run->init();
	dev()->run->enable_fpu();
	rtc()->run->init();

	dev()->enable_peripheral(GPIOF);
	gpio()->hmoder( GPIOF, MODE_OUTPUT, 1 << 2 );

	gpio()->clear_pin(GPIOF, 2);

	ST7789_Handle lcd1 = st7789_enable(SPI3, 7, 8, 9, NULL);
	(void) lcd1;

	Serial1 = usart1();

	Serial1->run->init(Serial1->par);

	// 2. CRITICAL: Turn on the receiver engine and enable the DMA stream!
	Serial1->run->start_rx();

	Serial1->run->send((uint8_t *) "Received:", 10);

	lcd1.run->start(&lcd1.par);
	lcd1.run->draw_circle(&lcd1.par,200,80,15,ST77XX_CYAN);
	lcd1.run->draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);
	lcd1.run->stop(&lcd1.par);

	tim1_blink_setup();
	irq()->timer->tim1->update = tim_u_callback;
	irq()->timer->tim1->cc1 = tim_cc1_callback;
	uint8_t time[10];

	dev()->enable_peripheral(CORDIC);
	cordic_arg angle;

	while(1)
	{
		rtc()->run->tr2vec(time);

		lcd1.run->start(&lcd1.par);
		lcd1.run->drawstring16x24_size(&lcd1.par,"Hello",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.run->stop(&lcd1.par);
		_delay_ms(500);
		lcd1.run->start(&lcd1.par);
		lcd1.run->drawstring16x24_size(&lcd1.par,"Good Bye",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.run->drawstring_size( &lcd1.par, &Font16, func()->ui32toa(dev()->get->sysclk()), 10, 100, ST77XX_MAGENTA, BG_colour, 10 );
		//lcd1.run->drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_source()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		//lcd1.run->drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_vco_out()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		//lcd1.run->stop(&lcd1.par);
		_delay_ms(500);

		//angle = (cordic_arg){ exe()->deg_to_angle(60.0f), 0, 0, 0 };
		angle.arg_1 = exe()->deg_to_angle(60.0f);
		cordic()->q31(CORDIC_COS, &angle);

		float result = exe()->q31_to_float(angle.out_1);

		lcd1.run->start(&lcd1.par);
		//func()->format_string(str,32,"%u", 60);
		//ptr = function_ui16toa(60);
		//ptr = func()->ui16toa(60);
		//ptr = func()->ui16toa(rtc()->get->second());
		ptr = func()->ftoa(result,2);
		lcd1.run->drawstring16x24_size(&lcd1.par,ptr,10,200,ST77XX_RED,BG_colour,10);
		//lcd1.drawstring16x24(&lcd1.par,"hello",10,200,ST77XX_RED,ST77XX_GREEN);
		lcd1.run->stop(&lcd1.par);

		lcd1.run->start(&lcd1.par);
		func()->format_string(str,32,"%d%d:%d%d:%d%d",time[0], time[1], time[2], time[3], time[4], time[5]);
		lcd1.run->drawstring_size(&lcd1.par,&Font20,str,15,70,ST77XX_RED,BG_colour,8);
		lcd1.run->stop(&lcd1.par);

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
					gpio()->toggle_hpin(GPIOF, 1 << 2);
					Serial1->run->send((uint8_t *) "ACK: Pin Toggled\r\n", 18);
				}
			}
		}
	}
}

/*** EOF ***/

