/**
  ******************************************************************************
  * @file    gpio_bitfield.h
  * @brief   Type definitions for STM32 GPIO registers utilizing type-safe 
  *          bitfields unions.
  ******************************************************************************
***/

#ifndef GPIO_BITFIELD_H
	#define GPIO_BITFIELD_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#ifndef __IO
#define __IO volatile
#endif

/**
 * @brief  GPIO port mode bitfield structure (2 bits per pin)
 */
typedef struct
{
  uint32_t MODE0  : 2;
  uint32_t MODE1  : 2;
  uint32_t MODE2  : 2;
  uint32_t MODE3  : 2;
  uint32_t MODE4  : 2;
  uint32_t MODE5  : 2;
  uint32_t MODE6  : 2;
  uint32_t MODE7  : 2;
  uint32_t MODE8  : 2;
  uint32_t MODE9  : 2;
  uint32_t MODE10 : 2;
  uint32_t MODE11 : 2;
  uint32_t MODE12 : 2;
  uint32_t MODE13 : 2;
  uint32_t MODE14 : 2;
  uint32_t MODE15 : 2;
} GPIO_MODER_BitField_TypeDef;

/**
 * @brief  GPIO port output type bitfield structure (1 bit per pin)
 */
typedef struct
{
  uint32_t OT0       : 1;
  uint32_t OT1       : 1;
  uint32_t OT2       : 1;
  uint32_t OT3       : 1;
  uint32_t OT4       : 1;
  uint32_t OT5       : 1;
  uint32_t OT6       : 1;
  uint32_t OT7       : 1;
  uint32_t OT8       : 1;
  uint32_t OT9       : 1;
  uint32_t OT10      : 1;
  uint32_t OT11      : 1;
  uint32_t OT12      : 1;
  uint32_t OT13      : 1;
  uint32_t OT14      : 1;
  uint32_t OT15      : 1;
  uint32_t Reserved  : 16;
} GPIO_OTYPER_BitField_TypeDef;

/**
 * @brief  GPIO port output speed bitfield structure (2 bits per pin)
 */
typedef struct
{
  uint32_t OSPEED0  : 2;
  uint32_t OSPEED1  : 2;
  uint32_t OSPEED2  : 2;
  uint32_t OSPEED3  : 2;
  uint32_t OSPEED4  : 2;
  uint32_t OSPEED5  : 2;
  uint32_t OSPEED6  : 2;
  uint32_t OSPEED7  : 2;
  uint32_t OSPEED8  : 2;
  uint32_t OSPEED9  : 2;
  uint32_t OSPEED10 : 2;
  uint32_t OSPEED11 : 2;
  uint32_t OSPEED12 : 2;
  uint32_t OSPEED13 : 2;
  uint32_t OSPEED14 : 2;
  uint32_t OSPEED15 : 2;
} GPIO_OSPEEDR_BitField_TypeDef;

/**
 * @brief  GPIO port pull-up/pull-down bitfield structure (2 bits per pin)
 */
typedef struct
{
  uint32_t PUPD0  : 2;
  uint32_t PUPD1  : 2;
  uint32_t PUPD2  : 2;
  uint32_t PUPD3  : 2;
  uint32_t PUPD4  : 2;
  uint32_t PUPD5  : 2;
  uint32_t PUPD6  : 2;
  uint32_t PUPD7  : 2;
  uint32_t PUPD8  : 2;
  uint32_t PUPD9  : 2;
  uint32_t PUPD10 : 2;
  uint32_t PUPD11 : 2;
  uint32_t PUPD12 : 2;
  uint32_t PUPD13 : 2;
  uint32_t PUPD14 : 2;
  uint32_t PUPD15 : 2;
} GPIO_PUPDR_BitField_TypeDef;

/**
 * @brief  GPIO port input data bitfield structure (1 bit per pin)
 */
typedef struct
{
  uint32_t ID0       : 1;
  uint32_t ID1       : 1;
  uint32_t ID2       : 1;
  uint32_t ID3       : 1;
  uint32_t ID4       : 1;
  uint32_t ID5       : 1;
  uint32_t ID6       : 1;
  uint32_t ID7       : 1;
  uint32_t ID8       : 1;
  uint32_t ID9       : 1;
  uint32_t ID10      : 1;
  uint32_t ID11      : 1;
  uint32_t ID12      : 1;
  uint32_t ID13      : 1;
  uint32_t ID14      : 1;
  uint32_t ID15      : 1;
  uint32_t Reserved  : 16;
} GPIO_IDR_BitField_TypeDef;

