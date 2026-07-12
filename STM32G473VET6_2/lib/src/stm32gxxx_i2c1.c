/************************************************************************
	STM32GXXX_I2C1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4
Date:     02/07/2026
************************************************************************/
#include "stm32gxxx_i2c1.h"

// Define standard tracking status identifiers matching I2C_ISR bit offsets
#define I2C_FLAG_TXIS  I2C_ISR_TXIS
#define I2C_FLAG_RXNE  I2C_ISR_RXNE
#define I2C_FLAG_TC    I2C_ISR_TC
#define I2C_FLAG_NACK  I2C_ISR_NACKF

static volatile uint32_t i2c1_cr2;

/*** i2c1 PARAMETER ***/
static i2c1_par par_setup = { // DEFAULT
	.pin_scl_gpio = GPIOB,
	.pin_sda_gpio = GPIOB,
	.pin_scl_af = 6,
	.pin_sda_af = 6,
	.pin_scl = 8,
	.pin_sda = 9,
	.bus_speed = I2C_SPEED_STANDARD,
	.address_mode = I2C_ADDR_7BIT
};

/*** Procedure & Function Definition ***/
static void i2c1_clock_enable(void) {
	exe()->set_reg(&dev()->sys->rcc->APB1ENR1,RCC_APB1ENR1_I2C1EN);
}
static void i2c1_clock_disable(void) {
	exe()->clear_reg(&dev()->sys->rcc->APB1ENR1,RCC_APB1ENR1_I2C1EN);
}
//helper to handle configuration safety locks
static inline void _i2c1_modify_cr1_protected(void (*modify_func)(void)) {
    uint32_t is_enabled = exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos);
    if (is_enabled) {
        exe()->clear_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
        while(exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos));
    }
    modify_func();
    if (is_enabled) {
        exe()->set_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
    }
}
// Universal non-blocking status check helper
static uint8_t _i2c1_get_flag(uint32_t flag_mask) {
    // Read the whole register and isolate the single flag bit
    return (dev()->comm->i2c1->ISR & flag_mask) ? 1U : 0U;
}
// Fixed-timeout polling engine to protect your MCU from locking up indefinitely on bus faults
uint8_t _i2c1_wait_flag_timeout(uint32_t flag_mask, uint8_t status_expected, uint32_t timeout_loops) {
    volatile uint32_t timeout = timeout_loops;
    while (_i2c1_get_flag(flag_mask) != status_expected) {
        if (--timeout == 0) {
            return 0; // Operation failed / Timed out
        }
    }
    return 1; // Success
}
// Helper to safely read specific flags from the ISR status register
static uint8_t _i2c1_get_status_flag(uint32_t msk) {
	// Uses your get_field_value tool (Pos is 0 since we want the masked raw bit location)
	return exe()->get_field_value(dev()->comm->i2c1->ISR, msk, 0) ? 1U : 0U;
}
// Fixed loop timeout polling engine to prevent the MCU from hanging on a dead bus
static uint8_t _i2c1_wait_status_flag(uint32_t msk, uint8_t expected_state, uint32_t timeout_loops) {
	volatile uint32_t timeout = timeout_loops;
	while (_i2c1_get_status_flag(msk) != expected_state) {
		if (--timeout == 0) {
			return 0; // Failed / Timed Out
		}
		// If a NACK occurs during transmission, abort early
		if (msk != I2C_ISR_NACKF && _i2c1_get_status_flag(I2C_ISR_NACKF)) {
			exe()->set_reg(&dev()->comm->i2c1->ICR, I2C_ICR_NACKCF); // Clear NACK flag
			return 0;
		}
	}
	return 1; // Success
}

