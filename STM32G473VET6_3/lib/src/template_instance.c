/************************************************************************
	TEMPLATE MULTI INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#include "template_instance.h"

/*** Procedure & Function Definition ***/

/*** INSTANCE V-TABLE ***/
static instance_run run_setup = {
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL
};
/*** INSTANCE INITIALIZE ***/
instance_handler instance_enable(void) {
	/*** INSTANCE HANDLER ***/
	instance_handler instance_setup = {
		.par = {
			.var_1 = 0,
			.var_2 = 0,
			.handler = NULL
		},
		.run = &run_setup
	};
	return instance_setup;
}

/*** EOF ***/

