/*************************************************************************
	ZNPID
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 128
Date:     17022021_start
Comment:

************************************************************************/
/*** File Library ***/
#include "znpid.h"

/*** File Constant & Macro ***/
#define ZNPID_outMAX 1023
#define ZNPID_outMIN -1023
#define BYTE_BITS 8
#define WORD_BITS 16
#define N_BITS 32
#define N_LIMBITS 33
#define H_BIT 31
#define L_BIT 0

/*** File Variable ***/
static double ZNPID_tmp;

/*** File Header ***/
void ZNPID_set_kc(znpidparameter* par, double kc);
void ZNPID_set_ki(znpidparameter* par, double ki);
void ZNPID_set_kd(znpidparameter* par, double kp);
void ZNPID_set_SP(znpidparameter* par, double setpoint);
double ZNPID_output(znpidparameter* par, double PV, double timelapse);
double ZNPID_integral(znpidparameter* par, double PV, double timelapse);
double ZNPID_derivative(znpidparameter* par, double PV, double timelapse);
double ZNPID_delta(double present_value, double past_value);
double ZNPID_sum(double value_1, double value_2);
double ZNPID_product(double value_1, double value_2);
znpidparameter znpid_par_inic(void);

/*** Tools ***/
void znpid_set_reg(volatile uint32_t* reg, uint32_t hbits);
void znpid_clear_reg(volatile uint32_t* reg, uint32_t hbits);
uint32_t znpid_get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n);
uint32_t znpid_get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos);
void znpid_write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void znpid_write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
void znpid_set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);
void znpid_set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data);
uint32_t znpid_get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n);
void znpid_set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data);

/*** ZNPID Auxiliar  ***/
znpidparameter znpid_par_inic(void)
{
	znpidparameter znpid_par;
	// initialize variables
	znpid_par.k.c = 1;
	znpid_par.k.i = 0;
	znpid_par.k.d = 0;
	znpid_par.SetPoint = 0;
	znpid_par.aux.Err_past = 0;
	znpid_par.aux.dy = 0;
	znpid_par.aux.dx = 0;
	znpid_par.aux.integral = 0;
	znpid_par.aux.derivative = 0;
	znpid_par.PV = 0;
	znpid_par.OP = 0;
	return znpid_par;
}
/*** ZNPID Procedure & Function Definition ***/
ZNPID_Handler ZNPIDenable(void)
{
	// LOCAL VARIABLES
	ZNPID_Handler znpid;
	// initialize variables
	znpid.par = znpid_par_inic();
	// Direccionar apontadores para PROTOTIPOS
	znpid.set_kc = ZNPID_set_kc;
	znpid.set_ki = ZNPID_set_ki;
	znpid.set_kd = ZNPID_set_kd;
	znpid.set_SP = ZNPID_set_SP;
	znpid.output = ZNPID_output;
	
	return znpid;
}

void ZNPID_set_kc(znpidparameter* par, double kc)
{
	par->k.c = kc;
}

void ZNPID_set_ki(znpidparameter* par, double ki)
{
	par->k.i = ki;
}

void ZNPID_set_kd(znpidparameter* par, double kd)
{	
	par->k.d = kd;
}

void ZNPID_set_SP(znpidparameter* par, double setpoint)
{
	par->SetPoint = setpoint;
}

double ZNPID_output(znpidparameter* par, double PV, double timelapse)
{
	double result;
	par->PV = PV;
	par->aux.dy = ZNPID_delta(par->SetPoint, PV);
	par->aux.dx = timelapse;
	result = ZNPID_product(par->k.c, par->aux.dy);
	ZNPID_tmp = ZNPID_product(par->k.i, ZNPID_integral(par, PV, timelapse));
	result = ZNPID_sum(result, ZNPID_tmp);
	ZNPID_tmp = ZNPID_product(par->k.d, ZNPID_derivative(par, PV, timelapse));
	result = ZNPID_sum(result, ZNPID_tmp);
	par->aux.Err_past = par->aux.dy;
	par->OP = result;
	if(result > ZNPID_outMAX)
		par->aux.integral = ZNPID_outMAX - (par->aux.dy * par->aux.dx) - (par->aux.derivative * par->aux.dx * par->aux.dx);
	else if(result < ZNPID_outMIN)
		par->aux.integral = ZNPID_outMIN + (par->aux.dy * par->aux.dx) + (par->aux.derivative * par->aux.dx * par->aux.dx);
	return result;
}

