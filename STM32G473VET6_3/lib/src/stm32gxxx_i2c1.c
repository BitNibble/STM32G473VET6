/************************************************************************
	STM32GXXX_I2C1
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4
Date:     02/07/2026
************************************************************************/
#include "stm32gxxx_i2c1.h"

typedef struct
{
    uint8_t presc;
    uint8_t scldel;
    uint8_t sdadel;
    uint8_t sclh;
    uint8_t scll;
} I2C_TIMING;

/*** i2c1 PARAMETER ***/
static i2c1_par par_setup = {
	.gpio = NULL,
	.af = 0,
	.pin_1 = 0,
	.pin_2 = 0,
	.var_1 = 0,
	.var_2 = 0
};

/*** Procedure & Function Definition ***/
uint8_t _i2c1_device_mode(uint8_t device_address, uint8_t r_w){
	return (device_address << 1) | (r_w & 0x01);
}
void i2c1_clock_enable(void) {
	exe()->set_reg(&dev()->sys->rcc->APB1ENR1,RCC_APB1ENR1_I2C1EN);
}
void i2c1_clock_disable(void) {
	exe()->clear_reg(&dev()->sys->rcc->APB1ENR1,RCC_APB1ENR1_I2C1EN);
}
void i2c1_clock_configure(void) {
	// setting the SCLH and SCLL bits in the I2C_TIMINGR register.
}
void i2c1_digital_filter(uint8_t filter) {
	exe()->write_field_value(&dev()->comm->i2c1->CR1,I2C_CR1_DNF,I2C_CR1_DNF_Pos,filter);
}
void i2c1_analog_filter_enable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_ANFOFF);
}
void i2c1_analog_filter_disable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_ANFOFF);
}
void i2c1_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
uint8_t _i2c1_is_enabled(void) {
	return exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
void i2c1_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR1,I2C_CR1_PE);
}
uint8_t _i2c1_is_disabled(void) {
	return !exe()->get_field_value(dev()->comm->i2c1->CR1,I2C_CR1_PE,I2C_CR1_PE_Pos);
}
void i2c1_reset(void) {
	i2c1_disable();
	while(!_i2c1_is_disabled());
	i2c1_enable();
}
void i2c1_slave_address(uint8_t device_ID) {
	exe()->write_field_value(&dev()->comm->i2c1->CR2,I2C_CR2_SADD,I2C_CR2_SADD_Pos,device_ID);
}
void i2c1_direction(uint8_t r_w) {
	if(r_w)
		exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_RD_WRN);
	else
		exe()->clear_reg(&dev()->comm->i2c1->CR2,I2C_CR2_RD_WRN);
}
void i2c1_start(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_START);
}
void i2c1_stop(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_STOP);
}
void i2c1_nbytes(uint8_t nbytes) {
	exe()->write_field_value(&dev()->comm->i2c1->CR2,I2C_CR2_NBYTES,I2C_CR2_NBYTES_Pos,nbytes);
}
void i2c1_reload_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_RELOAD);
}
void i2c1_reload_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR2,I2C_CR2_RELOAD);
}
void i2c1_autoend_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_AUTOEND);
}
void i2c1_autoend_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR2,I2C_CR2_AUTOEND);
}
void i2c1_pecbyte_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->CR2,I2C_CR2_PECBYTE);
}
void i2c1_pecbyte_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->CR2,I2C_CR2_PECBYTE);
}
void i2c1_own_address(uint8_t address) {
	exe()->write_field_value(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1,I2C_OAR1_OA1_Pos,address);
}
void i2c1_own_address_enable(void) {
	exe()->set_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
void i2c1_own_address_disable(void) {
	exe()->clear_reg(&dev()->comm->i2c1->OAR1,I2C_OAR1_OA1EN);
}
void i2c1_restart(void) {
}
uint32_t i2c1_status(void) { // ACK NACK & ERROR FLAGS
	return dev()->comm->i2c1->ISR;
}
void i2c1_poll(uint16_t timeout){ // WAIR_READY
}
uint8_t i2c1_get_pecr(void) {
	return exe()->get_field_value(dev()->comm->i2c1->PECR,I2C_PECR_PEC,I2C_PECR_PEC_Pos);
}
uint8_t i2c1_get_rxdata(void) {
	return exe()->get_field_value(dev()->comm->i2c1->RXDR,I2C_RXDR_RXDATA,I2C_RXDR_RXDATA_Pos);
}
void i2c1_set_txdata(uint8_t data) {
	return exe()->write_field_value(&dev()->comm->i2c1->TXDR,I2C_TXDR_TXDATA,I2C_TXDR_TXDATA_Pos, data);
}
uint8_t i2c1_master_write(uint8_t var_twiData_u8){return 0;}
uint8_t i2c1_master_read(uint8_t ack_nack){return 0;}

/*** i2c1 GET ***/
static i2c1_get get_setup = {
	.get_1 = NULL,
	.get_2 = NULL,
	.status = i2c1_status,
	.pecr = i2c1_get_pecr,
	.rxdata = i2c1_get_rxdata,
};
/*** i2c1 SET ***/
static i2c1_set set_setup = {
	.set_1 = NULL,
	.set_2 = NULL,
	.slave_address = i2c1_slave_address,
	.direction = i2c1_direction,
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
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL,
	.clock_enable = i2c1_clock_enable,
	.clock_disable = i2c1_clock_disable,
	.digital_filter = i2c1_digital_filter,
	.analog_filter_enable = i2c1_analog_filter_enable,
	.analog_filter_disable = i2c1_analog_filter_disable,
	.enable = i2c1_enable,
	.disable = i2c1_disable,
	.reset = i2c1_reset,
	.start = i2c1_start,
	.stop = i2c1_stop,
	.own_address_enable= i2c1_own_address_enable,
	.own_address_disable = i2c1_own_address_disable,
};
/*** i2c1 CALLBACK ***/
static i2c1_irq irq_setup = {
	.callback_1 = NULL,
	.callback_2 = NULL
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

