//=============================================================================
// i2c_bitfield.h
// STM32G473VET6 I2C Bitfield Definitions
//=============================================================================

#ifndef I2C_BITFIELD_H
	#define I2C_BITFIELD_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

//=============================================================================
// CR1 - Control Register 1
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t PE          : 1;   // Bit 0
        uint32_t TXIE        : 1;   // Bit 1
        uint32_t RXIE        : 1;   // Bit 2
        uint32_t ADDRIE      : 1;   // Bit 3
        uint32_t NACKIE      : 1;   // Bit 4
        uint32_t STOPIE      : 1;   // Bit 5
        uint32_t TCIE        : 1;   // Bit 6
        uint32_t ERRIE       : 1;   // Bit 7
        uint32_t DNF         : 4;   // Bits 8-11
        uint32_t ANFOFF      : 1;   // Bit 12
        uint32_t SWRST       : 1;   // Bit 13
        uint32_t TXDMAEN     : 1;   // Bit 14
        uint32_t RXDMAEN     : 1;   // Bit 15
        uint32_t SBC         : 1;   // Bit 16
        uint32_t NOSTRETCH   : 1;   // Bit 17
        uint32_t WUPEN       : 1;   // Bit 18
        uint32_t GCEN        : 1;   // Bit 19
        uint32_t SMBHEN      : 1;   // Bit 20
        uint32_t SMBDEN      : 1;   // Bit 21
        uint32_t ALERTEN     : 1;   // Bit 22
        uint32_t PECEN       : 1;   // Bit 23
        uint32_t RESERVED    : 8;   // Bits 24-31

    } par;

} I2C_CR1_t;

//=============================================================================
// CR2 - Control Register 2
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t SADD        :10;   // Bits 0-9
        uint32_t RD_WRN      : 1;   // Bit 10
        uint32_t ADD10       : 1;   // Bit 11
        uint32_t HEAD10R     : 1;   // Bit 12
        uint32_t START       : 1;   // Bit 13
        uint32_t STOP        : 1;   // Bit 14
        uint32_t NACK        : 1;   // Bit 15
        uint32_t NBYTES      : 8;   // Bits 16-23
        uint32_t RELOAD      : 1;   // Bit 24
        uint32_t AUTOEND     : 1;   // Bit 25
        uint32_t PECBYTE     : 1;   // Bit 26
        uint32_t RESERVED    : 5;   // Bits 27-31

    } par;

} I2C_CR2_t;

//=============================================================================
// OAR1 - Own Address Register 1
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t OA1         :10;   // Bits 0-9
        uint32_t OA1MODE     : 1;   // Bit 10
        uint32_t RESERVED0   : 4;   // Bits 11-14
        uint32_t OA1EN       : 1;   // Bit 15
        uint32_t RESERVED1   :16;   // Bits 16-31

    } par;

} I2C_OAR1_t;

//=============================================================================
// OAR2 - Own Address Register 2
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t RESERVED0   : 1;   // Bit 0
        uint32_t OA2         : 7;   // Bits 1-7
        uint32_t OA2MSK      : 3;   // Bits 8-10
        uint32_t RESERVED1   : 4;   // Bits 11-14
        uint32_t OA2EN       : 1;   // Bit 15
        uint32_t RESERVED2   :16;   // Bits 16-31

    } par;

} I2C_OAR2_t;

//=============================================================================
// TIMINGR - Timing Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t SCLL        : 8;   // Bits 0-7
        uint32_t SCLH        : 8;   // Bits 8-15
        uint32_t SDADEL      : 4;   // Bits 16-19
        uint32_t SCLDEL      : 4;   // Bits 20-23
        uint32_t RESERVED    : 4;   // Bits 24-27
        uint32_t PRESC       : 4;   // Bits 28-31

    } par;

} I2C_TIMINGR_t;

//=============================================================================
// TIMEOUTR - Timeout Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t TIMEOUTA    :12;   // Bits 0-11
        uint32_t TIDLE       : 1;   // Bit 12
        uint32_t RESERVED0   : 2;   // Bits 13-14
        uint32_t TIMOUTEN    : 1;   // Bit 15
        uint32_t TIMEOUTB    :12;   // Bits 16-27
        uint32_t RESERVED1   : 3;   // Bits 28-30
        uint32_t TEXTEN      : 1;   // Bit 31

    } par;

} I2C_TIMEOUTR_t;

