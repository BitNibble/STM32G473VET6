/*****************************************
	STM32 TOOL
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32
Update:   15/11/2025
*****************************************/
#include "stm32xtool.h"
#include <stdarg.h>
#include <math.h>

/*** Define and Macro ***/
#define FTDELAY_SIZE 255
unsigned int ft_Delay_Lock[FTDELAY_SIZE] = {0};
volatile unsigned int ftCounter[FTDELAY_SIZE] = {0};
/*** Local ***/
uint32_t _mask_var(uint32_t var, uint32_t Msk);
uint32_t _imask_var(uint32_t var, uint32_t Msk);
uint32_t _size_to_block(uint32_t size_block);
uint32_t _block_to_size(uint32_t block);
uint32_t _block_mask(uint32_t size_block, uint32_t Pos);
uint32_t _mask_pos(uint32_t Msk);
uint32_t _mask_data(uint32_t Msk, uint32_t data);
/*** Tools ***/
void set_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg |= hbits;
}
void clear_reg(volatile uint32_t* reg, uint32_t hbits){
	*reg &= ~hbits;
}
/*** SUB Tools ***/
inline uint32_t _mask_var(uint32_t var, uint32_t Msk){
	return (var & Msk);
}
inline uint32_t _imask_var(uint32_t var, uint32_t Msk){
	return (var & ~Msk);
}
inline uint32_t _size_to_block(uint32_t size_block){
	return (size_block >= DWORD_BITS) ? 0xFFFFFFFFU : ((1U << size_block) - 1);
}
inline uint32_t _block_to_size(uint32_t block) {
    return block ? ((unsigned int)DWORD_BITS - __builtin_clz(block)) : 0U;
}
inline uint32_t _block_pos(uint32_t size_block, uint32_t block_n){
	return size_block * block_n;
}
inline uint32_t _block_mask(uint32_t size_block, uint32_t Pos){
	return _size_to_block(size_block) << Pos;
}
inline uint32_t _mask_pos(uint32_t Msk){
	return Msk ? (unsigned int)__builtin_ctz(Msk) : 0U;
}
inline uint32_t _mask_data(uint32_t Msk, uint32_t data){
	return _mask_var(data << _mask_pos(Msk), Msk);
}


inline uint32_t get_reg_field(uint32_t reg, uint32_t Msk, uint32_t Pos)
{
	return (reg & Msk) >> Pos;
}
inline void set_reg_field_encoded(volatile uint32_t* reg, uint32_t Msk, uint32_t ShiftedValue)
{
    uint32_t tmp = *reg;
    tmp &= ~Msk;
    tmp |= (ShiftedValue & Msk);
    *reg = tmp;
}


inline void write_reg_field(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data)
{
	uint32_t value = _imask_var(*reg, Msk);
	data = _mask_var((data << Pos), Msk); value |= data; *reg = value;
}
inline void set_reg_field(volatile uint32_t* reg, uint32_t Msk, uint32_t Pos, uint32_t data)
{
	data = _mask_var((data << Pos), Msk); clear_reg(reg, Msk); set_reg(reg, data);
}

uint32_t get_reg_Msk(uint32_t reg, uint32_t Msk)
{
	return get_reg_field(reg, Msk, _mask_pos(Msk));
}
void write_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data)
{
	write_reg_field(reg, Msk, _mask_pos(Msk), data);
}
void set_reg_Msk(volatile uint32_t* reg, uint32_t Msk, uint32_t data)
{
	set_reg_field(reg, Msk, _mask_pos(Msk), data);
}
uint32_t get_reg_block(uint32_t reg, uint8_t size_block, uint8_t Pos)
{
	return get_reg_field(reg, _block_mask(size_block, Pos), Pos);
}
void write_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	write_reg_field(reg, _block_mask(size_block, Pos), Pos, data);
}
void set_reg_block(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	set_reg_field(reg, _block_mask(size_block, Pos), Pos, data);
}
uint32_t get_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos)
{
	uint32_t n = Pos / DWORD_BITS; Pos = Pos % DWORD_BITS;
	return get_reg_field((uint32_t)*(reg + n), _block_mask(size_block, Pos), Pos);
}
void set_bit_block(volatile uint32_t* reg, uint8_t size_block, uint8_t Pos, uint32_t data)
{
	uint32_t n = Pos / DWORD_BITS; Pos = Pos % DWORD_BITS;
	set_reg_field((reg + n), _block_mask(size_block, Pos), Pos, data);
}
// --- Generic helpers ---
inline uint32_t reg_get(uint32_t reg, uint32_t Msk){
    return _mask_var(reg, Msk) >> _mask_pos(Msk);
}
inline void reg_set(volatile uint32_t *reg, uint32_t Msk, uint32_t data){
	*reg = _imask_var(*reg, Msk) | _mask_data(Msk, data);
}
/****************************************/
// UNUSED
void STM32446SetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits <= DWORD_BITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (uint32_t)(1 << va_arg(list, int));
		}
		va_end(list);
	}
}
void STM32446ResetRegBits( uint32_t* reg, uint8_t n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits <= DWORD_BITS){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (uint32_t)~(1 << va_arg(list, int));
		}
		va_end(list);
	}
}
void STM32446VecSetup( volatile uint32_t vec[], unsigned int size_block, unsigned int block_n, unsigned int data )
{
	const unsigned int n_bits = sizeof(data) * BYTE_BITS;
	if(size_block > n_bits){ size_block = n_bits; }
	const unsigned int block = _size_to_block(size_block);
	unsigned int index = _block_pos(size_block, block_n) / n_bits;
	data &= block;
	vec[index] &= ~( block << (_block_pos(size_block, block_n) - (index * n_bits)) );
	vec[index] |= ( data << (_block_pos(size_block, block_n) - (index * n_bits)) );
}

/****************************************/
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
    if (lock_ID >= FTDELAY_SIZE) return 0; // safety check

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
    if (ID >= FTDELAY_SIZE) return; // safety check
    ft_Delay_Lock[ID] = 0U;
    ftCounter[ID] = 0U;
}

/*** EOF ***/

