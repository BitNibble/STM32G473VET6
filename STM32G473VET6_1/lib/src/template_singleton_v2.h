#ifndef TEMPLATE_SINGLETON_V2_H
	#define TEMPLATE_SINGLETON_V2_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct
{
    uint8_t var_1;
    uint8_t var_2;

} singleton_par;

typedef const struct
{
    uint8_t (*var_1)(void);
    uint8_t (*var_2)(void);

} singleton_get_par;

typedef const struct
{
    void (*var_1)(uint8_t value);
    void (*var_2)(uint8_t value);

} singleton_set_par;

typedef struct
{
    void (*callback_1)(void);
    void (*callback_2)(void);

} singleton_irq;

typedef const struct
{
    void (*init)(const singleton_par *par);
    void (*enable)(void);
    void (*disable)(void);
    void (*reset)(void);

} singleton_common;

typedef const struct
{
    void (*proc_1)(void);
    void (*proc_2)(void);
    void (*func_1)(uint32_t value);
    void (*func_2)(uint32_t value1,uint32_t value2);

} singleton_block1;

typedef const struct
{
    void (*proc_1)(void);
    void (*proc_2)(void);

} singleton_block2;

typedef const struct
{
    void (*proc_1)(void);
    void (*proc_2)(void);

} singleton_block3;

typedef const struct
{
    void (*proc_1)(void);
    void (*proc_2)(void);

} singleton_block4;

typedef const struct
{
    const singleton_common *common;
    const singleton_block1 *block1;
    const singleton_block2 *block2;
    const singleton_block3 *block3;
    const singleton_block4 *block4;

} singleton_run;

typedef const struct
{
    singleton_par *par;
    singleton_get_par *get_par;
    singleton_set_par *set_par;
    singleton_irq *irq;
    const singleton_run *run;

} singleton_handler;

singleton_handler *singleton_v2(void);

#endif

