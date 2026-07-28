#ifndef STM32G4_REGISTER_H
	#define STM32G4_REGISTER_H

#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef union
{
    uint32_t val;

    struct {
        uint32_t DMA1EN               : 1;
        uint32_t DMA2EN               : 1;
        uint32_t DMAMUX1EN            : 1;
        uint32_t CORDICEN             : 1;
        uint32_t FMACEN               : 1;
        uint32_t RESERVED0   : 3;
        uint32_t FLASHEN              : 1;
        uint32_t RESERVED1   : 3;
        uint32_t CRCEN                : 1;
        uint32_t RESERVED2   : 19;
    } par;
} RCC_AHB1ENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t DMA1RST              : 1;
        uint32_t DMA2RST              : 1;
        uint32_t DMAMUX1RST           : 1;
        uint32_t CORDICRST            : 1;
        uint32_t FMACRST              : 1;
        uint32_t RESERVED0   : 3;
        uint32_t FLASHRST             : 1;
        uint32_t RESERVED1   : 3;
        uint32_t CRCRST               : 1;
        uint32_t RESERVED2   : 19;
    } par;
} RCC_AHB1RSTR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t DMA1SMEN             : 1;
        uint32_t DMA2SMEN             : 1;
        uint32_t DMAMUX1SMEN          : 1;
        uint32_t CORDICSMEN           : 1;
        uint32_t FMACSMEN             : 1;
        uint32_t RESERVED0   : 3;
        uint32_t FLASHSMEN            : 1;
        uint32_t SRAM1SMEN            : 1;
        uint32_t RESERVED1   : 2;
        uint32_t CRCSMEN              : 1;
        uint32_t RESERVED2   : 19;
    } par;
} RCC_AHB1SMENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t GPIOAEN              : 1;
        uint32_t GPIOBEN              : 1;
        uint32_t GPIOCEN              : 1;
        uint32_t GPIODEN              : 1;
        uint32_t GPIOEEN              : 1;
        uint32_t GPIOFEN              : 1;
        uint32_t GPIOGEN              : 1;
        uint32_t RESERVED0   : 6;
        uint32_t ADC12EN              : 1;
        uint32_t ADC345EN             : 1;
        uint32_t RESERVED1            : 1;
        uint32_t DAC1EN               : 1;
        uint32_t DAC2EN               : 1;
        uint32_t DAC3EN               : 1;
        uint32_t DAC4EN               : 1;
        uint32_t RESERVED2   : 6;
        uint32_t RNGEN                : 1;
        uint32_t RESERVED3   : 5;
    } par;
} RCC_AHB2ENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t GPIOARST             : 1;
        uint32_t GPIOBRST             : 1;
        uint32_t GPIOCRST             : 1;
        uint32_t GPIODRST             : 1;
        uint32_t GPIOERST             : 1;
        uint32_t GPIOFRST             : 1;
        uint32_t GPIOGRST             : 1;
        uint32_t RESERVED0   : 6;
        uint32_t ADC12RST             : 1;
        uint32_t ADC345RST            : 1;
        uint32_t RESERVED1   : 1;
        uint32_t DAC1RST              : 1;
        uint32_t DAC2RST              : 1;
        uint32_t DAC3RST              : 1;
        uint32_t DAC4RST              : 1;
        uint32_t RESERVED2   : 6;
        uint32_t RNGRST               : 1;
        uint32_t RESERVED3   : 5;
    } par;
} RCC_AHB2RSTR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t GPIOASMEN            : 1;
        uint32_t GPIOBSMEN            : 1;
        uint32_t GPIOCSMEN            : 1;
        uint32_t GPIODSMEN            : 1;
        uint32_t GPIOESMEN            : 1;
        uint32_t GPIOFSMEN            : 1;
        uint32_t GPIOGSMEN            : 1;
        uint32_t RESERVED0   : 2;
        uint32_t CCMSRAMSMEN          : 1;
        uint32_t SRAM2SMEN            : 1;
        uint32_t RESERVED1   : 2;
        uint32_t ADC12SMEN            : 1;
        uint32_t ADC345SMEN           : 1;
        uint32_t RESERVED2   : 1;
        uint32_t DAC1SMEN             : 1;
        uint32_t DAC2SMEN             : 1;
        uint32_t DAC3SMEN             : 1;
        uint32_t DAC4SMEN             : 1;
        uint32_t RESERVED3   : 6;
        uint32_t RNGSMEN              : 1;
        uint32_t RESERVED4   : 5;
    } par;
} RCC_AHB2SMENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t FMCEN                : 1;
        uint32_t RESERVED0   : 7;
        uint32_t QSPIEN               : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_AHB3ENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t FMCRST               : 1;
        uint32_t RESERVED0   : 7;
        uint32_t QSPIRST              : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_AHB3RSTR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t FMCSMEN              : 1;
        uint32_t RESERVED0   : 7;
        uint32_t QSPISMEN             : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_AHB3SMENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t TIM2EN               : 1;
        uint32_t TIM3EN               : 1;
        uint32_t TIM4EN               : 1;
        uint32_t TIM5EN               : 1;
        uint32_t TIM6EN               : 1;
        uint32_t TIM7EN               : 1;
        uint32_t RESERVED0   : 2;
        uint32_t CRSEN                : 1;
        uint32_t RESERVED1   : 1;
        uint32_t RTCAPBEN             : 1;
        uint32_t WWDGEN               : 1;
        uint32_t RESERVED2   : 2;
        uint32_t SPI2EN               : 1;
        uint32_t SPI3EN               : 1;
        uint32_t RESERVED3   : 1;
        uint32_t USART2EN             : 1;
        uint32_t USART3EN             : 1;
        uint32_t UART4EN              : 1;
        uint32_t UART5EN              : 1;
        uint32_t I2C1EN               : 1;
        uint32_t I2C2EN               : 1;
        uint32_t USBEN                : 1;
        uint32_t RESERVED4   : 1;
        uint32_t FDCANEN              : 1;
        uint32_t RESERVED5   : 2;
        uint32_t PWREN                : 1;
        uint32_t RESERVED6   : 1;
        uint32_t I2C3EN               : 1;
        uint32_t LPTIM1EN             : 1;
    } par;
} RCC_APB1ENR1_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LPUART1EN            : 1;
        uint32_t I2C4EN               : 1;
        uint32_t RESERVED0   : 6;
        uint32_t UCPD1EN              : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_APB1ENR2_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t TIM2RST              : 1;
        uint32_t TIM3RST              : 1;
        uint32_t TIM4RST              : 1;
        uint32_t TIM5RST              : 1;
        uint32_t TIM6RST              : 1;
        uint32_t TIM7RST              : 1;
        uint32_t RESERVED0   : 2;
        uint32_t CRSRST               : 1;
        uint32_t RESERVED1   : 5;
        uint32_t SPI2RST              : 1;
        uint32_t SPI3RST              : 1;
        uint32_t RESERVED2   : 1;
        uint32_t USART2RST            : 1;
        uint32_t USART3RST            : 1;
        uint32_t UART4RST             : 1;
        uint32_t UART5RST             : 1;
        uint32_t I2C1RST              : 1;
        uint32_t I2C2RST              : 1;
        uint32_t USBRST               : 1;
        uint32_t RESERVED3   : 1;
        uint32_t FDCANRST             : 1;
        uint32_t RESERVED4   : 2;
        uint32_t PWRRST               : 1;
        uint32_t RESERVED5   : 1;
        uint32_t I2C3RST              : 1;
        uint32_t LPTIM1RST            : 1;
    } par;
} RCC_APB1RSTR1_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LPUART1RST           : 1;
        uint32_t I2C4RST              : 1;
        uint32_t RESERVED0   : 6;
        uint32_t UCPD1RST             : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_APB1RSTR2_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t TIM2SMEN             : 1;
        uint32_t TIM3SMEN             : 1;
        uint32_t TIM4SMEN             : 1;
        uint32_t TIM5SMEN             : 1;
        uint32_t TIM6SMEN             : 1;
        uint32_t TIM7SMEN             : 1;
        uint32_t RESERVED0   : 2;
        uint32_t CRSSMEN              : 1;
        uint32_t RESERVED1   : 1;
        uint32_t RTCAPBSMEN           : 1;
        uint32_t WWDGSMEN             : 1;
        uint32_t RESERVED2   : 2;
        uint32_t SPI2SMEN             : 1;
        uint32_t SPI3SMEN             : 1;
        uint32_t RESERVED3   : 1;
        uint32_t USART2SMEN           : 1;
        uint32_t USART3SMEN           : 1;
        uint32_t UART4SMEN            : 1;
        uint32_t UART5SMEN            : 1;
        uint32_t I2C1SMEN             : 1;
        uint32_t I2C2SMEN             : 1;
        uint32_t USBSMEN              : 1;
        uint32_t RESERVED4   : 1;
        uint32_t FDCANSMEN            : 1;
        uint32_t RESERVED5   : 2;
        uint32_t PWRSMEN              : 1;
        uint32_t RESERVED6   : 1;
        uint32_t I2C3SMEN             : 1;
        uint32_t LPTIM1SMEN           : 1;
    } par;
} RCC_APB1SMENR1_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LPUART1SMEN          : 1;
        uint32_t I2C4SMEN             : 1;
        uint32_t RESERVED0   : 6;
        uint32_t UCPD1SMEN            : 1;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_APB1SMENR2_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t SYSCFGEN             : 1;
        uint32_t RESERVED0   : 10;
        uint32_t TIM1EN               : 1;
        uint32_t SPI1EN               : 1;
        uint32_t TIM8EN               : 1;
        uint32_t USART1EN             : 1;
        uint32_t SPI4EN               : 1;
        uint32_t TIM15EN              : 1;
        uint32_t TIM16EN              : 1;
        uint32_t TIM17EN              : 1;
        uint32_t RESERVED1   : 1;
        uint32_t TIM20EN              : 1;
        uint32_t SAI1EN               : 1;
        uint32_t RESERVED2   : 10;
    } par;
} RCC_APB2ENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t SYSCFGRST            : 1;
        uint32_t RESERVED0   : 10;
        uint32_t TIM1RST              : 1;
        uint32_t SPI1RST              : 1;
        uint32_t TIM8RST              : 1;
        uint32_t USART1RST            : 1;
        uint32_t SPI4RST              : 1;
        uint32_t TIM15RST             : 1;
        uint32_t TIM16RST             : 1;
        uint32_t TIM17RST             : 1;
        uint32_t RESERVED1   : 1;
        uint32_t TIM20RST             : 1;
        uint32_t SAI1RST              : 1;
        uint32_t RESERVED2   : 10;
    } par;
} RCC_APB2RSTR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t SYSCFGSMEN           : 1;
        uint32_t RESERVED0   : 10;
        uint32_t TIM1SMEN             : 1;
        uint32_t SPI1SMEN             : 1;
        uint32_t TIM8SMEN             : 1;
        uint32_t USART1SMEN           : 1;
        uint32_t SPI4SMEN             : 1;
        uint32_t TIM15SMEN            : 1;
        uint32_t TIM16SMEN            : 1;
        uint32_t TIM17SMEN            : 1;
        uint32_t RESERVED1   : 1;
        uint32_t TIM20SMEN            : 1;
        uint32_t SAI1SMEN             : 1;
        uint32_t RESERVED2   : 10;
    } par;
} RCC_APB2SMENR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LSEON                : 1;
        uint32_t LSERDY               : 1;
        uint32_t LSEBYP               : 1;
        uint32_t LSEDRV               : 2;
        uint32_t LSECSSON             : 1;
        uint32_t LSECSSD              : 1;
        uint32_t RESERVED0   : 1;
        uint32_t RTCSEL               : 2;
        uint32_t RESERVED1   : 5;
        uint32_t RTCEN                : 1;
        uint32_t BDRST                : 1;
        uint32_t RESERVED2   : 7;
        uint32_t LSCOEN               : 1;
        uint32_t LSCOSEL              : 1;
        uint32_t RESERVED3   : 6;
    } par;
} RCC_BDCR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t USART1SEL            : 2;
        uint32_t USART2SEL            : 2;
        uint32_t USART3SEL            : 2;
        uint32_t UART4SEL             : 2;
        uint32_t UART5SEL             : 2;
        uint32_t LPUART1SEL           : 2;
        uint32_t I2C1SEL              : 2;
        uint32_t I2C2SEL              : 2;
        uint32_t I2C3SEL              : 2;
        uint32_t LPTIM1SEL            : 2;
        uint32_t SAI1SEL              : 2;
        uint32_t I2S23SEL             : 2;
        uint32_t FDCANSEL             : 2;
        uint32_t CLK48SEL             : 2;
        uint32_t ADC12SEL             : 2;
        uint32_t ADC345SEL            : 2;
    } par;
} RCC_CCIPR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t I2C4SEL              : 2;
        uint32_t RESERVED0   : 18;
        uint32_t QSPISEL              : 2;
        uint32_t RESERVED1   : 10;
    } par;
} RCC_CCIPR2_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t SW                   : 2;
        uint32_t SWS                  : 2;
        uint32_t HPRE                 : 4;
        uint32_t PPRE1                : 3;
        uint32_t PPRE2                : 3;
        uint32_t RESERVED0   : 10;
        uint32_t MCOSEL               : 4;
        uint32_t MCOPRE               : 3;
        uint32_t RESERVED1   : 1;
    } par;
} RCC_CFGR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LSIRDYC              : 1;
        uint32_t LSERDYC              : 1;
        uint32_t RESERVED0   : 1;
        uint32_t HSIRDYC              : 1;
        uint32_t HSERDYC              : 1;
        uint32_t PLLRDYC              : 1;
        uint32_t RESERVED1   : 2;
        uint32_t CSSC                 : 1;
        uint32_t LSECSSC              : 1;
        uint32_t HSI48RDYC            : 1;
        uint32_t RESERVED2   : 21;
    } par;
} RCC_CICR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LSIRDYIE             : 1;
        uint32_t LSERDYIE             : 1;
        uint32_t RESERVED0   : 1;
        uint32_t HSIRDYIE             : 1;
        uint32_t HSERDYIE             : 1;
        uint32_t PLLRDYIE             : 1;
        uint32_t RESERVED1   : 3;
        uint32_t LSECSSIE             : 1;
        uint32_t HSI48RDYIE           : 1;
        uint32_t RESERVED2   : 21;
    } par;
} RCC_CIER_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LSIRDYF              : 1;
        uint32_t LSERDYF              : 1;
        uint32_t RESERVED0   : 1;
        uint32_t HSIRDYF              : 1;
        uint32_t HSERDYF              : 1;
        uint32_t PLLRDYF              : 1;
        uint32_t RESERVED1   : 2;
        uint32_t CSSF                 : 1;
        uint32_t LSECSSF              : 1;
        uint32_t HSI48RDYF            : 1;
        uint32_t RESERVED2   : 21;
    } par;
} RCC_CIFR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t RESERVED0   : 8;
        uint32_t HSION                : 1;
        uint32_t HSIKERON             : 1;
        uint32_t HSIRDY               : 1;
        uint32_t RESERVED1   : 5;
        uint32_t HSEON                : 1;
        uint32_t HSERDY               : 1;
        uint32_t HSEBYP               : 1;
        uint32_t CSSON                : 1;
        uint32_t RESERVED2   : 4;
        uint32_t PLLON                : 1;
        uint32_t PLLRDY               : 1;
        uint32_t RESERVED3   : 6;
    } par;
} RCC_CR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t HSI48ON              : 1;
        uint32_t HSI48RDY             : 1;
        uint32_t RESERVED0   : 5;
        uint32_t HSI48CAL             : 2;
        uint32_t RESERVED1   : 23;
    } par;
} RCC_CRRCR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t LSION                : 1;
        uint32_t LSIRDY               : 1;
        uint32_t RESERVED0   : 21;
        uint32_t RMVF                 : 1;
        uint32_t RESERVED1   : 1;
        uint32_t OBLRSTF              : 1;
        uint32_t PINRSTF              : 1;
        uint32_t BORRSTF              : 1;
        uint32_t SFTRSTF              : 1;
        uint32_t IWDGRSTF             : 1;
        uint32_t WWDGRSTF             : 1;
        uint32_t LPWRRSTF             : 1;
    } par;
} RCC_CSR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t RESERVED0   : 16;
        uint32_t HSICAL               : 8;
        uint32_t HSITRIM              : 7;
        uint32_t RESERVED1   : 1;
    } par;
} RCC_ICSCR_reg;

