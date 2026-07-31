/************************************************************************
	TEMPLATE SYNTAX SINGLETON
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#include "template_singleton.h"

/*** SINGLETON PARAMETER ***/
static singleton_par par_setup = {
	.gpio = NULL,
	.af = 0,
	.pin_1 = 0,
	.pin_2 = 0,
	.var_1 = 0,
	.var_2 = 0
};

/*** Procedure & Function Definition ***/

/*** SINGLETON GET ***/
static singleton_get get_setup = {
	.get_1 = NULL,
	.get_2 = NULL
};
/*** SINGLETON SET ***/
static singleton_set set_setup = {
	.set_1 = NULL,
	.set_2 = NULL
};
/*** SINGLETON V-TABLE ***/
static singleton_run run_setup = {
	.init = NULL,
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL
};
/*** SINGLETON CALLBACK ***/
static singleton_irq irq_setup = {
	.callback_1 = NULL,
	.callback_2 = NULL
};
/*** SINGLETON HANDLER ***/
static singleton_handler singleton_setup = {
	.par = &par_setup,
	.get = &get_setup,
	.set = &set_setup,
	.irq = &irq_setup,
	.run = &run_setup
};
/*** SINGLETON ACCESSOR FUNCTION ***/
singleton_handler* singleton(void){return &singleton_setup;}

/*** EOF ***/

