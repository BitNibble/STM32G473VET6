/************************************************************************
	TEMPLATE SINGLETON
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#include "template_singleton.h"

/*** SINGLETON PARAMETER ***/
static singleton_par par_setup= {
	.var_1 = 0,
	.var_2 = 0
};
/*** SINGLETON GET PARAMETER ***/
static singleton_get_par get_par_setup = {
	.var_1 = NULL,
	.var_2 = NULL
};
/*** SINGLETON SET PARAMETER ***/
static singleton_set_par set_par_setup = {
	.var_1 = NULL,
	.var_2 = NULL
};
/*** SINGLETON CALLBACK ***/
static singleton_irq irq_setup = {
	.callback_1 = NULL,
	.callback_2 = NULL
};
/*** SINGLETON V-TABLE ***/
static singleton_run run_setup = {
	.config = NULL,
	.init = NULL,
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL
};
/*** SINGLETON HANDLER ***/
singleton_handler singleton_setup = {
	.par = &par_setup,
	.get_par = &get_par_setup,
	.set_par = &set_par_setup,
	.irq = &irq_setup,
	.run = &run_setup
};
/*** ACCESSOR FUNCTION ***/
singleton_handler* singleton(void){return &singleton_setup;}

/*** EOF ***/