/*******************  Bit definition for I2C_CR1 register  *******************/
uint8_t _i2c1_is_enabled(void) {
	return exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
static uint8_t _i2c1_is_disabled(void) {
	return !exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
static void i2c1_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
static void i2c1_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
static void i2c1_digital_filter(uint8_t filter) {
	uint32_t is_enabled = exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos);

	if (is_enabled) {
		exe()->clear_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
		while(exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos));
	}

	exe()->write_field_value(&dev()->comm->i2c1->CR1,I2C_CR1_DNF,I2C_CR1_DNF_Pos,filter);

	if (is_enabled) {
		exe()->set_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
	}
}
static void i2c1_analog_filter_enable(void) {
	uint32_t is_enabled = exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos);
	if (is_enabled) {
		exe()->clear_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
		while(exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos));
	}

	exe()->clear_reg(&dev()->comm->i2c1->CR1, I2C_CR1_ANFOFF);

	if (is_enabled) {
		exe()->set_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
	}
}
static void i2c1_analog_filter_disable(void) {
	uint32_t is_enabled = exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos);

	if (is_enabled) {
		exe()->clear_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
		while(exe()->get_field_value(dev()->comm->i2c1->CR1, I2C_CR1_PE, I2C_CR1_PE_Pos));
	}

	exe()->set_reg(&dev()->comm->i2c1->CR1, I2C_CR1_ANFOFF);

	if (is_enabled) {
		exe()->set_reg(&dev()->comm->i2c1->CR1, I2C_CR1_PE);
	}
}
static void i2c1_software_reset(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_SWRST);
}
static void i2c1_clock_stretch_enable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_NOSTRETCH);
}
static void i2c1_clock_stretch_disable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_NOSTRETCH);
}
static void i2c1_general_call_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_GCEN);
}
static void i2c1_general_call_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_GCEN);
}
static void i2c1_pec_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PECEN);
}
static void i2c1_pec_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PECEN);
}

/******************  Bit definition for I2C_CR2 register  ********************/
static void i2c1_slave_address(uint16_t device_ID) {
	uint16_t shifted_address = (device_ID << 1);
	exe()->write_field_value(&i2c1_cr2, I2C_CR2_SADD, I2C_CR2_SADD_Pos, shifted_address);
}
static void i2c1_direction(uint8_t r_w) {
	if(r_w)
		exe()->set_reg(&i2c1_cr2, I2C_CR2_RD_WRN);
	else
		exe()->clear_reg(&i2c1_cr2, I2C_CR2_RD_WRN);
}
static void i2c1_addressing_mode(i2c_addr_mode_t mode) {
	if(mode == I2C_ADDR_10BIT)
		exe()->set_reg(&i2c1_cr2, I2C_CR2_ADD10);
	else
		exe()->clear_reg(&i2c1_cr2, I2C_CR2_ADD10);
}
static void i2c1_mode10_read_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_HEAD10R);
}
static void i2c1_mode10_read_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_HEAD10R);
}
static void i2c1_nbytes(uint8_t nbytes) {
	exe()->write_field_value(&i2c1_cr2, I2C_CR2_NBYTES, I2C_CR2_NBYTES_Pos, nbytes);
}
static void i2c1_reload_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_RELOAD);
}
static void i2c1_reload_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_RELOAD);
}
static void i2c1_autoend_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_AUTOEND);
}
static void i2c1_autoend_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_AUTOEND);
}
static void i2c1_pecbyte_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_PECBYTE);
}
static void i2c1_pecbyte_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_PECBYTE);
}
static void i2c1_start(void) {
	uint32_t final_hardware_cmd = i2c1_cr2 | I2C_CR2_START;
	exe()->write_field_encoded(&dev()->comm->i2c1->CR2, 0xFFFFFFFFU, final_hardware_cmd);

	uint32_t persistent_mask = I2C_CR2_NBYTES | I2C_CR2_RD_WRN | I2C_CR2_START;
	i2c1_cr2 = exe()->_imask(i2c1_cr2, persistent_mask);
}
static uint8_t i2c1_get_start(void) {
	return exe()->get_field_value(dev()->comm->i2c1->CR2, I2C_CR2_START, I2C_CR2_START_Pos);
}
static void i2c1_stop(void) {
	// STOP can be asserted directly to hardware safely to terminate/abort sequences
	exe()->set_reg(&dev()->comm->i2c1->CR2, I2C_CR2_STOP);
}

/*******************  Bit definition for I2C_OAR1 register  ******************/
static void i2c1_own_address(uint8_t address) {
	exe()->write_field_value(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1,I2C_OAR1_OA1_Pos,address);
}
static void i2c1_own_address_10bit_mode_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1MODE);
}
static void i2c1_own_address_10bit_mode_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1MODE);
}
static void i2c1_own_address_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
static void i2c1_own_address_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
/*******************  Bit definition for I2C_TIMINGR register *******************/
static void i2c1_low_period(uint8_t ll) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLL,I2C_TIMINGR_SCLL_Pos,ll);
}
static void i2c1_high_period(uint8_t hh) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLH,I2C_TIMINGR_SCLH_Pos,hh);
}
static void i2c1_hold_timing(uint8_t hold) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SDADEL,I2C_TIMINGR_SDADEL_Pos,hold & 0xF);
}
static void i2c1_setup_timing(uint8_t setup) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLDEL,I2C_TIMINGR_SCLDEL_Pos,setup & 0xF);
}
static void i2c1_timing_prescaler(uint8_t prescaler) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_PRESC,I2C_TIMINGR_PRESC_Pos,prescaler & 0xF);
}
static uint8_t i2c1_get_low_period(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLL,I2C_TIMINGR_SCLL_Pos);
}
static uint8_t i2c1_get_high_period(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLH,I2C_TIMINGR_SCLH_Pos);
}
static uint8_t i2c1_get_hold_timing(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SDADEL,I2C_TIMINGR_SDADEL_Pos);
}
static uint8_t i2c1_get_setup_timing(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLDEL,I2C_TIMINGR_SCLDEL_Pos);
}
static uint8_t i2c1_get_timing_prescaler(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_PRESC,I2C_TIMINGR_PRESC_Pos);
}

