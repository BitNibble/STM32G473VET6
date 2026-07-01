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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	rcc()->inic();
	fpu_enable();
	rtc()->inic();
    /* Loop forever */
	for(;;);
}
