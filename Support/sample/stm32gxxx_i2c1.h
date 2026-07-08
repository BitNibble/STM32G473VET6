#ifndef STM32GXXX_I2C1_H
#define STM32GXXX_I2C1_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g473vet6.h"
#include "stm32xtool.h"

#define I2C1_ADDR_7BIT             0U
#define I2C1_ADDR_10BIT            1U

#define I2C1_FILTER_DISABLE        0U
#define I2C1_FILTER_ENABLE         1U

typedef struct
{
    /* Configuration */

    uint32_t timing;
    uint16_t own_address;
    uint8_t addressing_mode;
    uint8_t analog_filter;
    uint8_t digital_filter;
    volatile uint32_t status;

} i2c1_par;

typedef const struct
{
    uint8_t (*busy)(void);
    uint8_t (*ready)(void);
    uint8_t (*enabled)(void);
    uint8_t (*error)(void);

} i2c1_get_par;

typedef const struct
{
    void (*timing)(uint32_t);
    void (*own_address)(uint16_t);
    void (*addressing_mode)(uint8_t);
    void (*analog_filter)(uint8_t);
    void (*digital_filter)(uint8_t);

} i2c1_set_par;

typedef struct
{
    void (*tx_complete)(void);
    void (*rx_complete)(void);
    void (*listen)(void);
    void (*error)(void);

} i2c1_irq;

typedef const struct
{
    void (*config)(const i2c1_par *par);
    void (*init)(void);
    void (*enable)(void);
    void (*disable)(void);
    void (*reset)(void);
    void (*irq_event)(void);
    void (*irq_error)(void);

} i2c1_common;

typedef const struct
{
	int8_t (*write_byte)(uint16_t address,uint8_t data);
	int8_t (*read_byte)(uint16_t address,uint8_t *data);
	int8_t (*write)(uint16_t address,const uint8_t *buffer,uint16_t length);
	int8_t (*read)(uint16_t address,uint8_t *buffer,uint16_t length);
	int8_t (*probe)(uint16_t address);
	int8_t (*scan)(uint8_t *list,uint16_t *count);

} i2c1_master;

typedef const struct
{
    int8_t (*write)(uint16_t address,uint16_t reg,const uint8_t *buffer,uint16_t length);
    int8_t (*read)(uint16_t address,uint16_t reg,uint8_t *buffer,uint16_t length);

} i2c1_memory;

typedef const struct
{
    void (*enable)(void);
    void (*disable)(void);
    void (*listen)(void);

} i2c1_slave;

typedef const struct
{
    int8_t (*write)(uint16_t address,const uint8_t *buffer,uint16_t length);
    int8_t (*read)(uint16_t address,uint8_t *buffer,uint16_t length);

} i2c1_dma;

typedef const struct
{
    const i2c1_common *common;
    const i2c1_master *master;
    const i2c1_memory *memory;
    const i2c1_slave *slave;
    const i2c1_dma *dma;

} i2c1_run;

typedef const struct
{
    i2c1_par *par;
    i2c1_get_par *get_par;
    i2c1_set_par *set_par;
    i2c1_irq *irq;
    const i2c1_run *run;

} i2c1_handler;

i2c1_handler *i2c1(void);

#ifdef __cplusplus
}
#endif

#endif
