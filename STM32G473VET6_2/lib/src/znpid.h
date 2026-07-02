/************************************************************************
	ZNPID
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Atmega 128
Date:     17022021_start
Comment:

************************************************************************/
#ifndef _ZNPID_H_
	#define _ZNPID_H_

/*** File Library ***/
#include <inttypes.h>
/*** File TypeDef ***/
typedef struct {
	double c; // constant p
	double i; // constant i
	double d; // constant d
}k_par;
typedef struct {
	double Err_past; // Last Error reading
	double dy; // difference error y axis points.
	double dx; // difference time x axis points.
	double integral; // progression
	double derivative; // rate of growth (tangent), or derivative
}aux_par;
typedef struct {
	k_par k;
	aux_par aux;
	double SetPoint; // desired output
	double PV; // output feedback
	double OP; // output signal
}znpid_par;
typedef const struct {
	void (*set_kc)(znpid_par* par, double kc);
	void (*set_ki)(znpid_par* par, double ki);
	void (*set_kd)(znpid_par* par, double kd);
	void (*set_SP)(znpid_par* par, double setpoint);
	double (*output)(znpid_par* par, double PV, double timelapse);
}znpid_run;

/*** ZNPID ***/
struct znpid{
	znpid_par par;
	znpid_run* run;
};
typedef struct znpid ZNPID_Handler;

ZNPID_Handler ZNPID_enable(void);

#endif
/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

