/******************************************************************************
	BUFFER
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     17112022
Comment:
	Buffer
******************************************************************************/
/*** File Library ***/
#include "buffer.h"

/*** File Header ***/
void BUFF_push(bufferparameter* par, BUFF_var data);
BUFF_var* BUFF_raw(bufferparameter* par);
void BUFF_flush(bufferparameter* par);
bufferparameter buff_par_inic( uint8_t size_buff, BUFF_var* buff );

/*** BUFF Auxiliar ***/
bufferparameter buff_par_inic( uint8_t size_buff, BUFF_var* buff )
{
	bufferparameter buff_par;
	// inic VAR
	buff_par.orig = buff;
	buff_par.head = buff;
	buff_par.end = buff + ( size_buff ); // generic
	return buff_par;
}
/*** BUFF Procedure & Function Definition ***/
BUFF_Handler BUFF_enable( uint8_t size_buff, BUFF_var* buff )
{
	// OBJECT STRUCT
	BUFF_Handler ret;
	// inic VAR
	ret.par = buff_par_inic( size_buff, buff );
	// function pointers
	ret.push = BUFF_push;
	ret.raw = BUFF_raw;
	ret.flush = BUFF_flush;
	return ret; // return copy
}

void BUFF_push( bufferparameter* par, BUFF_var data ){
	BUFF_var* head; BUFF_var* next;
	head = par->head;
	if(data){
		if( head == par->end ){
			head = par->orig;
			next = head + 1;
		}else{
			next = head + 1;
		}
			*head = data;
			*next = 0;
			par->head = next;
	}
}

BUFF_var* BUFF_raw( bufferparameter* par ){
		return par->orig;
}

void BUFF_flush( bufferparameter* par ){
	BUFF_var* head;
	head = par->orig;
	par->head = head;
	*head = 0;
}

/***EOF***/

