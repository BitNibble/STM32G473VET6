/******************************************************************************
	i2c_irq.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#ifndef I2C_IRQ_H
	#define I2C_IRQ_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
/******************************************************************************
 * I2C1
 ******************************************************************************/
/* Error interrupts */
void i2c1_berr_callback(void)    __attribute__((weak));
void i2c1_arlo_callback(void)    __attribute__((weak));
void i2c1_ovr_callback(void)     __attribute__((weak));
void i2c1_pecerr_callback(void)  __attribute__((weak));
void i2c1_timeout_callback(void) __attribute__((weak));
void i2c1_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c1_rxne_callback(void)      __attribute__((weak));
void i2c1_txis_callback(void)      __attribute__((weak));
void i2c1_addr_callback(void)    __attribute__((weak));
void i2c1_nack_callback(void)    __attribute__((weak));
void i2c1_stop_callback(void)    __attribute__((weak));
void i2c1_tc_callback(void)      __attribute__((weak));
void i2c1_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C2
 ******************************************************************************/
/* Error interrupts */
void i2c2_berr_callback(void)    __attribute__((weak));
void i2c2_arlo_callback(void)    __attribute__((weak));
void i2c2_ovr_callback(void)     __attribute__((weak));
void i2c2_pecerr_callback(void)  __attribute__((weak));
void i2c2_timeout_callback(void) __attribute__((weak));
void i2c2_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c2_rxne_callback(void)      __attribute__((weak));
void i2c2_txis_callback(void)      __attribute__((weak));
void i2c2_addr_callback(void)    __attribute__((weak));
void i2c2_nack_callback(void)    __attribute__((weak));
void i2c2_stop_callback(void)    __attribute__((weak));
void i2c2_tc_callback(void)      __attribute__((weak));
void i2c2_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C3
 ******************************************************************************/
/* Error interrupts */
void i2c3_berr_callback(void)    __attribute__((weak));
void i2c3_arlo_callback(void)    __attribute__((weak));
void i2c3_ovr_callback(void)     __attribute__((weak));
void i2c3_pecerr_callback(void)  __attribute__((weak));
void i2c3_timeout_callback(void) __attribute__((weak));
void i2c3_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c3_rxne_callback(void)      __attribute__((weak));
void i2c3_txis_callback(void)      __attribute__((weak));
void i2c3_addr_callback(void)    __attribute__((weak));
void i2c3_nack_callback(void)    __attribute__((weak));
void i2c3_stop_callback(void)    __attribute__((weak));
void i2c3_tc_callback(void)      __attribute__((weak));
void i2c3_tcr_callback(void)     __attribute__((weak));

/******************************************************************************
 * I2C4
 ******************************************************************************/
/* Error interrupts */
void i2c4_berr_callback(void)    __attribute__((weak));
void i2c4_arlo_callback(void)    __attribute__((weak));
void i2c4_ovr_callback(void)     __attribute__((weak));
void i2c4_pecerr_callback(void)  __attribute__((weak));
void i2c4_timeout_callback(void) __attribute__((weak));
void i2c4_alert_callback(void)   __attribute__((weak));

/* Event interrupts */
void i2c4_rxne_callback(void)      __attribute__((weak));
void i2c4_txis_callback(void)      __attribute__((weak));
void i2c4_addr_callback(void)    __attribute__((weak));
void i2c4_nack_callback(void)    __attribute__((weak));
void i2c4_stop_callback(void)    __attribute__((weak));
void i2c4_tc_callback(void)      __attribute__((weak));
void i2c4_tcr_callback(void)     __attribute__((weak));

#endif

/*** EOF ***/

