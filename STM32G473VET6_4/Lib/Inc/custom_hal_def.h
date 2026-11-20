/************************************************************************
	STM32G4
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
************************************************************************/
#ifndef CUSTOM_HAL_DEF_H
	#define CUSTOM_HAL_DEF_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#if !defined (HSE_VALUE)
#define HSE_VALUE (8000000UL) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined (HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT (100UL)   /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

#if !defined (HSI_VALUE)
#define HSI_VALUE (16000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined (HSI48_VALUE)
#define HSI48_VALUE (48000000UL) /*!< Value of the Internal High Speed oscillator for USB FS/RNG in Hz.
                                   The real value my vary depending on manufacturing process variations.*/
#endif /* HSI48_VALUE */

#if !defined (LSI_VALUE)
#define LSI_VALUE (32000UL)      /*!< LSI Typical Value in Hz*/
#endif /* LSI_VALUE */

#if !defined (LSE_VALUE)
#define LSE_VALUE (32768UL) /*!< Value of the External oscillator in Hz*/
#endif /* LSE_VALUE */

#if !defined (LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT (5000UL)  /*!< Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

#if !defined (EXTERNAL_CLOCK_VALUE)
#define EXTERNAL_CLOCK_VALUE (48000UL) /*!< Value of the External clock source in Hz*/
#endif /* EXTERNAL_CLOCK_VALUE */

#ifndef STM32G4xx_HAL_CONF_H

#define  VDD_VALUE                     (3300UL) /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY             (0x0FUL) /*!< tick interrupt priority */
#define  USE_RTOS                      0U
#define  PREFETCH_ENABLE               0U
#define  INSTRUCTION_CACHE_ENABLE      1U
#define  DATA_CACHE_ENABLE             1U

#define USE_SPI_CRC                    1U

#endif

#ifndef HAL_GPIO_MODULE_ENABLED

/*** MODER ***/
#define GPIO_MODE_Pos                  0U
#define GPIO_MODE                      (0x3UL << GPIO_MODE_Pos)
#define MODE_INPUT                     (0x0UL << GPIO_MODE_Pos)
#define MODE_OUTPUT                    (0x1UL << GPIO_MODE_Pos)
#define MODE_AF                        (0x2UL << GPIO_MODE_Pos)
#define MODE_ANALOG                    (0x3UL << GPIO_MODE_Pos)
/*** OTYPE ***/
#define OUTPUT_TYPE_Pos                0U
#define OUTPUT_TYPE                    (0x1UL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                      (0x0UL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                      (0x1UL << OUTPUT_TYPE_Pos)
/*** OSPEED ***/
#define  GPIO_SPEED_FREQ_LOW           (0x00000000U)   /*!< range up to 5 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_MEDIUM        (0x00000001U)   /*!< range  5 MHz to 25 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_HIGH          (0x00000002U)   /*!< range 25 MHz to 50 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_VERY_HIGH     (0x00000003U)   /*!< range 50 MHz to 120 MHz, please refer to the product datasheet */
/*** PUPD ***/
#define  GPIO_NOPULL                   (0x00000000U)   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP                   (0x00000001U)   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN                 (0x00000002U)   /*!< Pull-down activation                */

#define EXTI_MODE_Pos                  0U
#define EXTI_MODE                      (0x3UL << EXTI_MODE_Pos)
#define EXTI_IT                        (0x1UL << EXTI_MODE_Pos)
#define EXTI_EVT                       (0x2UL << EXTI_MODE_Pos)

#define TRIGGER_MODE_Pos               0U
#define TRIGGER_MODE                   (0x7UL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                 (0x1UL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                (0x2UL << TRIGGER_MODE_Pos)

#endif

typedef union{
	struct UN8bit{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
	}par;
	uint8_t var;
}U_byte;

typedef union{
	struct UN16bit{
		uint8_t l;
		uint8_t h;
	}par;
	uint16_t var;
}U_dbyte;

typedef union{
	struct UN32bit{
		uint16_t l;
		uint16_t h;
	}par;
	uint32_t var;
}U_word;

typedef union{
	struct UN64bit{
		uint32_t l;
		uint32_t h;
	}par;
	uint64_t var;
}U_dword;

#endif

/*** EOF ***/

