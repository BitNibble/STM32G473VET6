/********************************************************************
	EXPLODE
Author:   <sergio.salazar.santos@gmail.com>
License:  Free beer
Hardware: all
Date:     16032021
Comment:
	Pin Analysis
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
********************************************************************/
#include "explode.h"

IO_var EXPLODE_update(explode_par* par, IO_var x);
IO_var EXPLODE_hh(explode_par* par);
IO_var EXPLODE_ll(explode_par* par);
IO_var EXPLODE_lh(explode_par* par);
IO_var EXPLODE_hl(explode_par* par);

static const explode_run run_setup = {
	.update = EXPLODE_update,
	.hh = EXPLODE_hh,
	.ll = EXPLODE_ll,
	.lh = EXPLODE_lh,
	.hl = EXPLODE_hl
};

/*** EXPLODE Procedure & Function Definition ***/
EXPLODE_Handler EXPLODE_enable( void )
{
	EXPLODE_Handler setup = {
		.par = {
				.XI = 0,
				.XF = 0,
				.DIFF =0,
				.HH = 0,
				.LL = 0,
				.LH = 0,
				.HL = 0
			},
		.run = &run_setup,
	};
	return setup;
}
// boot
IO_var EXPLODE_update(explode_par* par, IO_var x)
{
	par->XI = par->XF;
	par->XF = x;
	par->DIFF = (par->XF ^ par->XI);

	par->HH = (par->XI & par->XF);
	par->LL = ~(par->XI | par->XF);
	par->LH = (par->DIFF & par->XF);
	par->HL = (par->DIFF & par->XI);
	return par->DIFF;
}
// hh
IO_var EXPLODE_hh(explode_par* par)
{
	return (par->XI & par->XF);
}
// ll
IO_var EXPLODE_ll(explode_par* par)
{
	return ~(par->XI | par->XF);
}
// lh
IO_var EXPLODE_lh(explode_par* par)
{
	return (par->DIFF & par->XF);
}
// hl
IO_var EXPLODE_hl(explode_par* par)
{
	return (par->DIFF & par->XI);
}

/***EOF***/

