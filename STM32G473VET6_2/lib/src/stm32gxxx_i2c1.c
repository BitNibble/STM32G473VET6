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

typedef struct
{
    uint8_t presc;
    uint8_t scldel;
    uint8_t sdadel;
    uint8_t sclh;
    uint8_t scll;
} I2C_TIMING;

static volatile uint32_t i2c1_cr2;

/*** i2c1 PARAMETER ***/
static i2c1_par par_setup = {
	.gpio = NULL,
	.af = 0,
	.pin_scl = 0,
	.pin_sda = 0,
	.bus_speed = 0,
	.address_mode = 0
};

/*** Procedure & Function Definition ***/
void i2c1_clock_enable(void) {
	exe()->set_reg(&dev()->sys->rcc->APB1ENR1,RCC_APB1ENR1_I2C1EN);
}
void i2c1_clock_disable(void) {
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
/*******************  Bit definition for I2C_CR1 register  *******************/
uint8_t _i2c1_is_enabled(void) {
	return exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
uint8_t _i2c1_is_disabled(void) {
	return !exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
void i2c1_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
void i2c1_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
void i2c1_digital_filter(uint8_t filter) {
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
void i2c1_analog_filter_enable(void) {
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
void i2c1_analog_filter_disable(void) {
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
void i2c1_software_reset(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_SWRST);
}
void i2c1_clock_stretch_enable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_NOSTRETCH);
}
void i2c1_clock_stretch_disable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_NOSTRETCH);
}
void i2c1_general_call_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_GCEN);
}
void i2c1_general_call_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_GCEN);
}
void i2c1_pec_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PECEN);
}
void i2c1_pec_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PECEN);
}
/******************  Bit definition for I2C_CR2 register  ********************/
void i2c1_slave_address(uint16_t device_ID) {
	uint16_t shifted_address = (device_ID << 1);
	exe()->write_field_value(&i2c1_cr2, I2C_CR2_SADD, I2C_CR2_SADD_Pos, shifted_address);
}
void i2c1_direction(uint8_t r_w) {
	if(r_w)
		exe()->set_reg(&i2c1_cr2, I2C_CR2_RD_WRN);
	else
		exe()->clear_reg(&i2c1_cr2, I2C_CR2_RD_WRN);
}
void i2c1_addressing_mode(i2c_addr_mode_t mode) {
	if(mode == 10)
		exe()->set_reg(&i2c1_cr2, I2C_CR2_ADD10);
	else
		exe()->clear_reg(&i2c1_cr2, I2C_CR2_ADD10);
}
void i2c1_mode10_read_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_HEAD10R);
}
void i2c1_mode10_read_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_HEAD10R);
}
void i2c1_nbytes(uint8_t nbytes) {
	exe()->write_field_value(&i2c1_cr2, I2C_CR2_NBYTES, I2C_CR2_NBYTES_Pos, nbytes);
}
void i2c1_reload_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_RELOAD);
}
void i2c1_reload_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_RELOAD);
}
void i2c1_autoend_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_AUTOEND);
}
void i2c1_autoend_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_AUTOEND);
}
void i2c1_pecbyte_enable(void) {
	exe()->set_reg(&i2c1_cr2, I2C_CR2_PECBYTE);
}
void i2c1_pecbyte_disable(void) {
	exe()->clear_reg(&i2c1_cr2, I2C_CR2_PECBYTE);
}
void i2c1_start(void) {
	uint32_t final_hardware_cmd = i2c1_cr2 | I2C_CR2_START;
	exe()->write_field_encoded(&dev()->comm->i2c1->CR2, 0xFFFFFFFFU, final_hardware_cmd);

	uint32_t persistent_mask = I2C_CR2_NBYTES | I2C_CR2_RD_WRN | I2C_CR2_START;
	i2c1_cr2 = exe()->_imask(i2c1_cr2, persistent_mask);
}
void i2c1_stop(void) {
	// STOP can be asserted directly to hardware safely to terminate/abort sequences
	exe()->set_reg(&dev()->comm->i2c1->CR2, I2C_CR2_STOP);
}
/*******************  Bit definition for I2C_OAR1 register  ******************/
void i2c1_own_address(uint8_t address) {
	exe()->write_field_value(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1,I2C_OAR1_OA1_Pos,address);
}
void i2c1_own_address_10bit_mode_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1MODE);
}
void i2c1_own_address_10bit_mode_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1MODE);
}
void i2c1_own_address_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
void i2c1_own_address_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
/*******************  Bit definition for I2C_TIMINGR register *******************/
void i2c1_low_period(uint8_t ll) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLL,I2C_TIMINGR_SCLL_Pos,ll);
}
void i2c1_high_period(uint8_t hh) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLH,I2C_TIMINGR_SCLH_Pos,hh);
}
void i2c1_hold_time(uint8_t hold) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SDADEL,I2C_TIMINGR_SDADEL_Pos,hold & 0xF);
}
void i2c1_setup_time(uint8_t setup) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_SCLDEL,I2C_TIMINGR_SCLDEL_Pos,setup & 0xF);
}
void i2c1_timing_prescaler(uint8_t prescaler) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMINGR,I2C_TIMINGR_PRESC,I2C_TIMINGR_PRESC_Pos,prescaler & 0xF);
}
/******************* Bit definition for I2C_TIMEOUTR register *******************/
void i2c1_bus_timeout(uint16_t timeout) {
	exe()->write_field_value(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMEOUTA,I2C_TIMEOUTR_TIMEOUTA_Pos,timeout & 0x0FFF);
}
void i2c1_idle_timeout_detect_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIDLE);
}
void i2c1_idle_timeout_detect_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIDLE);
}
uint8_t i2c1_idle_detect(void) {
	return exe()->get_field_value(dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIDLE,I2C_TIMEOUTR_TIDLE_Pos);
}
void i2c1_timeout_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMOUTEN);
}
void i2c1_timeout_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->TIMEOUTR,I2C_TIMEOUTR_TIMOUTEN);
}
/******************  Bit definition for I2C_ISR register  *********************/
uint32_t i2c1_status(void) { // ACK NACK & ERROR FLAGS
	return dev()->comm->i2c1->ISR;
}
void i2c1_poll(uint16_t timeout){ // WAIR_READY
}
/******************  Bit definition for I2C_PECR register  *********************/
uint8_t i2c1_get_pecr(void) {
	return exe()->get_field_value(dev()->comm->i2c1->PECR,I2C_PECR_PEC,I2C_PECR_PEC_Pos);
}
/******************  Bit definition for I2C_RXDR register  *********************/
uint8_t i2c1_get_rxdata(void) {
	return exe()->get_field_value(dev()->comm->i2c1->RXDR,I2C_RXDR_RXDATA,I2C_RXDR_RXDATA_Pos);
}
/******************  Bit definition for I2C_TXDR register  *********************/
void i2c1_set_txdata(uint8_t data) {
	exe()->write_field_value(&dev()->comm->i2c1->TXDR,I2C_TXDR_TXDATA,I2C_TXDR_TXDATA_Pos, data);
}
/*** Procedure & Function Definition ***/
void i2c1_reset(void) {
	i2c1_disable();
	while(!_i2c1_is_disabled());
	i2c1_enable();
}
void i2c1_clock_configure(void) {
	// setting the SCLH and SCLL bits in the I2C_TIMINGR register.
}
// Universal non-blocking status check helper
uint8_t i2c1_get_flag(uint32_t flag_mask) {
    // Read the whole register and isolate the single flag bit
    return (dev()->comm->i2c1->ISR & flag_mask) ? 1U : 0U;
}

