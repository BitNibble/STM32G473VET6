/******************************************************************************
	usart_irq.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#ifndef USART_IRQ_H
	#define USART_IRQ_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/******************************************************************************
 * USART1
 ******************************************************************************/
void usart1_pe_callback(void)    __attribute__((weak));
void usart1_fe_callback(void)    __attribute__((weak));
void usart1_ne_callback(void)    __attribute__((weak));
void usart1_ore_callback(void)   __attribute__((weak));

void usart1_idle_callback(void)  __attribute__((weak));
void usart1_rxne_callback(void)  __attribute__((weak));
void usart1_txe_callback(void)   __attribute__((weak));
void usart1_tc_callback(void)    __attribute__((weak));

void usart1_cts_callback(void)   __attribute__((weak));
void usart1_rtof_callback(void)  __attribute__((weak));
void usart1_eob_callback(void)   __attribute__((weak));
void usart1_cmf_callback(void)   __attribute__((weak));
void usart1_wuf_callback(void)   __attribute__((weak));

void usart1_txfe_callback(void)  __attribute__((weak));
void usart1_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * USART2
 ******************************************************************************/
void usart2_pe_callback(void)    __attribute__((weak));
void usart2_fe_callback(void)    __attribute__((weak));
void usart2_ne_callback(void)    __attribute__((weak));
void usart2_ore_callback(void)   __attribute__((weak));

void usart2_idle_callback(void)  __attribute__((weak));
void usart2_rxne_callback(void)  __attribute__((weak));
void usart2_txe_callback(void)   __attribute__((weak));
void usart2_tc_callback(void)    __attribute__((weak));

void usart2_cts_callback(void)   __attribute__((weak));
void usart2_rtof_callback(void)  __attribute__((weak));
void usart2_eob_callback(void)   __attribute__((weak));
void usart2_cmf_callback(void)   __attribute__((weak));
void usart2_wuf_callback(void)   __attribute__((weak));

void usart2_txfe_callback(void)  __attribute__((weak));
void usart2_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * USART3
 ******************************************************************************/
void usart3_pe_callback(void)    __attribute__((weak));
void usart3_fe_callback(void)    __attribute__((weak));
void usart3_ne_callback(void)    __attribute__((weak));
void usart3_ore_callback(void)   __attribute__((weak));

void usart3_idle_callback(void)  __attribute__((weak));
void usart3_rxne_callback(void)  __attribute__((weak));
void usart3_txe_callback(void)   __attribute__((weak));
void usart3_tc_callback(void)    __attribute__((weak));

void usart3_cts_callback(void)   __attribute__((weak));
void usart3_rtof_callback(void)  __attribute__((weak));
void usart3_eob_callback(void)   __attribute__((weak));
void usart3_cmf_callback(void)   __attribute__((weak));
void usart3_wuf_callback(void)   __attribute__((weak));

void usart3_txfe_callback(void)  __attribute__((weak));
void usart3_rxff_callback(void)  __attribute__((weak));

/******************************************************************************
 * UART4
 ******************************************************************************/
void uart4_pe_callback(void)     __attribute__((weak));
void uart4_fe_callback(void)     __attribute__((weak));
void uart4_ne_callback(void)     __attribute__((weak));
void uart4_ore_callback(void)    __attribute__((weak));

void uart4_idle_callback(void)   __attribute__((weak));
void uart4_rxne_callback(void)   __attribute__((weak));
void uart4_txe_callback(void)    __attribute__((weak));
void uart4_tc_callback(void)     __attribute__((weak));

void uart4_cts_callback(void)    __attribute__((weak));
void uart4_rtof_callback(void)   __attribute__((weak));
void uart4_eob_callback(void)    __attribute__((weak));
void uart4_cmf_callback(void)    __attribute__((weak));
void uart4_wuf_callback(void)    __attribute__((weak));

void uart4_txfe_callback(void)   __attribute__((weak));
void uart4_rxff_callback(void)   __attribute__((weak));

/******************************************************************************
 * UART5
 ******************************************************************************/
void uart5_pe_callback(void)     __attribute__((weak));
void uart5_fe_callback(void)     __attribute__((weak));
void uart5_ne_callback(void)     __attribute__((weak));
void uart5_ore_callback(void)    __attribute__((weak));

void uart5_idle_callback(void)   __attribute__((weak));
void uart5_rxne_callback(void)   __attribute__((weak));
void uart5_txe_callback(void)    __attribute__((weak));
void uart5_tc_callback(void)     __attribute__((weak));

void uart5_cts_callback(void)    __attribute__((weak));
void uart5_rtof_callback(void)   __attribute__((weak));
void uart5_eob_callback(void)    __attribute__((weak));
void uart5_cmf_callback(void)    __attribute__((weak));
void uart5_wuf_callback(void)    __attribute__((weak));

void uart5_txfe_callback(void)   __attribute__((weak));
void uart5_rxff_callback(void)   __attribute__((weak));

/******************************************************************************
 * LPUART1
 ******************************************************************************/
void lpuart1_pe_callback(void)   __attribute__((weak));
void lpuart1_fe_callback(void)   __attribute__((weak));
void lpuart1_ne_callback(void)   __attribute__((weak));
void lpuart1_ore_callback(void)  __attribute__((weak));

void lpuart1_idle_callback(void) __attribute__((weak));
void lpuart1_rxne_callback(void) __attribute__((weak));
void lpuart1_txe_callback(void)  __attribute__((weak));
void lpuart1_tc_callback(void)   __attribute__((weak));

void lpuart1_cts_callback(void)  __attribute__((weak));
void lpuart1_rtof_callback(void) __attribute__((weak));
void lpuart1_eob_callback(void)  __attribute__((weak));
void lpuart1_cmf_callback(void)  __attribute__((weak));
void lpuart1_wuf_callback(void)  __attribute__((weak));

void lpuart1_txfe_callback(void) __attribute__((weak));
void lpuart1_rxff_callback(void) __attribute__((weak));

#endif

/*** EOF ***/

