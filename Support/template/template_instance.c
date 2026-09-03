/************************************************************************
	TEMPLATE SYNTAX MULTI INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#include "template_instance.h"

/*** Procedure & Function Definition ***/
void instance_init(instance_par* par);

/*** INSTANCE V-TABLE ***/
static instance_run run_setup = {
	.init = instance_init,
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL
};
/*** INSTANCE INITIALIZE ***/
instance_handler instance_enable(void* peripheral, uint8_t par_1, uint8_t par_2) {
	/*** INSTANCE HANDLER ***/
	instance_handler instance_setup = {
		.par = {
			.gpio = NULL,
			.af = 0,
			.var_1 = par_1,
			.var_2 = par_2,
			.handler = NULL
		},
		.run = &run_setup
	};
	/*** INITIALIZE ***/
	
	if (instance_setup.run.init) instance_setup.run.init(&instance_setup.par);
	
	return instance_setup;
}

void instance_init(instance_par* par){
	// GPIO, PERIPHERAL, DRIVER INIT
}

/*** EOF ***/