/******************* Bit definition for I2C_TIMEOUTR register *******************/
static void i2c1_bus_timeout(uint16_t timeout) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMEOUTA,I2C_TIMEOUTR_TIMEOUTA_Pos,timeout & 0x0FFF);
}
static void i2c1_idle_timeout_detect_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIDLE);
}
static void i2c1_idle_timeout_detect_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIDLE);
}
static void i2c1_timeout_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMOUTEN);
}
static void i2c1_timeout_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMOUTEN);
}

/******************  Bit definition for I2C_ISR register  *********************/
static uint32_t i2c1_status(void) { // ACK NACK & ERROR FLAGS
	return dev()->comm->i2c1->ISR;
}

/******************  Bit definition for I2C_PECR register  *********************/
static uint8_t i2c1_get_pecr(void) {
	return exe()->get_field_value(dev()->comm->i2c1->PECR,I2C_PECR_PEC,I2C_PECR_PEC_Pos);
}

/******************  Bit definition for I2C_RXDR register  *********************/
static uint8_t i2c1_get_rxdata(void) {
	return exe()->get_field_value(dev()->comm->i2c1->RXDR,I2C_RXDR_RXDATA,I2C_RXDR_RXDATA_Pos);
}

/******************  Bit definition for I2C_TXDR register  *********************/
static void i2c1_set_txdata(uint8_t data) {
	exe()->write_field_value(&dev()->comm->i2c1->TXDR,I2C_TXDR_TXDATA,I2C_TXDR_TXDATA_Pos, data);
}

/*** Procedure & Function Definition ***/
static void i2c1_reset(void) {
	i2c1_disable();
	while(!_i2c1_is_disabled());
	i2c1_enable();
}

static uint8_t i2c1_is_idle(void) {
	uint32_t isr_value = dev()->comm->i2c1->ISR;

	if ((isr_value & I2C_ISR_BUSY) == 0U) {
		return 1U;
	}

	return 0U;
}

uint8_t wait_for_bus_idle(uint32_t timeout_loops) {
	volatile uint32_t timeout = timeout_loops;

	while (i2c1_is_idle() == 0U) {
		if (--timeout == 0U) {
			i2c1()->run->reset();
			return 0U;
		}
	}
	return 1U;
}

/******************  High-Level API Functions  *********************/
// Universal master buffer writer function
static uint8_t i2c1_write_buffer(uint16_t device_id, uint8_t* p_data, uint8_t length) {
	if (length == 0 || exe()->isPtrNull(p_data)) return 0;
	// 1. Stage the transaction parameters into your global shadow register
	i2c1_slave_address(device_id);
	i2c1_direction(I2C_DIR_WRITE);
	i2c1_nbytes(length);
	// 2. Clear out any leftover hardware status error flags before starting
	exe()->set_reg(&dev()->comm->i2c1->ICR, 0x3F38U);
	// 3. Fire the hardware start sequence!
	i2c1_start();
	// 4. Stream data out sequentially
	for (uint8_t i = 0; i < length; i++) {
		// Wait for TXIS (Transmit Interrupt Status) flag indicating TXDR is empty
		if (!_i2c1_wait_status_flag(I2C_ISR_TXIS, 1, 100000UL)) {
			i2c1_stop(); // Safe abort
			return 0;
		}
		// Load next data byte into the hardware transmitter
		i2c1_set_txdata(p_data[i]);
	}
	// 5. If AUTOEND is disabled, manually wait for Transfer Complete (TC) and stop
	// If AUTOEND is enabled, the hardware handles STOP automatically.
	return 1;
}
// Universal master buffer reader function
static uint8_t i2c1_read_buffer(uint16_t device_id, uint8_t* p_buffer, uint8_t length) {
	if (length == 0 || exe()->isPtrNull(p_buffer)) return 0;
	// 1. Stage parameters
	i2c1_slave_address(device_id);
	i2c1_direction(I2C_DIR_READ); // 1 = Read
	i2c1_nbytes(length);
	exe()->set_reg(&dev()->comm->i2c1->ICR, 0x3F38U);
	// 2. Fire Start
	i2c1_start();
	// 3. Stream data in sequentially
	for (uint8_t i = 0; i < length; i++) {
		// Wait for RXNE (Receive Not Empty) flag indicating data has arrived
		if (!_i2c1_wait_status_flag(I2C_ISR_RXNE, 1, 100000UL)) {
			return 0;
		}
		// Fetch the raw byte out of hardware
		p_buffer[i] = i2c1_get_rxdata();
	}
	return 1;
}

