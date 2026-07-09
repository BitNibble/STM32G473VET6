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
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t day_of_month;
    uint8_t month;
    uint16_t year;
    float temperature;
    
    uint8_t device_ID;
    i2c1_handler *i2c; 
} instance_par;

/*** INSTANCE V-TABLE ***/
typedef const struct {
    int8_t (*get_time)(instance_par* par);
    int8_t (*set_time)(instance_par* par);
    int8_t (*get_temp)(instance_par* par);
} instance_run;

/*** INSTANCE HANDLER ***/
typedef struct {
    instance_par par;
    instance_run* run;
} instance_handler;

/*** INSTANCE INITIALIZE ***/
instance_handler ds3231_enable(void);

#ifdef __cplusplus
}
#endif

#endif
