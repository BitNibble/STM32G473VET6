/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License

	Board BUTTON
Button - PC13
	Board LED
BLUE LED - PF2
	ST8879V
SCL - PC10
SDA - PC12
RST - PC9
DC - PC8
CS - PC7
 I2C1
SCL - GPIOB8
SDA - GPIOB9
************************************************************************/
#include "stm32gxxx_rcc.h"
#include "arm_systick.h"
#include "st7789.h"
#include "function.h"
#include "explode.h"
#include "stm32gxxx_i2c1.h"
#include <string.h>

#define BTN_ALL_PINS_MASK    (0x3FU << 8)
#define BG_colour 0x0000

static EXPLODE_Handler btn_engine;
void rtc_ui_init(void);

int main(void)
{
	rcc()->run->inic();
	dev()->enable->fpu();

	uint32_t count = 0;

	i2c1()->run->init();

	rtc_ui_init();

	dev()->enable->gpiof();
	gpio()->hmoder( GPIOF, MODE_OUTPUT, 1 << 2 );

	ST7789 lcd1 = st7789_enable(SPI3, 7, 8, 9, NULL);
	(void) lcd1;


	lcd1.run->start(&lcd1.par);
	lcd1.run->draw_circle(&lcd1.par,220,300,15,ST77XX_CYAN);
	lcd1.run->draw_star5(&lcd1.par,220,300,15,5,ST77XX_GOLD);
	lcd1.run->stop(&lcd1.par);

	while(1)
	{
		if(btn_engine.run->update(&btn_engine.par, GPIOD->IDR & BTN_ALL_PINS_MASK)) {

			lcd1.run->start(&lcd1.par);
			lcd1.run->drawstring8x12_size(&lcd1.par,func()->ui32toa(dev()->get->pclk1()),10,10,ST77XX_BLUE,BG_colour,10);
			lcd1.run->drawstring8x12_size(&lcd1.par,func()->ui32toa(count++),10,30,ST77XX_BLUE,BG_colour,10);
			lcd1.run->drawstring8x12_size(&lcd1.par,func()->ui32toa(i2c1()->run->test()),10,50,ST77XX_BLUE,BG_colour,10);


			lcd1.run->stop(&lcd1.par);

		}
	}
}

void rtc_ui_init(void)
{
    // Enable GPIO Port D Clock via your helper
	dev()->enable->gpiod();
    // Batch set PD8-PD13 to Input Mode (0)
	gpio()->hmoder(GPIOD, 0, BTN_ALL_PINS_MASK);
    // Batch set PD8-PD13 to internal Pull-Up (1)
    gpio()->hpupd(GPIOD, 1, BTN_ALL_PINS_MASK);
    // Initialize the edge detector tracking instance
    btn_engine = EXPLODE_enable();
}

/*** EOF ***/

