/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
	ST8879V
SCL - PC10
SDA - PC12
RST - PC9
DC - PC8
CS - PC7
************************************************************************/
#include "stm32gxxx_rcc.h"
#include "arm_systick.h"
#include "st7789.h"
#include "function.h"
#include "explode.h"
#include <string.h>

#define BG_colour 0x0000

int main(void)
{
	rcc()->run->inic();
	dev()->run->fpu_enable();

	dev()->run->gpio_clock( dev()->gpio->f, 1 );
	dev()->run->gpio_hmoder( dev()->gpio->f, 1 << 2, MODE_OUTPUT );

	ST7789 lcd1 = st7789_enable(dev()->comm->spi3, 7, 8, 9, NULL);
	(void) lcd1;


	lcd1.run->start(&lcd1.par);
	lcd1.run->draw_circle(&lcd1.par,220,300,15,ST77XX_CYAN);
	lcd1.run->draw_star5(&lcd1.par,220,300,15,5,ST77XX_GOLD);
	lcd1.run->stop(&lcd1.par);

	while(1)
	{

	}
}