static void init_v1(void) {
	// preamble stuff (sequence layout)
	uint8_t data = 0;
	(void) data;

	/*** SETUP ***/
	dev()->run->gpio_moder( par_setup.pin_scl_gpio, par_setup.pin_scl, MODE_AF );
	dev()->run->gpio_moder( par_setup.pin_sda_gpio, par_setup.pin_sda, MODE_AF );
	dev()->run->gpio_af( par_setup.pin_scl_gpio, par_setup.pin_scl, par_setup.pin_scl_af );
	dev()->run->gpio_af( par_setup.pin_sda_gpio, par_setup.pin_sda, par_setup.pin_sda_af );
	dev()->run->gpio_pupd( par_setup.pin_scl_gpio, par_setup.pin_scl, GPIO_PULLUP );
	dev()->run->gpio_pupd( par_setup.pin_sda_gpio, par_setup.pin_sda, GPIO_PULLUP );

	i2c1_clock_enable();
	i2c1_digital_filter(1);
	i2c1_analog_filter_disable();
	// tSCL = tSYNC1 + tSYNC2 + {[(SCLH+ 1) + (SCLL+ 1)] x (PRESC+ 1) x tI2CCLK}
	i2c1_timing_prescaler(0xB); // 48MHZ - 100KHZ - 0xB
	i2c1_low_period(0x13); // 48MHZ - 100KHZ - 0x13
	i2c1_high_period(0xF); // 48MHZ - 100KHZ - 0xF
	i2c1_hold_timing(0x2); // 48MHZ - 100KHZ - 0x2
	i2c1_setup_timing(0x4); // 48MHZ - 100KHZ - 0x4

	/*** Communication ***/
	i2c1_enable();

	if(!i2c1_get_start()){
		i2c1_addressing_mode(I2C_ADDR_7BIT);
		i2c1_slave_address(PCF8563);
		i2c1_direction(I2C_DIR_READ);
		i2c1_nbytes(TWO);

		if(i2c1_is_idle()){
			i2c1_start(); // busy
			i2c1_set_txdata(0x02); // RXNE
			data = i2c1_get_rxdata(); // RXNE
			i2c1_stop();
		}
	}
}

void init(void) {
	// Local buffer layout to track power-up responses safely
	uint8_t time_test_buffer[2] = {0};

	/*** SETUP ***/
	dev()->run->gpio_moder( par_setup.pin_scl_gpio, par_setup.pin_scl, MODE_AF );
	dev()->run->gpio_moder( par_setup.pin_sda_gpio, par_setup.pin_sda, MODE_AF );
	dev()->run->gpio_af( par_setup.pin_scl_gpio, par_setup.pin_scl, par_setup.pin_scl_af );
	dev()->run->gpio_af( par_setup.pin_sda_gpio, par_setup.pin_sda, par_setup.pin_sda_af );
	dev()->run->gpio_pupd( par_setup.pin_scl_gpio, par_setup.pin_scl, GPIO_PULLUP );
	dev()->run->gpio_pupd( par_setup.pin_sda_gpio, par_setup.pin_sda, GPIO_PULLUP );

	i2c1_clock_enable();
	i2c1_digital_filter(1);
	i2c1_analog_filter_disable();

	// tSCL Calculation Layout (48MHZ - 100KHZ Specification Metrics)
	i2c1_timing_prescaler(0xB);
	i2c1_low_period(0x13);
	i2c1_high_period(0xF);
	i2c1_hold_timing(0x2);
	i2c1_setup_timing(0x4);

	/*** Communication Wakeup ***/
	i2c1_enable();
	i2c1_addressing_mode(I2C_ADDR_7BIT);
	i2c1_autoend_enable(); // Enable auto-stop logic to support buffer transfers

	// Check if a hardware transaction is currently already running
	if(!i2c1_get_start()){
		if(i2c1_is_idle()){
			// Step 1: Tell PCF8563 we want to look at register address 0x02 (Seconds)
			uint8_t rtc_register_pointer = 0x02;

			if (i2c1_write_buffer(PCF8563, &rtc_register_pointer, 1U)) {
				// Step 2: Read the 2 raw active time bytes back securely
				if (i2c1_read_buffer(PCF8563, time_test_buffer, 2U)) {
					// Success! Hardware responded perfectly, data is now safe inside your array
					(void)time_test_buffer;
				}
			}
		}
	}
}

