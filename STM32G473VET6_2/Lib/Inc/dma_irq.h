/******************************************************************************
	dma_irq.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#ifndef DMA_IRQ_H
	#define DMA_IRQ_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/******************************************************************************
 * DMA1
 ******************************************************************************/

/* Channel 1 */
void dma1_ch1_gif_callback(void) __attribute__((weak));
void dma1_ch1_tc_callback(void)  __attribute__((weak));
void dma1_ch1_ht_callback(void)  __attribute__((weak));
void dma1_ch1_te_callback(void)  __attribute__((weak));

/* Channel 2 */
void dma1_ch2_gif_callback(void) __attribute__((weak));
void dma1_ch2_tc_callback(void)  __attribute__((weak));
void dma1_ch2_ht_callback(void)  __attribute__((weak));
void dma1_ch2_te_callback(void)  __attribute__((weak));

/* Channel 3 */
void dma1_ch3_gif_callback(void) __attribute__((weak));
void dma1_ch3_tc_callback(void)  __attribute__((weak));
void dma1_ch3_ht_callback(void)  __attribute__((weak));
void dma1_ch3_te_callback(void)  __attribute__((weak));

/* Channel 4 */
void dma1_ch4_gif_callback(void) __attribute__((weak));
void dma1_ch4_tc_callback(void)  __attribute__((weak));
void dma1_ch4_ht_callback(void)  __attribute__((weak));
void dma1_ch4_te_callback(void)  __attribute__((weak));

/* Channel 5 */
void dma1_ch5_gif_callback(void) __attribute__((weak));
void dma1_ch5_tc_callback(void)  __attribute__((weak));
void dma1_ch5_ht_callback(void)  __attribute__((weak));
void dma1_ch5_te_callback(void)  __attribute__((weak));

/* Channel 6 */
void dma1_ch6_gif_callback(void) __attribute__((weak));
void dma1_ch6_tc_callback(void)  __attribute__((weak));
void dma1_ch6_ht_callback(void)  __attribute__((weak));
void dma1_ch6_te_callback(void)  __attribute__((weak));

/* Channel 7 */
void dma1_ch7_gif_callback(void) __attribute__((weak));
void dma1_ch7_tc_callback(void)  __attribute__((weak));
void dma1_ch7_ht_callback(void)  __attribute__((weak));
void dma1_ch7_te_callback(void)  __attribute__((weak));

/******************************************************************************
 * DMA2
 ******************************************************************************/

/* Channel 1 */
void dma2_ch1_gif_callback(void) __attribute__((weak));
void dma2_ch1_tc_callback(void)  __attribute__((weak));
void dma2_ch1_ht_callback(void)  __attribute__((weak));
void dma2_ch1_te_callback(void)  __attribute__((weak));

/* Channel 2 */
void dma2_ch2_gif_callback(void) __attribute__((weak));
void dma2_ch2_tc_callback(void)  __attribute__((weak));
void dma2_ch2_ht_callback(void)  __attribute__((weak));
void dma2_ch2_te_callback(void)  __attribute__((weak));

/* Channel 3 */
void dma2_ch3_gif_callback(void) __attribute__((weak));
void dma2_ch3_tc_callback(void)  __attribute__((weak));
void dma2_ch3_ht_callback(void)  __attribute__((weak));
void dma2_ch3_te_callback(void)  __attribute__((weak));

/* Channel 4 */
void dma2_ch4_gif_callback(void) __attribute__((weak));
void dma2_ch4_tc_callback(void)  __attribute__((weak));
void dma2_ch4_ht_callback(void)  __attribute__((weak));
void dma2_ch4_te_callback(void)  __attribute__((weak));

/* Channel 5 */
void dma2_ch5_gif_callback(void) __attribute__((weak));
void dma2_ch5_tc_callback(void)  __attribute__((weak));
void dma2_ch5_ht_callback(void)  __attribute__((weak));
void dma2_ch5_te_callback(void)  __attribute__((weak));

/* Channel 6 */
void dma2_ch6_gif_callback(void) __attribute__((weak));
void dma2_ch6_tc_callback(void)  __attribute__((weak));
void dma2_ch6_ht_callback(void)  __attribute__((weak));
void dma2_ch6_te_callback(void)  __attribute__((weak));

/* Channel 7 */
void dma2_ch7_gif_callback(void) __attribute__((weak));
void dma2_ch7_tc_callback(void)  __attribute__((weak));
void dma2_ch7_ht_callback(void)  __attribute__((weak));
void dma2_ch7_te_callback(void)  __attribute__((weak));

#endif

/*** EOF ***/