// Fixed-timeout polling engine to protect your MCU from locking up indefinitely on bus faults
uint8_t i2c1_wait_flag_timeout(uint32_t flag_mask, uint8_t status_expected, uint32_t timeout_loops) {
    volatile uint32_t timeout = timeout_loops;
    while (i2c1_get_flag(flag_mask) != status_expected) {
        if (--timeout == 0) {
            return 0; // Operation failed / Timed out
        }
    }
    return 1; // Success
}

/******************  Extended Driver Infrastructure  *********************/

// Helper to safely read specific flags from the ISR status register
uint8_t i2c1_get_status_flag(uint32_t msk) {
	// Uses your get_field_value tool (Pos is 0 since we want the masked raw bit location)
	return exe()->get_field_value(dev()->comm->i2c1->ISR, msk, 0) ? 1U : 0U;
}

// Fixed loop timeout polling engine to prevent the MCU from hanging on a dead bus
uint8_t i2c1_wait_status_flag(uint32_t msk, uint8_t expected_state, uint32_t timeout_loops) {
	volatile uint32_t timeout = timeout_loops;
	while (i2c1_get_status_flag(msk) != expected_state) {
		if (--timeout == 0) {
			return 0; // Failed / Timed Out
		}
		// If a NACK occurs during transmission, abort early
		if (msk != I2C_ISR_NACKF && i2c1_get_status_flag(I2C_ISR_NACKF)) {
			exe()->set_reg(&dev()->comm->i2c1->ICR, I2C_ICR_NACKCF); // Clear NACK flag
			return 0;
		}
	}
	return 1; // Success
}