typedef union
{
    uint32_t val;

    struct {
        uint32_t PLLSRC               : 2;
        uint32_t RESERVED0   : 2;
        uint32_t PLLM                 : 4;
        uint32_t PLLN                 : 7;
        uint32_t RESERVED1   : 1;
        uint32_t PLLPEN               : 1;
        uint32_t PLLP                 : 1;
        uint32_t RESERVED2   : 2;
        uint32_t PLLQEN               : 1;
        uint32_t PLLQ                 : 2;
        uint32_t RESERVED3   : 1;
        uint32_t PLLREN               : 1;
        uint32_t PLLR                 : 2;
        uint32_t PLLPDIV              : 5;
    } par;
} RCC_PLLCFGR_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_MODER_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_OTYPER_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_OSPEEDR_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_PUPDR_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_IDR_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_ODR_reg;

typedef union { 
	uint32_t val;

	struct {
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
	} par;
} GPIO_LCKR_reg;

typedef union {
	uint32_t reg[2];

	struct {
	  uint32_t AFSEL0  : 4;  uint32_t AFSEL1  : 4;  uint32_t AFSEL2  : 4;  uint32_t AFSEL3  : 4;
	  uint32_t AFSEL4  : 4;  uint32_t AFSEL5  : 4;  uint32_t AFSEL6  : 4;  uint32_t AFSEL7  : 4;
	  uint32_t AFSEL8  : 4;  uint32_t AFSEL9  : 4;  uint32_t AFSEL10 : 4;  uint32_t AFSEL11 : 4;
	  uint32_t AFSEL12 : 4;  uint32_t AFSEL13 : 4;  uint32_t AFSEL14 : 4;  uint32_t AFSEL15 : 4;
	} par;
} GPIO_AFR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t PE          : 1;
        uint32_t TXIE        : 1;
        uint32_t RXIE        : 1;
        uint32_t ADDRIE      : 1;
        uint32_t NACKIE      : 1;
        uint32_t STOPIE      : 1;
        uint32_t TCIE        : 1;
        uint32_t ERRIE       : 1;
        uint32_t DNF         : 4;
        uint32_t ANFOFF      : 1;
        uint32_t SWRST       : 1;
        uint32_t TXDMAEN     : 1;
        uint32_t RXDMAEN     : 1;
        uint32_t SBC         : 1;
        uint32_t NOSTRETCH   : 1;
        uint32_t WUPEN       : 1;
        uint32_t GCEN        : 1;
        uint32_t SMBHEN      : 1;
        uint32_t SMBDEN      : 1;
        uint32_t ALERTEN     : 1;
        uint32_t PECEN       : 1;
        uint32_t RESERVED    : 8;

    } par;

} I2C_CR1_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t SADD        :10;
        uint32_t RD_WRN      : 1;
        uint32_t ADD10       : 1;
        uint32_t HEAD10R     : 1;
        uint32_t START       : 1;
        uint32_t STOP        : 1;
        uint32_t NACK        : 1;
        uint32_t NBYTES      : 8;
        uint32_t RELOAD      : 1;
        uint32_t AUTOEND     : 1;
        uint32_t PECBYTE     : 1;
        uint32_t RESERVED    : 5;

    } par;

} I2C_CR2_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t OA1         :10;
        uint32_t OA1MODE     : 1;
        uint32_t RESERVED0   : 4;
        uint32_t OA1EN       : 1;
        uint32_t RESERVED1   :16;

    } par;

} I2C_OAR1_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t RESERVED0   : 1;
        uint32_t OA2         : 7;
        uint32_t OA2MSK      : 3;
        uint32_t RESERVED1   : 4;
        uint32_t OA2EN       : 1;
        uint32_t RESERVED2   :16;

    } par;

} I2C_OAR2_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t SCLL        : 8;
        uint32_t SCLH        : 8;
        uint32_t SDADEL      : 4;
        uint32_t SCLDEL      : 4;
        uint32_t RESERVED    : 4;
        uint32_t PRESC       : 4;

    } par;

} I2C_TIMINGR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t TIMEOUTA    :12;
        uint32_t TIDLE       : 1;
        uint32_t RESERVED0   : 2;
        uint32_t TIMOUTEN    : 1;
        uint32_t TIMEOUTB    :12;
        uint32_t RESERVED1   : 3;
        uint32_t TEXTEN      : 1;

    } par;

} I2C_TIMEOUTR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t TXE         : 1;
        uint32_t TXIS        : 1;
        uint32_t RXNE        : 1;
        uint32_t ADDR        : 1;
        uint32_t NACKF       : 1;
        uint32_t STOPF       : 1;
        uint32_t TC          : 1;
        uint32_t TCR         : 1;
        uint32_t BERR        : 1;
        uint32_t ARLO        : 1;
        uint32_t OVR         : 1;
        uint32_t PECERR      : 1;
        uint32_t TIMEOUT     : 1;
        uint32_t ALERT       : 1;
        uint32_t RESERVED0   : 1;
        uint32_t BUSY        : 1;
        uint32_t DIR         : 1;
        uint32_t ADDCODE     : 7;
        uint32_t RESERVED1   : 8;

    } par;

} I2C_ISR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t RESERVED0   : 3;
        uint32_t ADDRCF      : 1;
        uint32_t NACKCF      : 1;
        uint32_t STOPCF      : 1;
        uint32_t RESERVED1   : 2;
        uint32_t BERRCF      : 1;
        uint32_t ARLOCF      : 1;
        uint32_t OVRCF       : 1;
        uint32_t PECCF       : 1;
        uint32_t TIMOUTCF    : 1;
        uint32_t ALERTCF     : 1;
        uint32_t RESERVED2   :18;

    } par;

} I2C_ICR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t PEC         : 8;
        uint32_t RESERVED    :24;

    } par;

} I2C_PECR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t RXDATA      : 8;
        uint32_t RESERVED    :24;

    } par;

} I2C_RXDR_reg;

typedef union
{
    uint32_t val;

    struct
    {
        uint32_t TXDATA      : 8;
        uint32_t RESERVED    :24;

    } par;

} I2C_TXDR_reg;

#endif

/*** EOF ***/

