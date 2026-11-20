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
#define INTEGRAL_LIMIT 1023.0

/*** File Header ***/
void ZNPID_set_kc(znpid_par* par, double kc);
void ZNPID_set_ki(znpid_par* par, double ki);
void ZNPID_set_kd(znpid_par* par, double kp);
void ZNPID_set_SP(znpid_par* par, double setpoint);
double ZNPID_OP(znpid_par* par, double PV, double timelapse);
/*** ZNPID Auxiliar  ***/
znpid_par znpid_par_init(void)
{ // DEFAULT
	znpid_par znpid_par;
	// initialize variables
	znpid_par.k.c = 1;
	znpid_par.k.i = 0;
	znpid_par.k.d = 0;
	znpid_par.SetPoint = 0;
	znpid_par.aux.error = 0;
	znpid_par.aux.integral = 0;
	znpid_par.aux.derivative = 0;
	znpid_par.PV = 0;
	znpid_par.OP = 0;
	return znpid_par;
}
static znpid_run run_setup = {
	.set_kc = ZNPID_set_kc,
	.set_ki = ZNPID_set_ki,
	.set_kd = ZNPID_set_kd,
	.set_SP = ZNPID_set_SP,
	.get_OP = ZNPID_OP
};
/*** ZNPID Procedure & Function Definition ***/
ZNPID_Handler ZNPID_enable(void)
{
	// LOCAL VARIABLES
	ZNPID_Handler znpid = {
		.par = znpid_par_init(),
		.run = &run_setup
	};
	
	return znpid;
}

void ZNPID_set_kc(znpid_par* par, double kc)
{
	par->k.c = kc;
}

void ZNPID_set_ki(znpid_par* par, double ki)
{
	par->k.i = ki;
}

void ZNPID_set_kd(znpid_par* par, double kd)
{	
	par->k.d = kd;
}

void ZNPID_set_SP(znpid_par* par, double setpoint)
{
	par->SetPoint = setpoint;
}

double ZNPID_OP(znpid_par* par, double PV, double timelapse)
{
    // Safety check
    if(timelapse <= 0) return par->OP;

    double error = par->SetPoint - PV;

    // Proportional on error
    double P_term = par->k.c * error;

    // Integral on ERROR
    par->aux.integral += (error + par->aux.error) * timelapse / 2.0;
    par->aux.error = error;

    // Clamp integral to prevent excessive wind up
    if(par->aux.integral > INTEGRAL_LIMIT)
        par->aux.integral = INTEGRAL_LIMIT;
    if(par->aux.integral < -INTEGRAL_LIMIT)
        par->aux.integral = -INTEGRAL_LIMIT;

    double I_term = par->k.i * par->aux.integral;

    // Derivative on PV
    double dPV = (PV - par->PV) / timelapse;
    double D_term = -par->k.d * dPV;

    double result = P_term + I_term + D_term;

    // Anti-windup with safety
    if(result > ZNPID_outMAX) {
        result = ZNPID_outMAX;
        if(par->k.i != 0.0) {
            par->aux.integral = (ZNPID_outMAX - P_term - D_term) / par->k.i;
        }
    } else if(result < ZNPID_outMIN) {
        result = ZNPID_outMIN;
        if(par->k.i != 0.0) {
            par->aux.integral = (ZNPID_outMIN - P_term - D_term) / par->k.i;
        }
    }

    par->PV = PV;
    par->OP = result;

    return result;
}

/*** EOF ***/

