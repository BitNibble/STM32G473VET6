#include "ds3231_rtc.h"

/* --- Helper Utilities --- */
static uint8_t bcd_to_dec(uint8_t val) { return ((val / 16) * 10) + (val % 16); }
static uint8_t dec_to_bcd(uint8_t val) { return ((val / 10) * 16) + (val % 10); }

/* --- GET Implementations --- */
static uint8_t get_hours(instance_par* par)     { return par->hours; }
static uint8_t get_minutes(instance_par* par)   { return par->minutes; }
static uint8_t get_seconds(instance_par* par)   { return par->seconds; }
static float get_temperature(instance_par* par) { return par->temperature; }

/* --- SET Implementations --- */
static void set_hours(instance_par* par, uint8_t val)   { par->hours = val; }
static void set_minutes(instance_par* par, uint8_t val) { par->minutes = val; }
static void set_seconds(instance_par* par, uint8_t val) { par->seconds = val; }

/* --- V-TABLE (RUN) Implementations --- */
static void run_config(instance_par* self, instance_par par)
{
    if (self == NULL) return;
    self->device_ID = par.device_ID;
    self->i2c = par.i2c;
    self->hours = par.hours;
    self->minutes = par.minutes;
    self->seconds = par.seconds;
}

static int8_t run_get_time(instance_par* par)
{
    if (par == NULL || par->i2c == NULL) return -1;
    
    uint8_t raw_buf[7] = {0};
    /* Using your memory layout interface seamlessly via dependency injection */
    int8_t status = par->i2c->run->memory->read(DS3231_I2C_ADDR, 0x00, raw_buf, 7);
    if (status != 0) return status;
    
    par->seconds      = bcd_to_dec(raw_buf[0] & 0x7FU);
    par->minutes      = bcd_to_dec(raw_buf[1] & 0x7FU);
    par->hours        = bcd_to_dec(raw_buf[2] & 0x3FU); /* Assumes 24h mode */
    par->day_of_week  = bcd_to_dec(raw_buf[3] & 0x07U);
    par->day_of_month = bcd_to_dec(raw_buf[4] & 0x3FU);
    par->month        = bcd_to_dec(raw_buf[5] & 0x1FU);
    par->year         = bcd_to_dec(raw_buf[6]) + 2000U;
    
    return 0;
}

static int8_t run_set_time(instance_par* par)
{
    if (par == NULL || par->i2c == NULL) return -1;
    
    uint8_t raw_buf[7];
    raw_buf[0] = dec_to_bcd(par->seconds);
    raw_buf[1] = dec_to_bcd(par->minutes);
    raw_buf[2] = dec_to_bcd(par->hours); /* 24h mode format */
    raw_buf[3] = dec_to_bcd(par->day_of_week);
    raw_buf[4] = dec_to_bcd(par->day_of_month);
    raw_buf[5] = dec_to_bcd(par->month);
    raw_buf[6] = dec_to_bcd((uint8_t)(par->year - 2000U));
    
    return par->i2c->run->memory->write(par->device_ID, 0x00, raw_buf, 7);
}

static int8_t run_get_temp(instance_par* par)
{
    if (par == NULL || par->i2c == NULL) return -1;
    
    uint8_t raw_buf[2] = {0};
    int8_t status = par->i2c->run->memory->read(par->device_ID, 0x11, raw_buf, 2);
    if (status != 0) return status;
    
    par->temperature = (float)((int8_t)raw_buf[0]) + ((float)(raw_buf[1] >> 6) * 0.25f);
    return 0;
}

/* --- Shared Constant Sub-structures --- */
static instance_get_par rtc_get = {
    .hours       = get_hours,
    .minutes     = get_minutes,
    .seconds     = get_seconds,
    .temperature = get_temperature
};

static instance_set_par rtc_set = {
    .hours   = set_hours,
    .minutes = set_minutes,
    .seconds = set_seconds
};

static instance_run rtc_run = {
    .config   = run_config,
    .get_time = run_get_time,
    .set_time = run_set_time,
    .get_temp = run_get_temp
};

/*** INSTANCE INITIALIZE ***/
instance_handler ds3231_enable(instance_par par)
{
    instance_handler handler;
    
    /* Copy incoming parameters (including injected i2c handle) into the local instance state */
    handler.par = par;
    
    /* Bind interface tables to this runtime handle */
    handler.get_par = &rtc_get;
    handler.set_par = &rtc_set;
    handler.run     = &rtc_run;
    
    /* Clear callbacks by default */
    handler.irq.alarm_triggered = NULL;
    
    return handler;
}

