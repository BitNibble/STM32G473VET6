/************************************************************************
	STM32GXXX_I2C1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4
Date:     02/07/2026
************************************************************************/
#ifndef STM32GXXX_I2C1_H
#define STM32GXXX_I2C1_H

/*** LIBRARY ***/
#include "stm32g473vet6.h"

#define PCF8563   0x51

/* Public I2C Configuration Types */
typedef enum {
    I2C_DIR_WRITE = 0U,
    I2C_DIR_READ  = 1U
} i2c_direction_t;

typedef enum {
    I2C_ADDR_7BIT  = 7U,
    I2C_ADDR_10BIT = 10U
} i2c_addr_mode_t;

typedef enum {
    I2C_SPEED_STANDARD   = 100000UL,  // 100 kHz
    I2C_SPEED_FAST       = 400000UL,  // 400 kHz
    I2C_SPEED_FAST_PLUS  = 1000000UL  // 1 MHz
} i2c_bus_speed_t;

/*** i2c1 PARAMETER ***/
typedef struct {
	GPIO_TypeDef*    gpio;
	uint8_t          af;
	uint8_t          pin_scl;       // Renamed var for visual clarity
	uint8_t          pin_sda;       // Renamed var for visual clarity
	i2c_bus_speed_t  bus_speed;     // Self-documenting
	i2c_addr_mode_t  address_mode;  // Self-documenting
} i2c1_par;

/*** i2c1 GET ***/
typedef const struct {
	uint8_t  (*scl_state)(void);
	uint8_t  (*sda_state)(void);
	uint32_t (*status)(void);
	uint8_t  (*pecr)(void);
	uint8_t  (*rxdata)(void);
} i2c1_get;

/*** i2c1 SET ***/
typedef const struct {
	void (*digital_filter)(uint8_t filter);
	void (*slave_address)(uint16_t device_ID);
	void (*direction)(i2c_direction_t r_w);
	void (*addressing_mode)(i2c_addr_mode_t mode);
	void (*nbytes)(uint8_t nbytes);
	void (*own_address)(uint8_t address);

	void (*txdata)(uint8_t data);
	void (*reload_enable)(void);
	void (*reload_disable)(void);
	void (*autoend_enable)(void);
	void (*autoend_disable)(void);
	void (*pecbyte_enable)(void);
	void (*pecbyte_disable)(void);
} i2c1_set;

/*** i2c1 V-TABLE ***/
typedef const struct {
	void (*init)(void);
	void (*clock_enable)(void);
	void (*clock_disable)(void);
	void (*enable)(void);
	void (*disable)(void);
	void (*analog_filter_enable)(void);
	void (*analog_filter_disable)(void);
	void (*software_reset)(void);
	void (*clock_stretch_enable)(void);
	void (*clock_stretch_disable)(void);
	void (*general_call_enable)(void);
	void (*general_call_disable)(void);
	void (*pec_enable)(void);
	void (*pec_disable)(void);
	void (*mode10_read_enable)(void);
	void (*mode10_read_disable)(void);
	void (*reload_enable)(void);
	void (*reload_disable)(void);
	void (*autoend_enable)(void);
	void (*autoend_disable)(void);
	void (*pecbyte_enable)(void);
	void (*pecbyte_disable)(void);
	void (*start)(void);
	void (*stop)(void);

	void (*reset)(void);
	void (*own_address_enable)(void);
	void (*own_address_disable)(void);
} i2c1_run;

/*** i2c1 CALLBACK ***/
typedef struct {
	void (*ev_handler_callback)(void); // Maps to Event IRQ
	void (*er_handler_callback)(void); // Maps to Error IRQ
} i2c1_irq;

/*** i2c1 HANDLER ***/
typedef const struct {
	i2c1_par* par;
	i2c1_get* get;
	i2c1_set* set;
	i2c1_irq* irq;
	i2c1_run* run;
} i2c1_handler;

/*** i2c1 ACCESSOR FUNCTION ***/
i2c1_handler* i2c1(void);

#endif /* STM32GXXX_I2C1_H */
/*** EOF ***/
