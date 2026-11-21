/*****************************************
    stm32x_cordic.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*****************************************/
#ifndef STM32X_CORDIC_H
	#define STM32X_CORDIC_H

#include <stm32g4xx.h>

typedef enum
{
    CORDIC_COS,
    CORDIC_SIN,
    CORDIC_PHASE,
    CORDIC_MODULUS,
    CORDIC_ATAN,
    CORDIC_HCOS,
    CORDIC_HSIN,
    CORDIC_HATAN,
    CORDIC_LN,
    CORDIC_SQRT,

} cordic_operation;

/* CORDIC PARAMETER */

typedef struct
{
    int32_t arg_1;
    int32_t arg_2;

    int32_t out_1;
    int32_t out_2;

} cordic_arg;

typedef void (*cordic_vector)(cordic_arg *arg);

typedef const struct
{
    void (*q31)(cordic_operation operation, cordic_arg *arg);
    void (*q15)(cordic_operation operation, cordic_arg *arg);

} CORDIC_Handle;

/* CORDIC ACCESSOR */

CORDIC_Handle* cordic(void);

#endif

/*** EOF ***/
