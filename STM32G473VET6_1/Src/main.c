/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
************************************************************************/
#include "stm32gxxxrcc.h"
#include "armsystick.h"
#include "timer_irq.h"
#include "st7789.h"
#include "armfunction.h"
#include "stm32gxxxrtc.h"
#include "stm32gxxxusart1.h"
#include<string.h>

#define BG_colour 0x0000

// Retrieve global reference to layout instance
static const USARTG4_Handle* Serial1;
char* token[4];

char usart_1[USART1_RX_SIZE];
uint8_t str[32];
char* ptr = NULL;

void tim1_blink_setup(void)
{
    /*-----------------------------
     * 1. CLOCK ENABLE (TIM1)
     *----------------------------*/
    dev()->sys->rcc->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /*-----------------------------
     * 2. TIMER CONFIG (1 Hz example)
     *    assuming 170 MHz TIM clock
     *----------------------------*/
    dev()->timer->tim1->PSC = 119;
    dev()->timer->tim1->ARR = 1999999;
    dev()->timer->tim1->CNT = 0;

    /* Force update so registers load */
    dev()->timer->tim1->EGR = TIM_EGR_UG;

    /*-----------------------------
     * 3. INTERRUPT ENABLE (TIM1 update)
     *----------------------------*/
    dev()->timer->tim1->DIER |= TIM_DIER_UIE;

    /*-----------------------------
     * 4. NVIC ENABLE (TIM1 UP IRQ)
     *----------------------------*/
    NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

    /*-----------------------------
     * 5. START TIMER
     *----------------------------*/
    dev()->timer->tim1->CR1 |= TIM_CR1_CEN;
}
void tim1_u_callback(void)
{
    dev()->gpio->f->ODR ^= (1 << 2);
}

int main(void)
{
	rcc()->inic();
	fpu_enable();
	rtc()->inic();

	//char str[32];
	//char vecD[8]; // for calendar date
	//char vecT[8]; // for calendar time

	GPIO_clock( dev()->gpio->f, 1 );
	GPIO_hmoder( dev()->gpio->f, 1 << 2, 1 );

	//clear_pin(dev()->gpio->f, 1 << 2);

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	Serial1 = usart1();

	Serial1->run->init();

	// 2. CRITICAL: Turn on the receiver engine and enable the DMA stream!
	Serial1->run->start_rx();

	Serial1->run->send((uint8_t *) "Received:", 10);

	lcd1.start(&lcd1.par);
	lcd1.draw_circle(&lcd1.par,200,80,15,ST77XX_CYAN);
	lcd1.draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);

	lcd1.stop(&lcd1.par);

	//tim1_blink_setup();

	while(1)
	{
		lcd1.start(&lcd1.par);
		lcd1.drawstring16x24_size(&lcd1.par,"LeD ON",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.stop(&lcd1.par);
		_delay_ms(500);
		//toggle_hpin( dev()->gpio->f, 1 << 2 );
		lcd1.start(&lcd1.par);
		lcd1.drawstring16x24_size(&lcd1.par,"LED OFF",10,20,ST77XX_MAGENTA,BG_colour, 8);
		lcd1.drawstring24x48_size( &lcd1.par, func()->ui32toa(get_sysclk()), 10, 100, ST77XX_MAGENTA, BG_colour, 10 );
		//lcd1.drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_source()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		//lcd1.drawstring24x48_size( &lcd1.par, func()->ui32toa(get_pll_vco_out()), 10, 100, ST77XX_MAGENTA, ST77XX_GREEN, 10 );
		lcd1.stop(&lcd1.par);
		_delay_ms(500);
		//toggle_hpin( dev()->gpio->f, 1 << 2 );

		lcd1.start(&lcd1.par);
		//func()->format_string(str,32,"%u", 60);
		//ptr = function_ui16toa(60);
		//ptr = func()->ui16toa(60);
		ptr = func()->ui16toa(rtc()->get_second());
		lcd1.drawstring16x24_size(&lcd1.par,ptr,10,200,ST77XX_RED,BG_colour,2);
		//lcd1.drawstring16x24(&lcd1.par,"hello",10,200,ST77XX_RED,ST77XX_GREEN);
		lcd1.stop(&lcd1.par);

		/***
		rtc()->dr2vec(vecD);
		rtc()->tr2vec(vecT);

		lcd1.start(&lcd1.par);
		func()->format_string(str,32,"%d%d-%d%d-20%d%d",vecD[5], vecD[6], vecD[3], vecD[4], vecD[0], vecD[1]);
		lcd1.drawstring16x24(&lcd1.par,str,10,150,ST77XX_BLACK,ST77XX_GREEN);

		lcd1.drawstring12x16_size(&lcd1.par,(char*)WeekDay_String(vecD[2]),10,200,ST77XX_BLACK,ST77XX_GREEN,7);

		func()->format_string(str,32,"%d%d:%d%d:%d%d",vecT[0], vecT[1], vecT[2], vecT[3], vecT[4], vecT[5]);
		lcd1.drawstring24x48_size(&lcd1.par,str,15,70,ST77XX_RED,ST77XX_GREEN,8);
		lcd1.stop(&lcd1.par);
		***/

		if (Serial1->run->read_str_size(usart_1, sizeof(usart_1)) > 0) {
			// Clear prior pointers to avoid parsing contamination
			memset(token, 0, sizeof(token));

			// Extract command fragments based on carriage return sequences
			func()->parse_string(usart_1, 4, token, "\r\n");

			// Confirm token[0] was successfully parsed before utilizing it
			if (token[0] != NULL) {
				lcd1.start(&lcd1.par);
				lcd1.drawstring16x24_size(&lcd1.par, token[0], 10, 160, ST77XX_RED, BG_colour, 12);
				lcd1.stop(&lcd1.par);

				// Safe command structure execution context
				if (strcmp(token[0], "s00") == 0) {
					toggle_hpin(dev()->gpio->f, 1 << 2);
					Serial1->run->send((uint8_t *) "ACK: Pin Toggled\r\n", 18);
				}
			}
		}

	}
}