/**
 * @brief  GPIO port output data bitfield structure (1 bit per pin)
 */
typedef struct
{
  uint32_t OD0       : 1;
  uint32_t OD1       : 1;
  uint32_t OD2       : 1;
  uint32_t OD3       : 1;
  uint32_t OD4       : 1;
  uint32_t OD5       : 1;
  uint32_t OD6       : 1;
  uint32_t OD7       : 1;
  uint32_t OD8       : 1;
  uint32_t OD9       : 1;
  uint32_t OD10      : 1;
  uint32_t OD11      : 1;
  uint32_t OD12      : 1;
  uint32_t OD13      : 1;
  uint32_t OD14      : 1;
  uint32_t OD15      : 1;
  uint32_t Reserved  : 16;
} GPIO_ODR_BitField_TypeDef;

/**
 * @brief  GPIO port configuration lock bitfield structure
 */
typedef struct
{
  uint32_t LCK0      : 1;
  uint32_t LCK1      : 1;
  uint32_t LCK2      : 1;
  uint32_t LCK3      : 1;
  uint32_t LCK4      : 1;
  uint32_t LCK5      : 1;
  uint32_t LCK6      : 1;
  uint32_t LCK7      : 1;
  uint32_t LCK8      : 1;
  uint32_t LCK9      : 1;
  uint32_t LCK10     : 1;
  uint32_t LCK11     : 1;
  uint32_t LCK12     : 1;
  uint32_t LCK13     : 1;
  uint32_t LCK14     : 1;
  uint32_t LCK15     : 1;
  uint32_t LCKK      : 1;
  uint32_t Reserved  : 15;
} GPIO_LCKR_BitField_TypeDef;

/**
 * @brief  GPIO alternate function register bitfield structure (4 bits per pin)
 */
typedef struct
{
  uint32_t AFSEL0  : 4;  uint32_t AFSEL1  : 4;  uint32_t AFSEL2  : 4;  uint32_t AFSEL3  : 4;
  uint32_t AFSEL4  : 4;  uint32_t AFSEL5  : 4;  uint32_t AFSEL6  : 4;  uint32_t AFSEL7  : 4;
  uint32_t AFSEL8  : 4;  uint32_t AFSEL9  : 4;  uint32_t AFSEL10 : 4;  uint32_t AFSEL11 : 4;
  uint32_t AFSEL12 : 4;  uint32_t AFSEL13 : 4;  uint32_t AFSEL14 : 4;  uint32_t AFSEL15 : 4;
} GPIO_AFR_BitField_TypeDef;

typedef union { 
	__IO uint32_t reg; 
	GPIO_MODER_BitField_TypeDef    par; 
} GPIO_MODER_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_OTYPER_BitField_TypeDef   par; 
} GPIO_OTYPER_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_OSPEEDR_BitField_TypeDef  par; 
} GPIO_OSPEEDR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_PUPDR_BitField_TypeDef    par; 
} GPIO_PUPDR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_IDR_BitField_TypeDef      par; 
} GPIO_IDR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_ODR_BitField_TypeDef      par; 
} GPIO_ODR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_BSRR_BitField_TypeDef     par; 
} GPIO_BSRR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_LCKR_BitField_TypeDef     par; 
} GPIO_LCKR_TypeDef;
typedef union { 
	__IO uint32_t reg; 
	GPIO_BRR_BitField_TypeDef      par; 
} GPIO_BRR_TypeDef;
typedef union {
	__IO uint32_t             reg[2]; 
	GPIO_AFR_BitField_TypeDef par;    
} GPIO_AFR_TypeDef;

/**@brief General Purpose I/O port register structure*/
typedef struct {
	__IO GPIO_MODER_TypeDef MODER;
	__IO GPIO_OTYPER_TypeDef OTYPER;
	__IO GPIO_OSPEEDR_TypeDef OSPEEDR;
	__IO GPIO_PUPDR_TypeDef PUPDR;
	__IO GPIO_IDR_TypeDef IDR;
	__IO GPIO_ODR_TypeDef ODR;
	__IO uint32_t BSRR;
	__IO GPIO_LCKR_TypeDef LCKR;
	__IO GPIO_AFR_TypeDef AFR;
	__IO uint32_t BRR;
} GPIO_TypeDef;

#endif /* GPIO_BITFIELD_H */

