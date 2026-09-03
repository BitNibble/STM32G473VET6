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
void BUFF_push(buffer_par* par, BUFF_var data);
BUFF_var* BUFF_raw(buffer_par* par);
void BUFF_flush(buffer_par* par);
static buffer_par buff_par_inic( uint8_t size_buff, BUFF_var* buff );

/*** BUFF Auxiliar ***/
static buffer_par buff_par_inic( uint8_t size_buff, BUFF_var* buff )
{
	buffer_par buff_par = {
		.orig = buff,
		.head = buff,
		.end = buff + ( size_buff )
	};
	return buff_par;
}
static buffer_run run_setup = {
	.push = BUFF_push,
	.raw = BUFF_raw,
	.flush = BUFF_flush
};
/*** BUFF Procedure & Function Definition ***/
BUFF_Handler BUFF_enable( uint8_t size_buff, BUFF_var* buff )
{
	BUFF_Handler ret = {
		.par = buff_par_inic( size_buff, buff ),
		.run = &run_setup
	};
	return ret;
}

void BUFF_push( buffer_par* par, BUFF_var data ){
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

BUFF_var* BUFF_raw( buffer_par* par ){
		return par->orig;
}

void BUFF_flush( buffer_par* par ){
	BUFF_var* head;
	head = par->orig;
	par->head = head;
	*head = 0;
}

/***EOF***/

