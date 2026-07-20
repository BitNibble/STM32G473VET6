// i2c_bitfield.h - Using "par" for bitfield access
#ifndef I2C_BITFIELD_H
#define I2C_BITFIELD_H

#include <stdint.h>

// Individual register bitfield definitions
typedef union {
    volatile uint32_t reg;    // Raw register access
    struct {
        volatile uint32_t PE          : 1;
        volatile uint32_t TXIE        : 1;
        volatile uint32_t RXIE        : 1;
        volatile uint32_t ADDRIE      : 1;
        volatile uint32_t NACKIE      : 1;
        volatile uint32_t STOPIE      : 1;
        volatile uint32_t TC_IE       : 1;
        volatile uint32_t ERRIE       : 1;
        volatile uint32_t DNF         : 4;
        volatile uint32_t ANFOFF      : 1;
        volatile uint32_t             : 1;
        volatile uint32_t TXDMAEN     : 1;
        volatile uint32_t RXDMAEN     : 1;
        volatile uint32_t SBC         : 1;
        volatile uint32_t NOSTRETCH   : 1;
        volatile uint32_t GCEN        : 1;
        volatile uint32_t SMBHEN      : 1;
        volatile uint32_t SMBDEN      : 1;
        volatile uint32_t ALERTEN     : 1;
        volatile uint32_t PECEN       : 1;
        volatile uint32_t             : 8;
    } par;  // ← Parameter/bitfield access
} I2C_CR1_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t SADD        : 10;
        volatile uint32_t             : 6;
        volatile uint32_t RD_WRN      : 1;
        volatile uint32_t NBYTES      : 8;
        volatile uint32_t NACK        : 1;
        volatile uint32_t STOP        : 1;
        volatile uint32_t START       : 1;
        volatile uint32_t HEADR       : 1;
        volatile uint32_t AUTOEND     : 1;
        volatile uint32_t RELOAD      : 1;
        volatile uint32_t             : 1;
    } par;
} I2C_CR2_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t OA1         : 10;
        volatile uint32_t             : 6;
        volatile uint32_t OA1MODE     : 1;
        volatile uint32_t OA1EN       : 1;
        volatile uint32_t             : 14;
    } par;
} I2C_OAR1_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t OA2         : 7;
        volatile uint32_t             : 1;
        volatile uint32_t OA2MSK      : 3;
        volatile uint32_t             : 4;
        volatile uint32_t OA2EN       : 1;
        volatile uint32_t             : 16;
    } par;
} I2C_OAR2_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t SCLH        : 8;
        volatile uint32_t SCLL        : 8;
        volatile uint32_t SDADEL      : 4;
        volatile uint32_t SCLDEL      : 4;
        volatile uint32_t             : 4;
        volatile uint32_t PRESC       : 4;
    } par;
} I2C_TIMINGR_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t TXE          : 1;
        volatile uint32_t TXIS         : 1;
        volatile uint32_t RXNE         : 1;
        volatile uint32_t ADDR         : 1;
        volatile uint32_t NACKF        : 1;
        volatile uint32_t STOPF        : 1;
        volatile uint32_t TC           : 1;
        volatile uint32_t TCR          : 1;
        volatile uint32_t BUSY         : 1;
        volatile uint32_t DIR          : 1;
        volatile uint32_t ADDCODE      : 7;
        volatile uint32_t              : 1;
        volatile uint32_t              : 14;
    } par;
} I2C_ISR_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t ADDRCF      : 1;
        volatile uint32_t NACKCF      : 1;
        volatile uint32_t STOPCF      : 1;
        volatile uint32_t BERRCF      : 1;
        volatile uint32_t ARLOCF      : 1;
        volatile uint32_t OVRCF       : 1;
        volatile uint32_t PECCF       : 1;
        volatile uint32_t              : 1;
        volatile uint32_t              : 24;
    } par;
} I2C_ICR_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t RXDATA      : 8;
        volatile uint32_t              : 24;
    } par;
} I2C_RXDR_t;

typedef union {
    volatile uint32_t reg;
    struct {
        volatile uint32_t TXDATA      : 8;
        volatile uint32_t              : 24;
    } par;
} I2C_TXDR_t;

// Complete I2C peripheral structure with correct offsets
typedef struct {
    I2C_CR1_t     CR1;      // 0x00
    I2C_CR2_t     CR2;      // 0x04
    I2C_OAR1_t    OAR1;     // 0x08
    I2C_OAR2_t    OAR2;     // 0x0C
    volatile uint32_t RESERVED1; // 0x10 (TIMINGR is at 0x10)
    I2C_TIMINGR_t TIMINGR;  // 0x10
    volatile uint32_t RESERVED2; // 0x14
    I2C_ISR_t     ISR;      // 0x18
    I2C_ICR_t     ICR;      // 0x1C
    I2C_RXDR_t    RXDR;     // 0x20
    I2C_TXDR_t    TXDR;     // 0x24
} I2C_Regs_Bitfield_t;

// Macro to cast CMSIS I2C_TypeDef to bitfield version
#define I2C_BF(i2c)   ((I2C_Regs_Bitfield_t*)(i2c))

#endif // I2C_BITFIELD_H
