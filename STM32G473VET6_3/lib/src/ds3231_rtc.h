#ifndef DS3231_RTC_H
#define DS3231_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/*** LIBRARY ***/
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include "stm32gxxx_i2c1.h" /* Dependency for your low-level I2C block */

#define DS3231_I2C_ADDR             0x68U

/*** INSTANCE PARAMETER ***/
typedef struct {
	uint8_t device_ID;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t day_of_month;
    uint8_t month;
    uint16_t year;
    float temperature;
    
    /* Low-level connection dependency injection */
    i2c1_handler *i2c; 
} instance_par;

/*** INSTANCE GET PARAMETER ***/
typedef const struct {
    uint8_t (*hours)(instance_par* par);
    uint8_t (*minutes)(instance_par* par);
    uint8_t (*seconds)(instance_par* par);
    float (*temperature)(instance_par* par);
} instance_get_par;

/*** INSTANCE SET PARAMETER ***/
typedef const struct {
    void (*hours)(instance_par* par, uint8_t val);
    void (*minutes)(instance_par* par, uint8_t val);
    void (*seconds)(instance_par* par, uint8_t val);
} instance_set_par;

/*** INSTANCE V-TABLE ***/
typedef const struct {
    void (*config)(instance_par* self, instance_par par);
    int8_t (*get_time)(instance_par* par);
    int8_t (*set_time)(instance_par* par);
    int8_t (*get_temp)(instance_par* par);
} instance_run;

/*** INSTANCE CALLBACK ***/
typedef struct {
    void (*alarm_triggered)(void);
} instance_irq;

/*** INSTANCE HANDLER ***/
typedef struct {
    instance_par par;
    instance_get_par* get_par;
    instance_set_par* set_par;
    instance_irq irq;
    instance_run* run;
} instance_handler;

/*** INSTANCE INITIALIZE ***/
instance_handler ds3231_enable(instance_par par);

#ifdef __cplusplus
}
#endif

#endif
