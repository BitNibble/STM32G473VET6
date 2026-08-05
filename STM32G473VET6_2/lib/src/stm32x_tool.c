/*****************************************
    stm32x_tool.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
*****************************************/
#include "stm32x_tool.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

/*** Define and Macro ***/
#define FTDELAY_SIZE 256
#define TOGGLE_SIZE 16

static unsigned int ft_Delay_Lock[FTDELAY_SIZE] = {0};
static volatile unsigned int ftCounter[FTDELAY_SIZE] = {0};
static volatile uint8_t toggle_flag[TOGGLE_SIZE] = {0};

/*** Local Forward Declarations ***/
static uint32_t _size_to_block(uint32_t size_block);
static uint32_t _block_to_size(uint32_t block);
static uint32_t _block_mask(uint32_t size_block, uint32_t Pos);
static uint32_t _mask_pos(uint32_t Msk);
static uint32_t _mask_data(uint32_t Msk, uint32_t data);

static uint32_t get_field_value(uint32_t reg, uint32_t Msk, uint32_t Pos);
static void write_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data);
static void write_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData);
static uint32_t get_block_value(uint32_t reg, uint8_t size_block, uint8_t Pos);
static void write_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);
static uint32_t get_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos);
static void write_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data);

static void increment(uint16_t* value, uint16_t min, uint16_t max);
static uint8_t toggle(uint8_t n);
static int isPtrNull(const void* ptr);
static int isCharPtrFlush(const void* ptr);
static float calculate_temperature(uint16_t adc_value);
static int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*init)(void), void (*term)(void));
static void ftdelayReset(uint8_t ID);
static void ftdelayTerm(uint8_t ID);

/*** Helpers ***/
static inline uint32_t _block_pos(uint32_t size_block, uint32_t block_n){
    return size_block * block_n;
}
static inline uint32_t _mask(uint32_t var, uint32_t Msk){
    return (var & Msk);
}
static inline uint32_t _set_bit(uint32_t var, uint32_t Msk){
    return (var | Msk);
}
static inline uint32_t _clear_bit(uint32_t var, uint32_t Msk){
    return (var & ~Msk);
}
static inline uint32_t _size_to_block(uint32_t size_block){
    // Pure bitmath trick avoiding conditional branches for max compiler speed
    return (size_block >= DWORD_BITS) ? 0xFFFFFFFFU : ((1U << (size_block & 31U)) - 1U);
}
static inline uint32_t _block_to_size(uint32_t block) {
    return block ? ((unsigned int)DWORD_BITS - (unsigned int)__builtin_clz(block)) : 0U;
}
static inline uint32_t _block_mask(uint32_t size_block, uint32_t Pos){
    return _size_to_block(size_block) << (Pos & 31U);
}
static inline uint32_t _mask_pos(uint32_t Msk){
    return Msk ? (unsigned int)__builtin_ctz(Msk) : 0U;
}
static inline uint32_t _mask_data(uint32_t Msk, uint32_t data){
    return _mask(data << _mask_pos(Msk), Msk);
}

/*** ToolSet Engines ***/
// field
static uint32_t get_field_value(uint32_t reg, uint32_t Msk, uint32_t Pos)
{
    return _mask(Msk, reg) >> Pos;
}
static void write_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data)
{
    uint32_t tmp = *reg;
    tmp = _clear_bit(tmp, Msk) | _mask((data << Pos), Msk);
    *reg = tmp;
}
static void write_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData)
{
    uint32_t tmp = *reg;
    tmp = _clear_bit(tmp, Msk) | _mask(ShiftedData, Msk);
    *reg = tmp;
}
// block
static uint32_t get_block_value(uint32_t reg, uint8_t size_block, uint8_t Pos)
{
    return get_field_value(reg, _block_mask(size_block, Pos), Pos);
}
static void write_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
    write_field_value(reg, _block_mask(size_block, Pos), Pos, data);
}
// bit_block
static uint32_t get_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos)
{
    uint32_t n = Pos / DWORD_BITS;
    Pos = Pos % DWORD_BITS;
    return get_field_value(*(reg + n), _block_mask(size_block, Pos), Pos);
}
static void write_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data) {
    uint32_t n = Pos / DWORD_BITS;
    Pos = Pos % DWORD_BITS;

    write_field_value((reg + n), _block_mask(size_block, Pos), Pos, data);
}
void write_bit_block_value_v2(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data) {
    uint32_t n = Pos / DWORD_BITS;
    Pos = Pos % DWORD_BITS;

    // Check if the bit block spills over into the next 32-bit register boundary
    if ((Pos + size_block) > DWORD_BITS) {
        uint8_t first_part_size = (uint8_t)(DWORD_BITS - Pos);
        uint8_t second_part_size = (uint8_t)(size_block - first_part_size);

        // 1. Write the lower fragment to the first register
        uint32_t first_mask = _block_mask(first_part_size, Pos);
        write_field_value((reg + n), first_mask, Pos, data);

        // 2. Write the upper fragment to the subsequent register (offset n + 1)
        uint32_t second_mask = _block_mask(second_part_size, 0);
        write_field_value((reg + n + 1), second_mask, 0, (data >> first_part_size));
    }
    else {
        // Normal case: The entire block perfectly fits inside a single 32-bit space
        write_field_value((reg + n), _block_mask(size_block, Pos), Pos, data);
    }
}

