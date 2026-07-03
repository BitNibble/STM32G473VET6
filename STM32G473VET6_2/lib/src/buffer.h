/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     17112022
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _BUFFER_H_
	#define _BUFFER_H_

/*** File Library ***/
#include <inttypes.h>
/*** File Constant & Macro ***/
#define BUFF_var char
/*** File TypeDef ***/
typedef struct {
	BUFF_var* orig;
	BUFF_var* head;
	BUFF_var* end;
}buffer_par;
typedef const struct {
	void (*push)(buffer_par* par, BUFF_var data);
	BUFF_var* (*raw)(buffer_par* par);
	void (*flush)(buffer_par* par);
}buffer_run;
/*** BUFFER TypeDef ***/
struct buffer
{
	buffer_par par;
	buffer_run* run;
};
typedef struct buffer BUFF_Handler;

BUFF_Handler BUFF_enable(uint8_t size_buff, BUFF_var* buff);

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

