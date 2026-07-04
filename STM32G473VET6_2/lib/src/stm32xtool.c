/*****************************************
	STM32 TOOL
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
Update:   15/11/2025
*****************************************/
#include "stm32xtool.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

/*** Define and Macro ***/
#define FTDELAY_SIZE 256
#define TOGGLE_SIZE 16
static unsigned int ft_Delay_Lock[FTDELAY_SIZE + ONE] = {0};
static volatile unsigned int ftCounter[FTDELAY_SIZE + ONE] = {0};
static volatile uint8_t toggle_flag[TOGGLE_SIZE + ONE] = {0};
/*** Local ***/
uint32_t _size_to_block(uint32_t size_block);
uint32_t _block_to_size(uint32_t block);
uint32_t _block_mask(uint32_t size_block, uint32_t Pos);
uint32_t _mask_pos(uint32_t Msk);
uint32_t _mask_data(uint32_t Msk, uint32_t data);

/*** Helpers ***/
inline uint32_t _block_pos(uint32_t size_block, uint32_t block_n){
	return size_block * block_n;
}
inline uint32_t _mask(uint32_t var, uint32_t Msk){
	return (var & Msk);
}
inline uint32_t _imask(uint32_t var, uint32_t Msk){
	return (var & ~Msk);
}
inline uint32_t _size_to_block(uint32_t size_block){
	return (size_block >= DWORD_BITS) ? 0xFFFFFFFFU : ((1U << size_block) - 1);
}
inline uint32_t _block_to_size(uint32_t block) {
    return block ? ((unsigned int)DWORD_BITS - __builtin_clz(block)) : 0U;
}
inline uint32_t _block_mask(uint32_t size_block, uint32_t Pos){
	return _size_to_block(size_block) << Pos;
}
inline uint32_t _mask_pos(uint32_t Msk){
	return Msk ? (unsigned int)__builtin_ctz(Msk) : 0U;
}
inline uint32_t _mask_data(uint32_t Msk, uint32_t data){
	return _mask(data << _mask_pos(Msk), Msk);
}

/*** Tools ***/
void set_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg |= hbits;
}
void clear_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg &= ~hbits;
}

/*** ToolSet ***/
// field
inline uint32_t get_field_value(uint32_t reg, uint32_t Msk, uint32_t Pos)
{
	return _mask(Msk , reg) >> Pos;
}
inline void write_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data)
{
	uint32_t tmp = *reg;
	*reg = _imask(tmp, Msk) | _mask((data << Pos), Msk);
}
inline void set_field_value(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data)
{
	clear_reg(reg, Msk); set_reg(reg, _mask((data << Pos), Msk));
}
inline void set_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedData)
{
	uint32_t tmp = *reg;
	*reg = _imask(tmp, Msk) | _mask(ShiftedData, Msk);
}
// block
uint32_t get_block_value(uint32_t reg, uint8_t size_block, uint8_t Pos)
{
	return get_field_value(reg, _block_mask(size_block, Pos), Pos);
}
void write_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	write_field_value(reg, _block_mask(size_block, Pos), Pos, data);
}
void set_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	set_field_value(reg, _block_mask(size_block, Pos), Pos, data);
}
// bit_block
uint32_t get_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos)
{
	uint32_t n = Pos / DWORD_BITS; Pos = Pos % DWORD_BITS;
	return get_field_value(*(reg + n), _block_mask(size_block, Pos), Pos);
}
void write_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	uint32_t n = Pos / DWORD_BITS; Pos = Pos % DWORD_BITS;
	write_field_value((reg + n), _block_mask(size_block, Pos), Pos, data);
}
void set_bit_block_value(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	uint32_t n = Pos / DWORD_BITS; Pos = Pos % DWORD_BITS;
	set_field_value((reg + n), _block_mask(size_block, Pos), Pos, data);
}

/****************************************/
inline uint8_t toggle(uint8_t n) {
	if (n < TOGGLE_SIZE){
		uint8_t mask = ONE;
		toggle_flag[n] &= mask;
		toggle_flag[n] ^= mask;
		return toggle_flag[n];
	} else {
		return ZERO;
	}
}
/*** NULL Check ***/
int isPtrNull(void* ptr) {
    return ptr ? 0 : 1; // Returns 1 if NULL, 0 otherwise
}
int isCharPtrFlush(void* ptr) {
	if (ptr == NULL) return 1;
    // Cast the void pointer to a char pointer to dereference it
    return *((unsigned char*)ptr) ? 0 : 1; // Returns 1 if '\0', 0 otherwise
}

/*** ADC ***/
float CalculateTemperature(uint16_t adc_value) {
    const float V_25 = 0.76f;  // Voltage at 25°C (in volts)
    const float Avg_slope = 0.0025f;  // Average slope (in volts/°C)
    const float V_ref = 3.3f;  // Reference voltage, typically 3.0V or 3.3V

    float V_sense = ((float)adc_value / 4095.0) * V_ref;
    return ((V_sense - V_25) / Avg_slope) + 25.0f;
}

/*** Fall Threw Delay ***/
int ftdelayCycles(uint8_t lock_ID, unsigned int n_cycle, void (*execute)(void)) {
    int ret = 0;
    if (lock_ID > FTDELAY_SIZE) return 0; // safety check

    if (ft_Delay_Lock[lock_ID] != lock_ID) {
        ft_Delay_Lock[lock_ID] = lock_ID;
        ftCounter[lock_ID] = (n_cycle > 0U) ? (n_cycle - 1U) : 0;
        if(execute){ execute (); }
    } else {
        if (ftCounter[lock_ID] > 0U) {
        	ftCounter[lock_ID]--;
            // still counting down, do nothing
        } else {
            ft_Delay_Lock[lock_ID] = 0U;
            ret = 1; // delay expired
        }
    }
    return ret;
}

void ftdelayReset(uint8_t ID) {
    if (ID > FTDELAY_SIZE) return; // safety check
    ft_Delay_Lock[ID] = 0U;
    ftCounter[ID] = 0U;
}

/*** EOF ***/

