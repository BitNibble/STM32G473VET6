/*****************************************
    stm32x_cordic.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*****************************************/
#include "stm32x_cordic.h"

#define CORDIC_TIMEOUT 32U

/*** CORDIC PARAMETER SNAPSHOT ***********************************************/

static cordic_arg par_setup = {0};

/*** 32 BIT *****************************************************************/
/* cordic_cos32 */
static void cordic_cos32(cordic_arg arg)
{
    CORDIC->CSR =
          0U
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_sin32 */
static void cordic_sin32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_phase32 */
static void cordic_phase32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_1
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_NARGS;

    CORDIC->WDATA = arg.arg_1;
    CORDIC->WDATA = arg.arg_2;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_modulus32 */
static void cordic_modulus32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_1
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_NARGS;

    CORDIC->WDATA = arg.arg_1;
    CORDIC->WDATA = arg.arg_2;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_atan32 */
static void cordic_atan32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_hcos32 */
static void cordic_hcos32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_hsin32 */
static void cordic_hsin32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_1
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_hatan32 */
static void cordic_hatan32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_1
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_ln32 */
static void cordic_ln32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_3
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}

/* cordic_sqrt32 */
static void cordic_sqrt32(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_3
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1;

    CORDIC->WDATA = arg.arg_1;

    arg.out_1 = CORDIC->RDATA;
    par_setup = arg;
}


/*** 16 BIT *****************************************************************/
/* cordic_cos16 */
static void cordic_cos16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    /*
     * One 16-bit argument is supplied in the lower half.
     * The CORDIC internally calculates the sine companion as well,
     * but this operation exposes the requested cosine result.
     */
    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_sin16 */
static void cordic_sin16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_phase16 */
static void cordic_phase16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_1
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA =
          ((uint32_t)(uint16_t)arg.arg_2 << 16)
        |  (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_modulus16 */
static void cordic_modulus16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_1
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA =
          ((uint32_t)(uint16_t)arg.arg_2 << 16)
        |  (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_atan16 */
static void cordic_atan16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_hcos16 */
static void cordic_hcos16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_hsin16 */
static void cordic_hsin16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_1
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_hatan16 */
static void cordic_hatan16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_2
        | CORDIC_CSR_FUNC_1
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_ln16 */
static void cordic_ln16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_3
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_SCALE_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}

/* cordic_sqrt16 */
static void cordic_sqrt16(cordic_arg arg)
{
    CORDIC->CSR =
          CORDIC_CSR_FUNC_3
        | CORDIC_CSR_FUNC_0
        | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1
        | CORDIC_CSR_ARGSIZE
        | CORDIC_CSR_RESSIZE;

    CORDIC->WDATA = (uint16_t)arg.arg_1;

    arg.out_1 = (int16_t)(CORDIC->RDATA & 0xFFFFU);
    par_setup = arg;
}


/*** 32 BIT VECTOR TABLE ****************************************************/

static const cordic_vector cordic32_vector[] =
{
    [CORDIC_COS]     = cordic_cos32,
    [CORDIC_SIN]     = cordic_sin32,
    [CORDIC_PHASE]   = cordic_phase32,
    [CORDIC_MODULUS] = cordic_modulus32,
    [CORDIC_ATAN]    = cordic_atan32,
    [CORDIC_HCOS]    = cordic_hcos32,
    [CORDIC_HSIN]    = cordic_hsin32,
    [CORDIC_HATAN]   = cordic_hatan32,
    [CORDIC_LN]      = cordic_ln32,
    [CORDIC_SQRT]    = cordic_sqrt32,
};


/*** 16 BIT VECTOR TABLE ****************************************************/

static const cordic_vector cordic16_vector[] =
{
    [CORDIC_COS]     = cordic_cos16,
    [CORDIC_SIN]     = cordic_sin16,
    [CORDIC_PHASE]   = cordic_phase16,
    [CORDIC_MODULUS] = cordic_modulus16,
    [CORDIC_ATAN]    = cordic_atan16,
    [CORDIC_HCOS]    = cordic_hcos16,
    [CORDIC_HSIN]    = cordic_hsin16,
    [CORDIC_HATAN]   = cordic_hatan16,
    [CORDIC_LN]      = cordic_ln16,
    [CORDIC_SQRT]    = cordic_sqrt16,
};

static void cordic32(cordic_operation operation, cordic_arg arg)
{
    cordic32_vector[operation](arg);
}

static void cordic16(cordic_operation operation, cordic_arg arg)
{
    cordic16_vector[operation](arg);
}

/*** CORDIC HANDLER *********************************************************/

cordic_handler cordic_setup =
{
    .par     = &par_setup,
    .q31 = cordic32,
    .q15 = cordic16
};


/*** CORDIC ACCESSOR ********************************************************/

cordic_handler* cordic(void)
{
    return &cordic_setup;
}

/*** EOF ***/

