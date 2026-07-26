//=============================================================================
// rcc_bitfield.h
// STM32G473VET6 RCC Bitfield Definitions
//=============================================================================

#ifndef RCC_BITFIELD_H
	#define RCC_BITFIELD_H
 
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1EN               : 1;
        volatile uint32_t DMA2EN               : 1;
        volatile uint32_t DMAMUX1EN            : 1;
        volatile uint32_t CORDICEN             : 1;
        volatile uint32_t FMACEN               : 1;
        volatile uint32_t RESERVED0   : 3;
        volatile uint32_t FLASHEN              : 1;
        volatile uint32_t RESERVED1   : 3;
        volatile uint32_t CRCEN                : 1;
        volatile uint32_t RESERVED2   : 19;
    } par;

} RCC_AHB1ENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1RST              : 1;
        volatile uint32_t DMA2RST              : 1;
        volatile uint32_t DMAMUX1RST           : 1;
        volatile uint32_t CORDICRST            : 1;
        volatile uint32_t FMACRST              : 1;
        volatile uint32_t RESERVED0   : 3;
        volatile uint32_t FLASHRST             : 1;
        volatile uint32_t RESERVED1   : 3;
        volatile uint32_t CRCRST               : 1;
        volatile uint32_t RESERVED2   : 19;
    } par;

} RCC_AHB1RSTR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1SMEN             : 1;
        volatile uint32_t DMA2SMEN             : 1;
        volatile uint32_t DMAMUX1SMEN          : 1;
        volatile uint32_t CORDICSMEN           : 1;
        volatile uint32_t FMACSMEN             : 1;
        volatile uint32_t RESERVED0   : 3;
        volatile uint32_t FLASHSMEN            : 1;
        volatile uint32_t SRAM1SMEN            : 1;
        volatile uint32_t RESERVED1   : 2;
        volatile uint32_t CRCSMEN              : 1;
        volatile uint32_t RESERVED2   : 19;
    } par;

} RCC_AHB1SMENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOAEN              : 1;
        volatile uint32_t GPIOBEN              : 1;
        volatile uint32_t GPIOCEN              : 1;
        volatile uint32_t GPIODEN              : 1;
        volatile uint32_t GPIOEEN              : 1;
        volatile uint32_t GPIOFEN              : 1;
        volatile uint32_t GPIOGEN              : 1;
        volatile uint32_t RESERVED0   : 6;
        volatile uint32_t ADC12EN              : 1;
        volatile uint32_t ADC345EN             : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t DAC1EN               : 1;
        volatile uint32_t DAC2EN               : 1;
        volatile uint32_t DAC3EN               : 1;
        volatile uint32_t DAC4EN               : 1;
        volatile uint32_t RESERVED2   : 6;
        volatile uint32_t RNGEN                : 1;
        volatile uint32_t RESERVED3   : 5;
    } par;

} RCC_AHB2ENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOARST             : 1;
        volatile uint32_t GPIOBRST             : 1;
        volatile uint32_t GPIOCRST             : 1;
        volatile uint32_t GPIODRST             : 1;
        volatile uint32_t GPIOERST             : 1;
        volatile uint32_t GPIOFRST             : 1;
        volatile uint32_t GPIOGRST             : 1;
        volatile uint32_t RESERVED0   : 6;
        volatile uint32_t ADC12RST             : 1;
        volatile uint32_t ADC345RST            : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t DAC1RST              : 1;
        volatile uint32_t DAC2RST              : 1;
        volatile uint32_t DAC3RST              : 1;
        volatile uint32_t DAC4RST              : 1;
        volatile uint32_t RESERVED2   : 6;
        volatile uint32_t RNGRST               : 1;
        volatile uint32_t RESERVED3   : 5;
    } par;

} RCC_AHB2RSTR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOASMEN            : 1;
        volatile uint32_t GPIOBSMEN            : 1;
        volatile uint32_t GPIOCSMEN            : 1;
        volatile uint32_t GPIODSMEN            : 1;
        volatile uint32_t GPIOESMEN            : 1;
        volatile uint32_t GPIOFSMEN            : 1;
        volatile uint32_t GPIOGSMEN            : 1;
        volatile uint32_t RESERVED0   : 2;
        volatile uint32_t CCMSRAMSMEN          : 1;
        volatile uint32_t SRAM2SMEN            : 1;
        volatile uint32_t RESERVED1   : 2;
        volatile uint32_t ADC12SMEN            : 1;
        volatile uint32_t ADC345SMEN           : 1;
        volatile uint32_t RESERVED2   : 1;
        volatile uint32_t DAC1SMEN             : 1;
        volatile uint32_t DAC2SMEN             : 1;
        volatile uint32_t DAC3SMEN             : 1;
        volatile uint32_t DAC4SMEN             : 1;
        volatile uint32_t RESERVED3   : 6;
        volatile uint32_t RNGSMEN              : 1;
        volatile uint32_t RESERVED4   : 5;
    } par;

} RCC_AHB2SMENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCEN                : 1;
        volatile uint32_t RESERVED0   : 7;
        volatile uint32_t QSPIEN               : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_AHB3ENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCRST               : 1;
        volatile uint32_t RESERVED0   : 7;
        volatile uint32_t QSPIRST              : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_AHB3RSTR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCSMEN              : 1;
        volatile uint32_t RESERVED0   : 7;
        volatile uint32_t QSPISMEN             : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_AHB3SMENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2EN               : 1;
        volatile uint32_t TIM3EN               : 1;
        volatile uint32_t TIM4EN               : 1;
        volatile uint32_t TIM5EN               : 1;
        volatile uint32_t TIM6EN               : 1;
        volatile uint32_t TIM7EN               : 1;
        volatile uint32_t RESERVED0   : 2;
        volatile uint32_t CRSEN                : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t RTCAPBEN             : 1;
        volatile uint32_t WWDGEN               : 1;
        volatile uint32_t RESERVED2   : 2;
        volatile uint32_t SPI2EN               : 1;
        volatile uint32_t SPI3EN               : 1;
        volatile uint32_t RESERVED3   : 1;
        volatile uint32_t USART2EN             : 1;
        volatile uint32_t USART3EN             : 1;
        volatile uint32_t UART4EN              : 1;
        volatile uint32_t UART5EN              : 1;
        volatile uint32_t I2C1EN               : 1;
        volatile uint32_t I2C2EN               : 1;
        volatile uint32_t USBEN                : 1;
        volatile uint32_t RESERVED4   : 1;
        volatile uint32_t FDCANEN              : 1;
        volatile uint32_t RESERVED5   : 2;
        volatile uint32_t PWREN                : 1;
        volatile uint32_t RESERVED6   : 1;
        volatile uint32_t I2C3EN               : 1;
        volatile uint32_t LPTIM1EN             : 1;
    } par;

} RCC_APB1ENR1_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1EN            : 1;
        volatile uint32_t I2C4EN               : 1;
        volatile uint32_t RESERVED0   : 6;
        volatile uint32_t UCPD1EN              : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_APB1ENR2_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2RST              : 1;
        volatile uint32_t TIM3RST              : 1;
        volatile uint32_t TIM4RST              : 1;
        volatile uint32_t TIM5RST              : 1;
        volatile uint32_t TIM6RST              : 1;
        volatile uint32_t TIM7RST              : 1;
        volatile uint32_t RESERVED0   : 2;
        volatile uint32_t CRSRST               : 1;
        volatile uint32_t RESERVED1   : 5;
        volatile uint32_t SPI2RST              : 1;
        volatile uint32_t SPI3RST              : 1;
        volatile uint32_t RESERVED2   : 1;
        volatile uint32_t USART2RST            : 1;
        volatile uint32_t USART3RST            : 1;
        volatile uint32_t UART4RST             : 1;
        volatile uint32_t UART5RST             : 1;
        volatile uint32_t I2C1RST              : 1;
        volatile uint32_t I2C2RST              : 1;
        volatile uint32_t USBRST               : 1;
        volatile uint32_t RESERVED3   : 1;
        volatile uint32_t FDCANRST             : 1;
        volatile uint32_t RESERVED4   : 2;
        volatile uint32_t PWRRST               : 1;
        volatile uint32_t RESERVED5   : 1;
        volatile uint32_t I2C3RST              : 1;
        volatile uint32_t LPTIM1RST            : 1;
    } par;

} RCC_APB1RSTR1_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1RST           : 1;
        volatile uint32_t I2C4RST              : 1;
        volatile uint32_t RESERVED0   : 6;
        volatile uint32_t UCPD1RST             : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_APB1RSTR2_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2SMEN             : 1;
        volatile uint32_t TIM3SMEN             : 1;
        volatile uint32_t TIM4SMEN             : 1;
        volatile uint32_t TIM5SMEN             : 1;
        volatile uint32_t TIM6SMEN             : 1;
        volatile uint32_t TIM7SMEN             : 1;
        volatile uint32_t RESERVED0   : 2;
        volatile uint32_t CRSSMEN              : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t RTCAPBSMEN           : 1;
        volatile uint32_t WWDGSMEN             : 1;
        volatile uint32_t RESERVED2   : 2;
        volatile uint32_t SPI2SMEN             : 1;
        volatile uint32_t SPI3SMEN             : 1;
        volatile uint32_t RESERVED3   : 1;
        volatile uint32_t USART2SMEN           : 1;
        volatile uint32_t USART3SMEN           : 1;
        volatile uint32_t UART4SMEN            : 1;
        volatile uint32_t UART5SMEN            : 1;
        volatile uint32_t I2C1SMEN             : 1;
        volatile uint32_t I2C2SMEN             : 1;
        volatile uint32_t USBSMEN              : 1;
        volatile uint32_t RESERVED4   : 1;
        volatile uint32_t FDCANSMEN            : 1;
        volatile uint32_t RESERVED5   : 2;
        volatile uint32_t PWRSMEN              : 1;
        volatile uint32_t RESERVED6   : 1;
        volatile uint32_t I2C3SMEN             : 1;
        volatile uint32_t LPTIM1SMEN           : 1;
    } par;

} RCC_APB1SMENR1_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1SMEN          : 1;
        volatile uint32_t I2C4SMEN             : 1;
        volatile uint32_t RESERVED0   : 6;
        volatile uint32_t UCPD1SMEN            : 1;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_APB1SMENR2_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGEN             : 1;
        volatile uint32_t RESERVED0   : 10;
        volatile uint32_t TIM1EN               : 1;
        volatile uint32_t SPI1EN               : 1;
        volatile uint32_t TIM8EN               : 1;
        volatile uint32_t USART1EN             : 1;
        volatile uint32_t SPI4EN               : 1;
        volatile uint32_t TIM15EN              : 1;
        volatile uint32_t TIM16EN              : 1;
        volatile uint32_t TIM17EN              : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t TIM20EN              : 1;
        volatile uint32_t SAI1EN               : 1;
        volatile uint32_t RESERVED2   : 10;
    } par;

} RCC_APB2ENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGRST            : 1;
        volatile uint32_t RESERVED0   : 10;
        volatile uint32_t TIM1RST              : 1;
        volatile uint32_t SPI1RST              : 1;
        volatile uint32_t TIM8RST              : 1;
        volatile uint32_t USART1RST            : 1;
        volatile uint32_t SPI4RST              : 1;
        volatile uint32_t TIM15RST             : 1;
        volatile uint32_t TIM16RST             : 1;
        volatile uint32_t TIM17RST             : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t TIM20RST             : 1;
        volatile uint32_t SAI1RST              : 1;
        volatile uint32_t RESERVED2   : 10;
    } par;

} RCC_APB2RSTR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGSMEN           : 1;
        volatile uint32_t RESERVED0   : 10;
        volatile uint32_t TIM1SMEN             : 1;
        volatile uint32_t SPI1SMEN             : 1;
        volatile uint32_t TIM8SMEN             : 1;
        volatile uint32_t USART1SMEN           : 1;
        volatile uint32_t SPI4SMEN             : 1;
        volatile uint32_t TIM15SMEN            : 1;
        volatile uint32_t TIM16SMEN            : 1;
        volatile uint32_t TIM17SMEN            : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t TIM20SMEN            : 1;
        volatile uint32_t SAI1SMEN             : 1;
        volatile uint32_t RESERVED2   : 10;
    } par;

} RCC_APB2SMENR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSEON                : 1;
        volatile uint32_t LSERDY               : 1;
        volatile uint32_t LSEBYP               : 1;
        volatile uint32_t LSEDRV               : 2;
        volatile uint32_t LSECSSON             : 1;
        volatile uint32_t LSECSSD              : 1;
        volatile uint32_t RESERVED0   : 1;
        volatile uint32_t RTCSEL               : 2;
        volatile uint32_t RESERVED1   : 5;
        volatile uint32_t RTCEN                : 1;
        volatile uint32_t BDRST                : 1;
        volatile uint32_t RESERVED2   : 7;
        volatile uint32_t LSCOEN               : 1;
        volatile uint32_t LSCOSEL              : 1;
        volatile uint32_t RESERVED3   : 6;
    } par;

} RCC_BDCR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t USART1SEL            : 2;
        volatile uint32_t USART2SEL            : 2;
        volatile uint32_t USART3SEL            : 2;
        volatile uint32_t UART4SEL             : 2;
        volatile uint32_t UART5SEL             : 2;
        volatile uint32_t LPUART1SEL           : 2;
        volatile uint32_t I2C1SEL              : 2;
        volatile uint32_t I2C2SEL              : 2;
        volatile uint32_t I2C3SEL              : 2;
        volatile uint32_t LPTIM1SEL            : 2;
        volatile uint32_t SAI1SEL              : 2;
        volatile uint32_t I2S23SEL             : 2;
        volatile uint32_t FDCANSEL             : 2;
        volatile uint32_t CLK48SEL             : 2;
        volatile uint32_t ADC12SEL             : 2;
        volatile uint32_t ADC345SEL            : 2;
    } par;

} RCC_CCIPR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t I2C4SEL              : 2;
        volatile uint32_t RESERVED0   : 18;
        volatile uint32_t QSPISEL              : 2;
        volatile uint32_t RESERVED1   : 10;
    } par;

} RCC_CCIPR2_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SW                   : 2;
        volatile uint32_t SWS                  : 2;
        volatile uint32_t HPRE                 : 4;
        volatile uint32_t PPRE1                : 3;
        volatile uint32_t PPRE2                : 3;
        volatile uint32_t RESERVED0   : 10;
        volatile uint32_t MCOSEL               : 4;
        volatile uint32_t MCOPRE               : 3;
        volatile uint32_t RESERVED1   : 1;
    } par;

} RCC_CFGR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYC              : 1;
        volatile uint32_t LSERDYC              : 1;
        volatile uint32_t RESERVED0   : 1;
        volatile uint32_t HSIRDYC              : 1;
        volatile uint32_t HSERDYC              : 1;
        volatile uint32_t PLLRDYC              : 1;
        volatile uint32_t RESERVED1   : 2;
        volatile uint32_t CSSC                 : 1;
        volatile uint32_t LSECSSC              : 1;
        volatile uint32_t HSI48RDYC            : 1;
        volatile uint32_t RESERVED2   : 21;
    } par;

} RCC_CICR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYIE             : 1;
        volatile uint32_t LSERDYIE             : 1;
        volatile uint32_t RESERVED0   : 1;
        volatile uint32_t HSIRDYIE             : 1;
        volatile uint32_t HSERDYIE             : 1;
        volatile uint32_t PLLRDYIE             : 1;
        volatile uint32_t RESERVED1   : 3;
        volatile uint32_t LSECSSIE             : 1;
        volatile uint32_t HSI48RDYIE           : 1;
        volatile uint32_t RESERVED2   : 21;
    } par;

} RCC_CIER_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYF              : 1;
        volatile uint32_t LSERDYF              : 1;
        volatile uint32_t RESERVED0   : 1;
        volatile uint32_t HSIRDYF              : 1;
        volatile uint32_t HSERDYF              : 1;
        volatile uint32_t PLLRDYF              : 1;
        volatile uint32_t RESERVED1   : 2;
        volatile uint32_t CSSF                 : 1;
        volatile uint32_t LSECSSF              : 1;
        volatile uint32_t HSI48RDYF            : 1;
        volatile uint32_t RESERVED2   : 21;
    } par;

} RCC_CIFR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t RESERVED0   : 8;
        volatile uint32_t HSION                : 1;
        volatile uint32_t HSIKERON             : 1;
        volatile uint32_t HSIRDY               : 1;
        volatile uint32_t RESERVED1   : 5;
        volatile uint32_t HSEON                : 1;
        volatile uint32_t HSERDY               : 1;
        volatile uint32_t HSEBYP               : 1;
        volatile uint32_t CSSON                : 1;
        volatile uint32_t RESERVED2   : 4;
        volatile uint32_t PLLON                : 1;
        volatile uint32_t PLLRDY               : 1;
        volatile uint32_t RESERVED3   : 6;
    } par;

} RCC_CR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t HSI48ON              : 1;
        volatile uint32_t HSI48RDY             : 1;
        volatile uint32_t RESERVED0   : 5;
        volatile uint32_t HSI48CAL             : 2;
        volatile uint32_t RESERVED1   : 23;
    } par;

} RCC_CRRCR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSION                : 1;
        volatile uint32_t LSIRDY               : 1;
        volatile uint32_t RESERVED0   : 21;
        volatile uint32_t RMVF                 : 1;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t OBLRSTF              : 1;
        volatile uint32_t PINRSTF              : 1;
        volatile uint32_t BORRSTF              : 1;
        volatile uint32_t SFTRSTF              : 1;
        volatile uint32_t IWDGRSTF             : 1;
        volatile uint32_t WWDGRSTF             : 1;
        volatile uint32_t LPWRRSTF             : 1;
    } par;

} RCC_CSR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t RESERVED0   : 16;
        volatile uint32_t HSICAL               : 8;
        volatile uint32_t HSITRIM              : 7;
        volatile uint32_t RESERVED1   : 1;
    } par;

} RCC_ICSCR_TypeDef;

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t PLLSRC               : 2;
        volatile uint32_t RESERVED0   : 2;
        volatile uint32_t PLLM                 : 4;
        volatile uint32_t PLLN                 : 7;
        volatile uint32_t RESERVED1   : 1;
        volatile uint32_t PLLPEN               : 1;
        volatile uint32_t PLLP                 : 1;
        volatile uint32_t RESERVED2   : 2;
        volatile uint32_t PLLQEN               : 1;
        volatile uint32_t PLLQ                 : 2;
        volatile uint32_t RESERVED3   : 1;
        volatile uint32_t PLLREN               : 1;
        volatile uint32_t PLLR                 : 2;
        volatile uint32_t PLLPDIV              : 5;
    } par;

} RCC_PLLCFGR_TypeDef;

