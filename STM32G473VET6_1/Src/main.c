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

//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif

// Retrieve global reference to layout instance
static USARTG4_Handle* Serial1;

uint8_t str[32];
char* ptr;

void tim1_blink_setup(void)
{
    /*-----------------------------
     * 1. CLOCK ENABLE (TIM1)
     *----------------------------*/
    dev()->system->rcc->APB2ENR |= RCC_APB2ENR_TIM1EN;

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
	GPIO_moder( dev()->gpio->f, 2, 1 );

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;

	Serial1 = usart1();

	Serial1->run.init(&Serial1->par);

	// 2. CRITICAL: Turn on the receiver engine and enable the DMA stream!
	Serial1->run.start_rx(&Serial1->par);

	Serial1->run.send(&Serial1->par, (uint8_t *) "Received: Xgdgdgsdgsdgsdgsdfgsdgdgsdgfdsg", 30);

	lcd1.start(&lcd1.par);
	lcd1.draw_circle(&lcd1.par,200,80,15,ST77XX_BLACK);
	lcd1.draw_star5(&lcd1.par,200,80,15,5,ST77XX_GOLD);

	lcd1.stop(&lcd1.par);

	//tim1_blink_setup();

	while(1)
	{
		set_pin( dev()->gpio->f, 2 );
		lcd1.start(&lcd1.par);
		lcd1.drawstring16x24_size(&lcd1.par,"LeD ON",10,20,ST77XX_MAGENTA,ST77XX_GREEN, 8);
		lcd1.stop(&lcd1.par);

		_delay_ms(1000);
		clear_pin( dev()->gpio->f, 2 );
		lcd1.start(&lcd1.par);
		lcd1.drawstring16x24_size(&lcd1.par,"LED OFF",10,20,ST77XX_MAGENTA,ST77XX_GREEN, 8);
		lcd1.drawstring24x48_size( &lcd1.par, "HHbra", 10, 80, ST77XX_MAGENTA, ST77XX_GREEN, 5 );
		lcd1.stop(&lcd1.par);
		_delay_ms(1000);

		lcd1.start(&lcd1.par);
		//func()->format_string(str,32,"%u", 60);
		//ptr = function_ui16toa(60);
		//ptr = func()->ui16toa(60);
		ptr = func()->ui16toa(rtc()->get_second());
		lcd1.drawstring16x24_size(&lcd1.par,ptr,10,200,ST77XX_RED,ST77XX_GREEN,2);
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

		// 1. Check if the circular DMA buffer has received new data
		//if (Serial1->run.available(&Serial1->par) > 6) {

			// 2. Fetch the byte out of the ring buffer
			//Serial1->run.read(&Serial1->par, str);

			//lcd1.start(&lcd1.par);
			//lcd1.drawstring16x24_size(&lcd1.par,(const char*)str,10,150,ST77XX_RED,ST77XX_GREEN,8);
			//lcd1.drawstring16x24_size(&lcd1.par,(const char*)Serial1->par.buff_rx + Serial1->par.rx_read_index,10,150,ST77XX_RED,ST77XX_GREEN,12);
			//Serial1->par.rx_read_index = Serial1->par.rx_write_index;
			//lcd1.stop(&lcd1.par);

			// 3. Wait for the TX hardware to be ready
			//while(!Serial1->run.tx_ready(&Serial1->par));

			// 4. Echo the byte back to your phone/PC screen
			//Serial1->run.send(&Serial1->par, str, 1);
		//}

		lcd1.start(&lcd1.par);
		//  lcd1.drawstring16x24_size(&lcd1.par,(const char*)str,10,150,ST77XX_RED,ST77XX_GREEN,8);
		lcd1.drawstring16x24_size(&lcd1.par,(const char*)Serial1->par.buff_rx + Serial1->par.rx_read_index,10,150,ST77XX_RED,ST77XX_GREEN,12);
		Serial1->par.rx_read_index = Serial1->par.rx_write_index;
		lcd1.stop(&lcd1.par);

	}
}

