/************************************************************************
	74HC595
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License     
Hardware: 74HC595
Date:     25/10/2020
************************************************************************/
/*** File Library ***/
#include "74hc595.h"

/*** File Header ***/
void HC595_shift_bit(hc595_par* par, uint8_t state);
void HC595_shift_ibyte(hc595_par* par, uint8_t byte);
void HC595_shift_byte(hc595_par* par, uint8_t byte);
void HC595_ibyte(hc595_par* par, uint8_t byte);
void HC595_byte(hc595_par* par, uint8_t byte);
void HC595_shift_out(hc595_par* par);

/*** 74HC595 Procedure & Function Definition ***/
HC595_Handler hc595_enable(volatile IO_var *ddr, volatile IO_var *port, uint8_t datapin, uint8_t clkpin, uint8_t outpin)
{
	HC595_Handler setup_hc595 = {
		.par = {
			.hc595_DDR = ddr,
			.hc595_PORT = port,
			.HC595_datapin = datapin,
			.HC595_clkpin = clkpin,
			.HC595_outpin = outpin
		},
		// V-table
		.shift_bit = HC595_shift_bit,
		.shift_ibyte = HC595_shift_ibyte,
		.shift_byte = HC595_shift_byte,
		.ibyte = HC595_ibyte,
		.byte = HC595_byte,
		.out = HC595_shift_out
	};
	#if defined (STM32F4XXX)
		*setup_hc595.par.hc595_DDR &= (IO_var) ~((3 << (datapin * 2)) | (3 << (clkpin * 2)) | (3 << (outpin * 2)));
		*setup_hc595.par.hc595_DDR |= ((1 << (datapin * 2)) | (1 << (clkpin * 2)) | (1 << (outpin * 2)));
	#else
		*setup_hc595.par.hc595_DDR |= (1 << datapin) | (1 << clkpin) | (1 << outpin);
	#endif
		*setup_hc595.par.hc595_PORT &= ~((1 << datapin) | (1 << clkpin) | (1 << outpin));
		
	return setup_hc595;
}

void HC595_shift_bit(hc595_par* par, uint8_t state)
{
	if (state)
		*par->hc595_PORT |= (1 << par->HC595_datapin); // Data bit HIGH
	else
		*par->hc595_PORT &= ~(1 << par->HC595_datapin); // Data bit LOW
	*par->hc595_PORT |= (1 << par->HC595_clkpin); // Shift bit
	*par->hc595_PORT &= ~(1 << par->HC595_clkpin); //Shift disable
}

void HC595_shift_ibyte(hc595_par* par, uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(par, byte & (1 << i));
}

void HC595_ibyte(hc595_par* par, uint8_t byte)
{
	HC595_shift_ibyte(par, byte);
	HC595_shift_out(par);
}

void HC595_shift_byte(hc595_par* par, uint8_t byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
		HC595_shift_bit(par, byte & (1 << (7 - i)));
}

void HC595_byte(hc595_par* par, uint8_t byte)
{
	HC595_shift_byte(par, byte);
	HC595_shift_out(par);
}

void HC595_shift_out(hc595_par* par)
{
	*par->hc595_PORT |= (1 << par->HC595_outpin); // Output enable
	*par->hc595_PORT &= ~(1 << par->HC595_outpin); // Output disable
}

/*** EOF ***/

