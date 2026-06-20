#ifndef TIM1_DRIVER_H
#define TIM1_DRIVER_H

#include "stm32g473vet6.h"

typedef struct {
    void (*b)(void);   void (*u)(void);   void (*t)(void);
    void (*cc1)(void); void (*cc2)(void); void (*cc3)(void); void (*cc4)(void);
} tim1_callback;

typedef const struct {
    void (*init)(uint16_t prescaler, uint32_t autoreload);
    void (*clock_enable)(void);
    void (*clock_disable)(void);
    void (*nvic_u_enable)(uint8_t priority);
    void (*nvic_u_disable)(void);
    void (*nvic_t_enable)(uint8_t priority);
    void (*start)(void);
    void (*stop)(void);
    tim1_callback* callback;
} TIM1_Handler;

TIM1_Handler* tim1(void);

#endif
