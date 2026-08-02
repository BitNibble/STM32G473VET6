/******************************************************************************
	spi_irq.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#ifndef SPI_IRQ_H
	#define SPI_IRQ_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
/******************************************************************************
 * SPI1
 ******************************************************************************/
void spi1_rxne_callback(void)    __attribute__((weak));
void spi1_txe_callback(void)     __attribute__((weak));

void spi1_ovr_callback(void)     __attribute__((weak));
void spi1_modf_callback(void)    __attribute__((weak));
void spi1_crcerr_callback(void)  __attribute__((weak));
void spi1_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI2
 ******************************************************************************/
void spi2_rxne_callback(void)    __attribute__((weak));
void spi2_txe_callback(void)     __attribute__((weak));

void spi2_ovr_callback(void)     __attribute__((weak));
void spi2_modf_callback(void)    __attribute__((weak));
void spi2_crcerr_callback(void)  __attribute__((weak));
void spi2_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI3
 ******************************************************************************/
void spi3_rxne_callback(void)    __attribute__((weak));
void spi3_txe_callback(void)     __attribute__((weak));

void spi3_ovr_callback(void)     __attribute__((weak));
void spi3_modf_callback(void)    __attribute__((weak));
void spi3_crcerr_callback(void)  __attribute__((weak));
void spi3_fre_callback(void)     __attribute__((weak));

/******************************************************************************
 * SPI4
 ******************************************************************************/
void spi4_rxne_callback(void)    __attribute__((weak));
void spi4_txe_callback(void)     __attribute__((weak));

void spi4_ovr_callback(void)     __attribute__((weak));
void spi4_modf_callback(void)    __attribute__((weak));
void spi4_crcerr_callback(void)  __attribute__((weak));
void spi4_fre_callback(void)     __attribute__((weak));

#endif

/*** EOF ***/

