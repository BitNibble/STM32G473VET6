#include "template_singleton_v2.h"

static singleton_par par_setup =
{
    .var_1 = 0,
    .var_2 = 0
};


static singleton_get_par get_par_setup =
{
    .var_1 = NULL,
    .var_2 = NULL
};

static singleton_set_par set_par_setup =
{
    .var_1 = NULL,
    .var_2 = NULL
};

static singleton_irq irq_setup =
{
    .callback_1 = NULL,
    .callback_2 = NULL
};

static singleton_common common_setup =
{
    .init    = NULL,
    .enable  = NULL,
    .disable = NULL,
    .reset   = NULL
};

static singleton_block1 block1_setup =
{
    .proc_1 = NULL,
    .proc_2 = NULL,
    .func_1 = NULL,
    .func_2 = NULL
};

static singleton_block2 block2_setup =
{
    .proc_1 = NULL,
    .proc_2 = NULL
};

static singleton_block3 block3_setup =
{
    .proc_1 = NULL,
    .proc_2 = NULL
};

static singleton_block4 block4_setup =
{
    .proc_1 = NULL,
    .proc_2 = NULL
};

static singleton_run run_setup =
{
    .common = &common_setup,
    .block1 = &block1_setup,
    .block2 = &block2_setup,
    .block3 = &block3_setup,
    .block4 = &block4_setup
};

static singleton_handler singleton_setup =
{
    .par     = &par_setup,
    .get_par = &get_par_setup,
    .set_par = &set_par_setup,
    .irq     = &irq_setup,
    .run     = &run_setup
};

singleton_handler *singleton_v2(void){ return &singleton_setup;}

