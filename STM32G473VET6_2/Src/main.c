/************************************************************************
	MAIN
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
************************************************************************/
#include "stm32gxxxrcc.h"

int main(void)
{
	rcc()->inic();
    /* Loop forever */
	for(;;);
}