//=============================================================================
// ISR - Interrupt & Status Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t TXE         : 1;   // Bit 0
        uint32_t TXIS        : 1;   // Bit 1
        uint32_t RXNE        : 1;   // Bit 2
        uint32_t ADDR        : 1;   // Bit 3
        uint32_t NACKF       : 1;   // Bit 4
        uint32_t STOPF       : 1;   // Bit 5
        uint32_t TC          : 1;   // Bit 6
        uint32_t TCR         : 1;   // Bit 7
        uint32_t BERR        : 1;   // Bit 8
        uint32_t ARLO        : 1;   // Bit 9
        uint32_t OVR         : 1;   // Bit 10
        uint32_t PECERR      : 1;   // Bit 11
        uint32_t TIMEOUT     : 1;   // Bit 12
        uint32_t ALERT       : 1;   // Bit 13
        uint32_t RESERVED0   : 1;   // Bit 14
        uint32_t BUSY        : 1;   // Bit 15
        uint32_t DIR         : 1;   // Bit 16
        uint32_t ADDCODE     : 7;   // Bits 17-23
        uint32_t RESERVED1   : 8;   // Bits 24-31

    } par;

} I2C_ISR_t;

//=============================================================================
// ICR - Interrupt Clear Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t RESERVED0   : 3;   // Bits 0-2
        uint32_t ADDRCF      : 1;   // Bit 3
        uint32_t NACKCF      : 1;   // Bit 4
        uint32_t STOPCF      : 1;   // Bit 5
        uint32_t RESERVED1   : 2;   // Bits 6-7
        uint32_t BERRCF      : 1;   // Bit 8
        uint32_t ARLOCF      : 1;   // Bit 9
        uint32_t OVRCF       : 1;   // Bit 10
        uint32_t PECCF       : 1;   // Bit 11
        uint32_t TIMOUTCF    : 1;   // Bit 12
        uint32_t ALERTCF     : 1;   // Bit 13
        uint32_t RESERVED2   :18;   // Bits 14-31

    } par;

} I2C_ICR_t;

//=============================================================================
// PECR - Packet Error Checking Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t PEC         : 8;   // Bits 0-7
        uint32_t RESERVED    :24;   // Bits 8-31

    } par;

} I2C_PECR_t;

//=============================================================================
// RXDR - Receive Data Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t RXDATA      : 8;   // Bits 0-7
        uint32_t RESERVED    :24;   // Bits 8-31

    } par;

} I2C_RXDR_t;

//=============================================================================
// TXDR - Transmit Data Register
//=============================================================================

typedef union
{
    volatile uint32_t reg;

    volatile struct
    {
        uint32_t TXDATA      : 8;   // Bits 0-7
        uint32_t RESERVED    :24;   // Bits 8-31

    } par;

} I2C_TXDR_t;

//=============================================================================
// Complete I2C Peripheral Register Map
//=============================================================================

typedef struct
{
    I2C_CR1_t          CR1;          // 0x00
    I2C_CR2_t          CR2;          // 0x04
    I2C_OAR1_t         OAR1;         // 0x08
    I2C_OAR2_t         OAR2;         // 0x0C
    I2C_TIMINGR_t      TIMINGR;      // 0x10
    I2C_TIMEOUTR_t     TIMEOUTR;     // 0x14
    I2C_ISR_t          ISR;          // 0x18
    I2C_ICR_t          ICR;          // 0x1C
    I2C_PECR_t         PECR;         // 0x20
    I2C_RXDR_t         RXDR;         // 0x24
    I2C_TXDR_t         TXDR;         // 0x28

} I2C_BitField_TypeDef;

//=============================================================================
// CMSIS Overlay Macro
//=============================================================================

#define I2C_BF(i2c)    ((I2C_BitField_TypeDef *)(i2c))

#endif /* I2C_BITFIELD_H */