/******************  High-Level API Functions  *********************/

// Universal master buffer writer function
uint8_t i2c1_write_buffer(uint16_t device_id, uint8_t* p_data, uint8_t length) {
	if (length == 0 || exe()->isPtrNull(p_data)) return 0;

	// 1. Stage the transaction parameters into your global shadow register
	i2c1_slave_address(device_id);
	i2c1_direction(0); // 0 = Write
	i2c1_nbytes(length);

	// 2. Clear out any leftover hardware status error flags before starting
	exe()->set_reg(&dev()->comm->i2c1->ICR, 0x3F38U);

	// 3. Fire the hardware start sequence!
	i2c1_start();

	// 4. Stream data out sequentially
	for (uint8_t i = 0; i < length; i++) {
		// Wait for TXIS (Transmit Interrupt Status) flag indicating TXDR is empty
		if (!i2c1_wait_status_flag(I2C_ISR_TXIS, 1, 100000UL)) {
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
uint8_t i2c1_read_buffer(uint16_t device_id, uint8_t* p_buffer, uint8_t length) {
	if (length == 0 || exe()->isPtrNull(p_buffer)) return 0;

	// 1. Stage parameters
	i2c1_slave_address(device_id);
	i2c1_direction(1); // 1 = Read
	i2c1_nbytes(length);

	exe()->set_reg(&dev()->comm->i2c1->ICR, 0x3F38U);

	// 2. Fire Start
	i2c1_start();

	// 3. Stream data in sequentially
	for (uint8_t i = 0; i < length; i++) {
		// Wait for RXNE (Receive Not Empty) flag indicating data has arrived
		if (!i2c1_wait_status_flag(I2C_ISR_RXNE, 1, 100000UL)) {
			return 0;
		}
		// Fetch the raw byte out of hardware
		p_buffer[i] = i2c1_get_rxdata();
	}

	return 1;
}

uint8_t i2c1_master_write(uint8_t var_twiData_u8){return 0;}
uint8_t i2c1_master_read(uint8_t ack_nack){return 0;}

/*** i2c1 GET ***/
static i2c1_get get_setup = {
	.status = i2c1_status,
	.pecr = i2c1_get_pecr,
	.rxdata = i2c1_get_rxdata,
};
/*** i2c1 SET ***/
static i2c1_set set_setup = {
	.digital_filter = i2c1_digital_filter,
	.slave_address = i2c1_slave_address,
	.direction = i2c1_direction,
	.addressing_mode = i2c1_addressing_mode,

	.nbytes = i2c1_nbytes,
	.own_address = i2c1_own_address,
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
	.init = NULL,
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

	.reset = i2c1_reset,
	.own_address_enable= i2c1_own_address_enable,
	.own_address_disable = i2c1_own_address_disable,
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

