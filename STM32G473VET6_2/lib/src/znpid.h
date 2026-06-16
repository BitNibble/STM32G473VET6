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
}kparameter;
typedef struct {
	double Err_past; // Last Error reading
	double dy; // difference error y axis points.
	double dx; // difference time x axis points.
	double integral; // progression
	double derivative; // rate of growth (tangent), or derivative
}auxparameter;
typedef struct {
	kparameter k;
	auxparameter aux;
	double SetPoint; // desired output
	double PV; // output feedback
	double OP; // output signal
}znpidparameter;

/*** ZNPID ***/
struct znpid{
	znpidparameter par;
	/******/
	void (*set_kc)(znpidparameter* par, double kc);
	void (*set_ki)(znpidparameter* par, double ki);
	void (*set_kd)(znpidparameter* par, double kd);
	void (*set_SP)(znpidparameter* par, double setpoint);
	double (*output)(znpidparameter* par, double PV, double timelapse);
};
typedef struct znpid ZNPID_Handler;

ZNPID_Handler ZNPIDenable(void);

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