/*** i2c1 GET ***/
static i2c1_get get_setup = {
	.status = i2c1_status,
	.is_idle = i2c1_is_idle,
	.pecr = i2c1_get_pecr,
	.rxdata = i2c1_get_rxdata,
	.low_period = i2c1_get_low_period,
	.high_period = i2c1_get_high_period,
	.hold_timing = i2c1_get_hold_timing,
	.setup_timing = i2c1_get_setup_timing,
	.timing_prescaler = i2c1_get_timing_prescaler,
	.start = i2c1_get_start,
};
/*** i2c1 SET ***/
static i2c1_set set_setup = {
	.digital_filter = i2c1_digital_filter,
	.slave_address = i2c1_slave_address,
	.direction = i2c1_direction,
	.addressing_mode = i2c1_addressing_mode,
	.nbytes = i2c1_nbytes,
	.own_address = i2c1_own_address,
	.low_period = i2c1_low_period,
	.high_period = i2c1_high_period,
	.hold_timing = i2c1_hold_timing,
	.setup_timing = i2c1_setup_timing,
	.timing_prescaler = i2c1_timing_prescaler,
	.bus_timeout = i2c1_bus_timeout,
	.txdata = i2c1_set_txdata,

	.reload_enable = i2c1_reload_enable,
	.reload_disable = i2c1_reload_disable,
	.autoend_enable = i2c1_autoend_enable,
	.autoend_disable = i2c1_autoend_disable,
	.pecbyte_enable = i2c1_pecbyte_enable,
	.pecbyte_disable = i2c1_pecbyte_disable,
};
/*** i2c1 V-TABLE ***/
static i2c1_run run_setup = {
	.init = init,
	.clock_enable = i2c1_clock_enable,
	.clock_disable = i2c1_clock_disable,
	.enable = i2c1_enable,
	.disable = i2c1_disable,
	.analog_filter_enable = i2c1_analog_filter_enable,
	.analog_filter_disable = i2c1_analog_filter_disable,
	.software_reset =  i2c1_software_reset,
	.clock_stretch_enable = i2c1_clock_stretch_enable,
	.clock_stretch_disable = i2c1_clock_stretch_disable,
	.general_call_enable = i2c1_general_call_enable,
	.general_call_disable = i2c1_general_call_disable,
	.pec_enable = i2c1_pec_enable,
	.pec_disable = i2c1_pec_disable,
	.mode10_read_enable = i2c1_mode10_read_enable,
	.mode10_read_disable = i2c1_mode10_read_disable,
	.reload_enable = i2c1_reload_enable,
	.reload_disable = i2c1_reload_disable,
	.autoend_enable = i2c1_autoend_enable,
	.autoend_disable = i2c1_autoend_disable,
	.pecbyte_enable = i2c1_pecbyte_enable,
	.pecbyte_disable = i2c1_pecbyte_disable,
	.start = i2c1_start,
	.stop = i2c1_stop,
	.own_address_10bit_mode_enable = i2c1_own_address_10bit_mode_enable,
	.own_address_10bit_mode_disable = i2c1_own_address_10bit_mode_disable,
	.own_address_enable = i2c1_own_address_enable,
	.own_address_disable = i2c1_own_address_disable,
	.idle_timeout_detect_enable = i2c1_idle_timeout_detect_enable,
	.idle_timeout_detect_disable = i2c1_idle_timeout_detect_disable,
	.timeout_enable = i2c1_timeout_enable,
	.timeout_disable = i2c1_timeout_disable,
	.reset = i2c1_reset,
	.wait_for_bus_idle = wait_for_bus_idle,
	.write_buffer = i2c1_write_buffer,
	.read_buffer = i2c1_read_buffer,
};
/*** i2c1 CALLBACK ***/
static i2c1_irq irq_setup = {
	.ev_handler_callback = NULL,
	.er_handler_callback = NULL
};
/*** i2c1 HANDLER ***/
static i2c1_handler i2c1_setup = {
	.par = &par_setup,
	.get = &get_setup,
	.set = &set_setup,
	.irq = &irq_setup,
	.run = &run_setup
};
/*** i2c1 ACCESSOR FUNCTION ***/
i2c1_handler* i2c1(void){return &i2c1_setup;}

/*** EOF ***/

