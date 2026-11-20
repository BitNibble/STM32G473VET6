/**************************************************
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
**************************************************/
#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  //#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
	for(;;);
}