/****************************************/
static void increment(uint16_t* value, uint16_t min, uint16_t max) {
    *value += 1;
    if(*value > max || *value < min){ *value = min; }
}

static uint8_t toggle(uint8_t n) {
    if (n < TOGGLE_SIZE) {
        // Safe explicit cast to match volatile uint8_t array operations
        toggle_flag[n] &= (uint8_t)ONE;
        toggle_flag[n] ^= (uint8_t)ONE;
        return toggle_flag[n];
    } else {
        return (uint8_t)ZERO;
    }
}

/*** NULL Check ***/
static int isPtrNull(const void* ptr) {
    return ptr ? 0 : 1;
}
static int isCharPtrFlush(const void* ptr) {
    if (ptr == NULL) return 1;
    return *((const unsigned char*)ptr) ? 0 : 1;
}

/*** ADC ***/
static float calculate_temperature(uint16_t adc_value) {
    const float V_25 = 0.76f;         // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;         // Reference voltage

    float V_sense = ((float)adc_value / 4095.0f) * V_ref;
    return ((V_sense - V_25) / Avg_slope) + 25.0f;
}

/*** Fall Through Delay ***/
static int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*init)(void), void (*term)(void)) {
    int ret = 0;
    if (lock_ID >= FTDELAY_SIZE) return ZERO;

    if (ft_Delay_Lock[lock_ID] != (lock_ID + ONE)) {
        ft_Delay_Lock[lock_ID] = (lock_ID + ONE);
        ftCounter[lock_ID] = (n_cycle > 0U) ? (n_cycle - 1U) : 0;
        if(init){ init(); }
    } else {
        if (ftCounter[lock_ID] > 0U) {
            ftCounter[lock_ID]--;
        } else {
            if(term){ term(); }
            ret = 1; // delay expired
        }
    }
    return ret;
}

static void ftdelayReset(uint8_t ID) {
    if (ID >= FTDELAY_SIZE) return;
    ft_Delay_Lock[ID] = 0U;
}

static void ftdelayTerm(uint8_t ID) {
    if (ID >= FTDELAY_SIZE) return;
    ft_Delay_Lock[ID] = (ID + ONE);
    ftCounter[ID] = 0;
}

/*** SINGLETON INSTANTIATION (Marked const to reside safely in Flash memory) ***/
static const tool_handler tool_setup = {
    ._block_pos = _block_pos,
    ._mask = _mask,
	._set_bit = _set_bit,
    ._clear_bit = _clear_bit,

    .get_field_value = get_field_value,
    .write_field_value = write_field_value,
    .write_field_encoded = write_field_encoded,

    .get_block_value = get_block_value,
    .write_block_value = write_block_value,

    .get_bit_block_value = get_bit_block_value,
    .write_bit_block_value = write_bit_block_value,
    /****************************************/
    .increment = increment,
    .toggle = toggle,
    /*** NULL Check ***/
    .isPtrNull = isPtrNull,
    .isCharPtrFlush = isCharPtrFlush,
    /*** ADC ***/
    .calculate_temperature = calculate_temperature,
    /*** Fall Through Delay ***/
    .ftdelayCycles = ftdelayCycles,
    .ftdelayReset = ftdelayReset,
    .ftdelayTerm = ftdelayTerm,
};

/*** SINGLETON ACCESSOR FUNCTION ***/
tool_handler* exe(void) {
    return (tool_handler*)&tool_setup;
}

/*** EOF ***/