double ZNPID_integral(znpidparameter* par, double PV, double timelapse)
{
	ZNPID_tmp = ZNPID_product(ZNPID_sum(ZNPID_delta(par->SetPoint, PV), par->aux.Err_past), timelapse);
	ZNPID_tmp /= 2;
	return (par->aux.integral += ZNPID_tmp);
}

double ZNPID_derivative(znpidparameter* par, double PV, double timelapse)
{
	ZNPID_tmp = ZNPID_delta(ZNPID_delta(par->SetPoint, PV), par->aux.Err_past);
	return (par->aux.derivative = (ZNPID_tmp / timelapse));
}

double ZNPID_delta(double present_value, double past_value)
{
	return (present_value - past_value);
}

double ZNPID_sum(double value_1, double value_2)
{
	return (value_1 + value_2);
}

double ZNPID_product(double value_1, double value_2)
{
	return (value_1 * value_2);
}

/*** Tools ***/
inline void znpid_set_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg |= hbits;
}
inline void clear_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg &= ~hbits;
}
inline uint32_t znpid_get_reg_Msk(uint32_t reg, uint32_t Msk, uint8_t Pos)
{
	if(Pos > H_BIT){ Pos = L_BIT; reg = 0; }
	else{ reg &= Msk; reg = (reg >> Pos); }
	return reg;
}
inline void znpid_write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	uint32_t value = *reg;
	if(Pos > H_BIT){ Pos = L_BIT; }
	else{ data = (data << Pos); data &= Msk; value &= ~(Msk); value |= data; *reg = value; }
}
inline void znpid_set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint8_t Pos, uint32_t data)
{
	if(Pos > H_BIT){ Pos = L_BIT; }
	else{ data = (data << Pos); data &= Msk; *reg &= ~(Msk); *reg |= data; }
}
uint32_t znpid_get_reg_block(uint32_t reg, uint8_t size_block, uint8_t bit_n)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = L_BIT; reg = 0; }
	else{
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		reg &= (mask << bit_n);
		reg = (reg >> bit_n);
	}
	return reg;
}
void znpid_write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = H_BIT; }
	else{
		uint32_t value = *reg;
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		data &= mask; value &= ~(mask << bit_n);
		data = (data << bit_n);
		value |= data;
		*reg = value;
	}
}
void znpid_set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	if(bit_n > H_BIT){ bit_n = H_BIT; }
	else{
		uint32_t mask = (uint32_t)((1 << size_block) - 1);
		data &= mask;
		*reg &= ~(mask << bit_n);
		*reg |= (data << bit_n);
	}
}
uint32_t znpid_get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n)
{
	uint32_t value;
	if(size_block > N_BITS){ size_block = N_BITS; }
	uint32_t n = bit_n / N_BITS; bit_n = bit_n % N_BITS;
	value = *(reg + n );
	uint32_t mask = (uint32_t)((1 << size_block) - 1);
	value &= (mask << bit_n);
	value = (value >> bit_n);
	return value;
}
void znpid_set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t bit_n, uint32_t data)
{
	if(size_block > N_BITS){ size_block = N_BITS; }
	uint32_t n = bit_n / N_BITS; bit_n = bit_n % N_BITS;
	uint32_t mask = (uint32_t)((1 << size_block) - 1);
	data &= mask;
	*(reg + n ) &= ~(mask << bit_n);
	*(reg + n ) |= (data << bit_n);
}

/***File Interrupt***/

/***EOF***/

