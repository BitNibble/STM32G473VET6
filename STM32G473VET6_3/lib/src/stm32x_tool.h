/***************************************************
    stm32x_tool.h
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
****************************************************/
#pragma once

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*** Define & Macro Constants ***/
#define ZERO 0
#define ONE 1UL
#define TWO 2UL
#define NIBBLE_BITS 4UL
#define BYTE_BITS 8UL
#define WORD_BITS 16UL
#define DWORD_BITS 32UL
#define QWORD_BITS 64UL

#ifndef SET_BIT
    #define SET_BIT(REG, BIT)                    ((REG) |= (BIT))
#endif
#ifndef CLEAR_BIT
    #define CLEAR_BIT(REG, BIT)                  ((REG) &= ~(BIT))
#endif
#ifndef READ_BIT
    #define READ_BIT(REG, BIT)                   ((REG) & (BIT))
#endif
#ifndef CLEAR_REG
    #define CLEAR_REG(REG)                       ((REG) = (0x0))
#endif
#ifndef WRITE_REG
    #define WRITE_REG(REG, VAL)                  ((REG) = (VAL))
#endif
#ifndef READ_REG
    #define READ_REG(REG)                        ((REG))
#endif
#ifndef MODIFY_REG
    #define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#endif
#ifndef POSITION_VAL
    #define POSITION_VAL(VAL)                    (__CLZ(__RBIT(VAL)))
#endif

/*** TOOL HANDLER STRUCT ***/
// Removed 'const' qualifier from the type definition so that the .c file can instantiate it cleanly.
typedef const struct {
    uint32_t (*_block_pos)(uint32_t size_block, uint32_t block_n);
    uint32_t (*_mask)(uint32_t var, uint32_t Msk);
    uint32_t (*_set_bit)(uint32_t var, uint32_t Msk);
    uint32_t (*_clear_bit)(uint32_t var, uint32_t Msk);

    uint32_t (*get_field_value)(uint32_t reg, uint32_t Msk, uint32_t Pos);
    void (*write_field_value)(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
    void (*write_field_encoded)(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData);

    uint32_t (*get_block_value)(uint32_t reg, uint8_t size_block, uint8_t Pos);
    void (*write_block_value)(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);

    uint32_t (*get_bit_block_value)(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos);
    void (*write_bit_block_value)(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
    /****************************************/
    void (*increment)(uint16_t* value, uint16_t min, uint16_t max);
    uint8_t (*toggle)(uint8_t n);
    /*** NULL Check ***/
    int (*isPtrNull)(const void* ptr);
    int (*isCharPtrFlush)(const void* ptr);
    /*** ADC ***/
    float (*calculate_temperature)(uint16_t adc_value);
    /*** Fall Threw Delay ***/
    int (*ftdelayCycles)(uint8_t lock_ID, unsigned int n_cycle, void (*init)(void), void (*term)(void));
    void (*ftdelayReset)(uint8_t ID);
    void (*ftdelayTerm)(uint8_t ID);
} tool_handler;

/*** TOOL ACCESSOR FUNCTION ***/
tool_handler* exe(void);

// ============================================================================
// WRAPPER MACROS (Cleans up calling syntax completely)
// ============================================================================
#define WRITE_FIELD(REG, Msk, Pos, Data)    exe()->write_field_value(&(REG), (Msk), (Pos), (Data))
#define WRITE_ENCODED(REG, Msk, Shifted)    exe()->write_field_encoded(&(REG), (Msk), (Shifted))
#define WRITE_BLOCK(REG, Size, Pos, Data)   exe()->write_block_value(&(REG), (Size), (Pos), (Data))
#define WRITE_BIT_BLOCK(REG, Size, Pos, Data) exe()->write_bit_block_value(&(REG), (Size), (Pos), (Data))

#define GET_FIELD(REG, Msk, Pos)            exe()->get_field_value((REG), (Msk), (Pos))
#define GET_BLOCK(REG, Size, Pos)           exe()->get_block_value((REG), (Size), (Pos))
#define GET_BIT_BLOCK(REG, Size, Pos)       exe()->get_bit_block_value(&(REG), (Size), (Pos))

/*** EOF ***/