typedef struct
{
	RCC_CR_TypeDef CR;
	RCC_ICSCR_TypeDef ICSCR;
	RCC_CFGR_TypeDef CFGR;
	RCC_PLLCFGR_TypeDef PLLCFGR;
	volatile uint32_t RESERVED0;
	volatile uint32_t RESERVED1;
	RCC_CIER_TypeDef CIER;
	RCC_CIFR_TypeDef CIFR;
	RCC_CICR_TypeDef CICR;
	volatile uint32_t RESERVED2;
	RCC_AHB1RSTR_TypeDef AHB1RSTR;
	RCC_AHB2RSTR_TypeDef AHB2RSTR;
	RCC_AHB3RSTR_TypeDef AHB3RSTR;
	volatile uint32_t RESERVED3;
	RCC_APB1RSTR1_TypeDef APB1RSTR1;
	RCC_APB1RSTR2_TypeDef APB1RSTR2;
	RCC_APB2RSTR_TypeDef APB2RSTR;
	volatile uint32_t RESERVED4;
	RCC_AHB1ENR_TypeDef AHB1ENR;
	RCC_AHB2ENR_TypeDef AHB2ENR;
	RCC_AHB3ENR_TypeDef AHB3ENR;
	volatile uint32_t RESERVED5;
	RCC_APB1ENR1_TypeDef APB1ENR1;
	RCC_APB1ENR2_TypeDef APB1ENR2;
	RCC_APB2ENR_TypeDef APB2ENR;
	volatile uint32_t RESERVED6;
	RCC_AHB1SMENR_TypeDef AHB1SMENR;
	RCC_AHB2SMENR_TypeDef AHB2SMENR;
	RCC_AHB3SMENR_TypeDef AHB3SMENR;
	volatile uint32_t RESERVED7;
	RCC_APB1SMENR1_TypeDef APB1SMENR1;
	RCC_APB1SMENR2_TypeDef APB1SMENR2;
	RCC_APB2SMENR_TypeDef APB2SMENR;
	volatile uint32_t RESERVED8;
	RCC_CCIPR_TypeDef CCIPR;
	volatile uint32_t RESERVED9;
	RCC_BDCR_TypeDef BDCR;
	RCC_CSR_TypeDef CSR;
	RCC_CRRCR_TypeDef CRRCR;
	RCC_CCIPR2_TypeDef CCIPR2;
} RCC_BitField_TypeDef;

#endif

/*** EOF ***/

