/************************************************************************
	TEMPLATE MULTI INSTANCE
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: MCU
Date:     02/07/2026
************************************************************************/
#include "template_instance.h"

/*** INSTANCE CALLBACK ***/
static instance_irq irq_default = {
	.callback_1 = NULL,
	.callback_2 = NULL
};
/*** INSTANCE V-TABLE ***/
static instance_run run_setup = {
	.config = NULL,
	.proc_1 = NULL,
	.proc_2 = NULL,
	.func_1 = NULL,
	.func_2 = NULL
};

/*** INSTANCE INITIALIZE ***/
instance_handler instance_enable(instance_par par) {
	/*** INSTANCE HANDLER ***/
	instance_handler instance_setup = {
		.par = par,
		.irq = irq_default,
		.run = &run_setup
	};

	return instance_setup;
}

/*** EOF ***/

