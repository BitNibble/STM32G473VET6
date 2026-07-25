//=============================================================================
// rcc_bitfield.h
// STM32G473VET6 RCC Bitfield Definitions
//=============================================================================

#ifndef RCC_BITFIELD_H
	#define RCC_BITFIELD_H
 
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

/*******************************************************************************
 * RCC Clock Control Register (RCC_CR)
 * Offset: 0x00
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t HSION      : 1;   /* [0]    Internal High Speed clock enable */
        volatile uint32_t HSIKERON   : 1;   /* [1]    HSI48 kernel clock enable */
        volatile uint32_t HSIRDY     : 1;   /* [2]    Internal High Speed clock ready */
        volatile uint32_t HSIKERDY   : 1;   /* [3]    HSI kernel clock ready */
        volatile uint32_t HSIDIV     : 2;   /* [5:4]  HSI clock divider */
        volatile uint32_t HSIDIVF    : 1;   /* [6]    HSI divider flag */
        volatile uint32_t RESERVED0  : 1;   /* [7] */

        volatile uint32_t HSEON      : 1;   /* [8]    External High Speed clock enable */
        volatile uint32_t HSERDY     : 1;   /* [9]    External High Speed clock ready */
        volatile uint32_t HSEBYP     : 1;   /* [10]   External High Speed clock bypass */
        volatile uint32_t CSSON      : 1;   /* [11]   Clock Security System enable */

        volatile uint32_t RESERVED1  : 4;   /* [15:12] */

        volatile uint32_t PLLON      : 1;   /* [16]   PLL enable */
        volatile uint32_t PLLRDY     : 1;   /* [17]   PLL clock ready */

        volatile uint32_t RESERVED2  : 14;  /* [31:18] */

    } var;

} RCC_CR_TypeDef;

/*******************************************************************************
 * RCC Internal Clock Sources Calibration Register (RCC_ICSCR)
 * Offset: 0x04
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t HSICAL      : 8;   /* [7:0]   HSI clock calibration */
        volatile uint32_t HSITRIM     : 7;   /* [14:8]  HSI clock trimming */
        volatile uint32_t RESERVED0   : 1;   /* [15] */

        volatile uint32_t MSICAL      : 8;   /* [23:16] MSI clock calibration */
        volatile uint32_t MSITRIM     : 8;   /* [31:24] MSI clock trimming */

    } var;

} RCC_ICSCR_TypeDef;

/*******************************************************************************
 * RCC Clock Configuration Register (RCC_CFGR)
 * Offset: 0x08
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SW         : 2;   /* [1:0]    System clock switch */
        volatile uint32_t SWS        : 2;   /* [3:2]    System clock switch status */

        volatile uint32_t HPRE       : 4;   /* [7:4]    AHB prescaler */

        volatile uint32_t PPRE1      : 3;   /* [10:8]   APB1 prescaler */
        volatile uint32_t PPRE2      : 3;   /* [13:11]  APB2 prescaler */

        volatile uint32_t RESERVED0  : 1;   /* [14] */

        volatile uint32_t MCOSEL     : 4;   /* [18:15]  Microcontroller clock output selection */

        volatile uint32_t MCOPRE     : 3;   /* [21:19]  Microcontroller clock output prescaler */

        volatile uint32_t RESERVED1  : 1;   /* [22] */

        volatile uint32_t STOPWUCK   : 1;   /* [23]     Wake-up from Stop clock selection */

        volatile uint32_t RESERVED2  : 8;   /* [31:24] */

    } var;

} RCC_CFGR_TypeDef;

/*******************************************************************************
 * RCC PLL Configuration Register (RCC_PLLCFGR)
 * Offset: 0x0C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t PLLSRC     : 2;   /* [1:0]    PLL entry clock source */
        volatile uint32_t RESERVED0  : 2;   /* [3:2] */

        volatile uint32_t PLLM       : 4;   /* [7:4]    PLL input divider */

        volatile uint32_t PLLN       : 7;   /* [14:8]   PLL multiplication factor */

        volatile uint32_t RESERVED1  : 1;   /* [15] */

        volatile uint32_t PLLPEN     : 1;   /* [16]     PLLP clock output enable */
        volatile uint32_t PLLP       : 5;   /* [21:17]  PLLP division factor */

        volatile uint32_t PLLQEN     : 1;   /* [22]     PLLQ clock output enable */
        volatile uint32_t PLLQ       : 2;   /* [24:23]  PLLQ division factor */

        volatile uint32_t PLLREN     : 1;   /* [25]     PLLR clock output enable */
        volatile uint32_t PLLR       : 2;   /* [27:26]  PLLR division factor */

        volatile uint32_t RESERVED2  : 4;   /* [31:28] */

    } var;

} RCC_PLLCFGR_TypeDef;

/*******************************************************************************
 * RCC Clock Interrupt Enable Register (RCC_CIER)
 * Offset: 0x18
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYIE   : 1;   /* [0]     LSI ready interrupt enable */
        volatile uint32_t LSERDYIE   : 1;   /* [1]     LSE ready interrupt enable */
        volatile uint32_t HSIRDYIE   : 1;   /* [2]     HSI ready interrupt enable */
        volatile uint32_t HSERDYIE   : 1;   /* [3]     HSE ready interrupt enable */
        volatile uint32_t PLLRDYIE   : 1;   /* [4]     PLL ready interrupt enable */

        volatile uint32_t RESERVED0  : 27;  /* [31:5] */

    } var;

} RCC_CIER_TypeDef;

/*******************************************************************************
 * RCC Clock Interrupt Flag Register (RCC_CIFR)
 * Offset: 0x1C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYF    : 1;   /* [0]     LSI ready interrupt flag */
        volatile uint32_t LSERDYF    : 1;   /* [1]     LSE ready interrupt flag */
        volatile uint32_t HSIRDYF    : 1;   /* [2]     HSI ready interrupt flag */
        volatile uint32_t HSERDYF    : 1;   /* [3]     HSE ready interrupt flag */
        volatile uint32_t PLLRDYF    : 1;   /* [4]     PLL ready interrupt flag */

        volatile uint32_t RESERVED0  : 27;  /* [31:5] */

    } var;

} RCC_CIFR_TypeDef;

/*******************************************************************************
 * RCC Clock Interrupt Clear Register (RCC_CICR)
 * Offset: 0x20
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSIRDYC    : 1;   /* [0]     LSI ready interrupt clear */
        volatile uint32_t LSERDYC    : 1;   /* [1]     LSE ready interrupt clear */
        volatile uint32_t HSIRDYC    : 1;   /* [2]     HSI ready interrupt clear */
        volatile uint32_t HSERDYC    : 1;   /* [3]     HSE ready interrupt clear */
        volatile uint32_t PLLRDYC    : 1;   /* [4]     PLL ready interrupt clear */

        volatile uint32_t RESERVED0  : 27;  /* [31:5] */

    } var;

} RCC_CICR_TypeDef;

/*******************************************************************************
 * RCC AHB1 Peripheral Reset Register (RCC_AHB1RSTR)
 * Offset: 0x28
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1RST    : 1;   /* [0]     DMA1 reset */
        volatile uint32_t DMA2RST    : 1;   /* [1]     DMA2 reset */
        volatile uint32_t DMAMUX1RST : 1;   /* [2]     DMAMUX1 reset */

        volatile uint32_t RESERVED0  : 29;  /* [31:3] */

    } var;

} RCC_AHB1RSTR_TypeDef;

/*******************************************************************************
 * RCC AHB2 Peripheral Reset Register (RCC_AHB2RSTR)
 * Offset: 0x2C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOARST   : 1;   /* [0]     GPIOA reset */
        volatile uint32_t GPIOBRST   : 1;   /* [1]     GPIOB reset */
        volatile uint32_t GPIOCRST   : 1;   /* [2]     GPIOC reset */
        volatile uint32_t GPIODRST   : 1;   /* [3]     GPIOD reset */
        volatile uint32_t GPIOERST   : 1;   /* [4]     GPIOE reset */
        volatile uint32_t GPIOFRST   : 1;   /* [5]     GPIOF reset */
        volatile uint32_t GPIOGRST   : 1;   /* [6]     GPIOG reset */

        volatile uint32_t RESERVED0  : 6;   /* [12:7] */

        volatile uint32_t ADC12RST   : 1;   /* [13]    ADC1/ADC2 reset */
        volatile uint32_t ADC345RST  : 1;   /* [14]    ADC3/ADC4/ADC5 reset */

        volatile uint32_t DAC1RST    : 1;   /* [15]    DAC1 reset */

        volatile uint32_t RESERVED1  : 16;  /* [31:16] */

    } var;

} RCC_AHB2RSTR_TypeDef;

/*******************************************************************************
 * RCC AHB3 Peripheral Reset Register (RCC_AHB3RSTR)
 * Offset: 0x30
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCRST     : 1;   /* [0]     FMC reset */

        volatile uint32_t RESERVED0  : 31;  /* [31:1] */

    } var;

} RCC_AHB3RSTR_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Reset Register 1 (RCC_APB1RSTR1)
 * Offset: 0x38
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2RST      : 1;   /* [0]     TIM2 reset */
        volatile uint32_t TIM3RST      : 1;   /* [1]     TIM3 reset */
        volatile uint32_t TIM4RST      : 1;   /* [2]     TIM4 reset */
        volatile uint32_t TIM5RST      : 1;   /* [3]     TIM5 reset */
        volatile uint32_t TIM6RST      : 1;   /* [4]     TIM6 reset */
        volatile uint32_t TIM7RST      : 1;   /* [5]     TIM7 reset */

        volatile uint32_t RESERVED0    : 2;   /* [7:6] */

        volatile uint32_t CRSRST       : 1;   /* [8]     CRS reset */

        volatile uint32_t RESERVED1    : 2;   /* [10:9] */

        volatile uint32_t RTCAPBRST    : 1;   /* [11]    RTC APB interface reset */
        volatile uint32_t WWDGRST      : 1;   /* [12]    Window watchdog reset */

        volatile uint32_t RESERVED2    : 1;   /* [13] */

        volatile uint32_t SPI2RST      : 1;   /* [14]    SPI2 reset */
        volatile uint32_t SPI3RST      : 1;   /* [15]    SPI3 reset */

        volatile uint32_t USART2RST    : 1;   /* [16]    USART2 reset */
        volatile uint32_t USART3RST    : 1;   /* [17]    USART3 reset */
        volatile uint32_t UART4RST     : 1;   /* [18]    UART4 reset */
        volatile uint32_t UART5RST     : 1;   /* [19]    UART5 reset */

        volatile uint32_t I2C1RST      : 1;   /* [20]    I2C1 reset */
        volatile uint32_t I2C2RST      : 1;   /* [21]    I2C2 reset */

        volatile uint32_t USBRST       : 1;   /* [22]    USB reset */

        volatile uint32_t RESERVED3    : 1;   /* [23] */

        volatile uint32_t FDCANRST     : 1;   /* [24]    FDCAN reset */

        volatile uint32_t RESERVED4    : 3;   /* [27:25] */

        volatile uint32_t PWRRST       : 1;   /* [28]    PWR reset */

        volatile uint32_t RESERVED5    : 2;   /* [30:29] */

        volatile uint32_t LPTIM1RST    : 1;   /* [31]    LPTIM1 reset */

    } var;

} RCC_APB1RSTR1_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Reset Register 2 (RCC_APB1RSTR2)
 * Offset: 0x3C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1RST   : 1;   /* [0]     LPUART1 reset */

        volatile uint32_t RESERVED0    : 3;   /* [3:1] */

        volatile uint32_t I2C3RST      : 1;   /* [4]     I2C3 reset */

        volatile uint32_t RESERVED1    : 3;   /* [7:5] */

        volatile uint32_t LPTIM2RST    : 1;   /* [8]     LPTIM2 reset */

        volatile uint32_t RESERVED2    : 12;  /* [20:9] */

        volatile uint32_t LPUART2RST   : 1;   /* [21]    LPUART2 reset */

        volatile uint32_t RESERVED3    : 10;  /* [31:22] */

    } var;

} RCC_APB1RSTR2_TypeDef;

/*******************************************************************************
 * RCC APB2 Peripheral Reset Register (RCC_APB2RSTR)
 * Offset: 0x40
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGRST    : 1;   /* [0]     SYSCFG reset */

        volatile uint32_t RESERVED0    : 10;  /* [10:1] */

        volatile uint32_t TIM1RST      : 1;   /* [11]    TIM1 reset */
        volatile uint32_t SPI1RST      : 1;   /* [12]    SPI1 reset */
        volatile uint32_t TIM8RST      : 1;   /* [13]    TIM8 reset */
        volatile uint32_t USART1RST    : 1;   /* [14]    USART1 reset */
        volatile uint32_t TIM15RST     : 1;   /* [15]    TIM15 reset */
        volatile uint32_t TIM16RST     : 1;   /* [16]    TIM16 reset */
        volatile uint32_t TIM17RST     : 1;   /* [17]    TIM17 reset */

        volatile uint32_t RESERVED1    : 2;   /* [19:18] */

        volatile uint32_t SAI1RST      : 1;   /* [20]    SAI1 reset */

        volatile uint32_t RESERVED2    : 1;   /* [21] */

        volatile uint32_t HRTIM1RST    : 1;   /* [22]    HRTIM1 reset */

        volatile uint32_t RESERVED3    : 2;   /* [24:23] */

        volatile uint32_t DFSDMRST     : 1;   /* [25]    DFSDM reset */

        volatile uint32_t RESERVED4    : 1;   /* [26] */

        volatile uint32_t ADC5RST      : 1;   /* [27]    ADC5 reset */

        volatile uint32_t RESERVED5    : 4;   /* [31:28] */

    } var;

} RCC_APB2RSTR_TypeDef;

/*******************************************************************************
 * RCC AHB1 Peripheral Clock Enable Register (RCC_AHB1ENR)
 * Offset: 0x48
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1EN      : 1;   /* [0]     DMA1 clock enable */
        volatile uint32_t DMA2EN      : 1;   /* [1]     DMA2 clock enable */
        volatile uint32_t DMAMUX1EN   : 1;   /* [2]     DMAMUX1 clock enable */

        volatile uint32_t RESERVED0   : 29;  /* [31:3] */

    } var;

} RCC_AHB1ENR_TypeDef;

/*******************************************************************************
 * RCC AHB2 Peripheral Clock Enable Register (RCC_AHB2ENR)
 * Offset: 0x4C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOAEN     : 1;   /* [0]     GPIOA clock enable */
        volatile uint32_t GPIOBEN     : 1;   /* [1]     GPIOB clock enable */
        volatile uint32_t GPIOCEN     : 1;   /* [2]     GPIOC clock enable */
        volatile uint32_t GPIODEN     : 1;   /* [3]     GPIOD clock enable */
        volatile uint32_t GPIOEEN     : 1;   /* [4]     GPIOE clock enable */
        volatile uint32_t GPIOFEN     : 1;   /* [5]     GPIOF clock enable */
        volatile uint32_t GPIOGEN     : 1;   /* [6]     GPIOG clock enable */

        volatile uint32_t RESERVED0   : 6;   /* [12:7] */

        volatile uint32_t ADC12EN     : 1;   /* [13]    ADC1/ADC2 clock enable */
        volatile uint32_t ADC345EN    : 1;   /* [14]    ADC3/ADC4/ADC5 clock enable */

        volatile uint32_t DAC1EN      : 1;   /* [15]    DAC1 clock enable */

        volatile uint32_t RESERVED1   : 16;  /* [31:16] */

    } var;

} RCC_AHB2ENR_TypeDef;

/*******************************************************************************
 * RCC AHB3 Peripheral Clock Enable Register (RCC_AHB3ENR)
 * Offset: 0x50
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCEN       : 1;   /* [0]     FMC clock enable */

        volatile uint32_t RESERVED0   : 31;  /* [31:1] */

    } var;

} RCC_AHB3ENR_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Clock Enable Register 1 (RCC_APB1ENR1)
 * Offset: 0x58
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2EN      : 1;   /* [0]     TIM2 clock enable */
        volatile uint32_t TIM3EN      : 1;   /* [1]     TIM3 clock enable */
        volatile uint32_t TIM4EN      : 1;   /* [2]     TIM4 clock enable */
        volatile uint32_t TIM5EN      : 1;   /* [3]     TIM5 clock enable */
        volatile uint32_t TIM6EN      : 1;   /* [4]     TIM6 clock enable */
        volatile uint32_t TIM7EN      : 1;   /* [5]     TIM7 clock enable */

        volatile uint32_t RESERVED0   : 2;   /* [7:6] */

        volatile uint32_t CRSEN       : 1;   /* [8]     CRS clock enable */

        volatile uint32_t RESERVED1   : 2;   /* [10:9] */

        volatile uint32_t RTCAPBEN    : 1;   /* [11]    RTC APB clock enable */
        volatile uint32_t WWDGEN      : 1;   /* [12]    Window watchdog clock enable */

        volatile uint32_t RESERVED2   : 1;   /* [13] */

        volatile uint32_t SPI2EN      : 1;   /* [14]    SPI2 clock enable */
        volatile uint32_t SPI3EN      : 1;   /* [15]    SPI3 clock enable */

        volatile uint32_t USART2EN    : 1;   /* [16]    USART2 clock enable */
        volatile uint32_t USART3EN    : 1;   /* [17]    USART3 clock enable */
        volatile uint32_t UART4EN     : 1;   /* [18]    UART4 clock enable */
        volatile uint32_t UART5EN     : 1;   /* [19]    UART5 clock enable */

        volatile uint32_t I2C1EN      : 1;   /* [20]    I2C1 clock enable */
        volatile uint32_t I2C2EN      : 1;   /* [21]    I2C2 clock enable */

        volatile uint32_t USBEN       : 1;   /* [22]    USB clock enable */

        volatile uint32_t RESERVED3   : 1;   /* [23] */

        volatile uint32_t FDCANEN     : 1;   /* [24]    FDCAN clock enable */

        volatile uint32_t RESERVED4   : 1;   /* [25] */

        volatile uint32_t PWREN       : 1;   /* [26]    Power interface clock enable */
        volatile uint32_t DAC1EN      : 1;   /* [27]    DAC1 clock enable */
        volatile uint32_t OPAMPEN     : 1;   /* [28]    OPAMP clock enable */
        volatile uint32_t LPTIM1EN    : 1;   /* [29]    LPTIM1 clock enable */

        volatile uint32_t RESERVED5   : 2;   /* [31:30] */

    } var;

} RCC_APB1ENR1_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Clock Enable Register 2 (RCC_APB1ENR2)
 * Offset: 0x5C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1EN   : 1;   /* [0]     LPUART1 clock enable */

        volatile uint32_t RESERVED0   : 3;   /* [3:1] */

        volatile uint32_t I2C3EN      : 1;   /* [4]     I2C3 clock enable */

        volatile uint32_t RESERVED1   : 3;   /* [7:5] */

        volatile uint32_t LPTIM2EN    : 1;   /* [8]     LPTIM2 clock enable */

        volatile uint32_t RESERVED2   : 12;  /* [20:9] */

        volatile uint32_t LPUART2EN   : 1;   /* [21]    LPUART2 clock enable */

        volatile uint32_t RESERVED3   : 10;  /* [31:22] */

    } var;

} RCC_APB1ENR2_TypeDef;

/*******************************************************************************
 * RCC APB2 Peripheral Clock Enable Register (RCC_APB2ENR)
 * Offset: 0x60
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGEN    : 1;   /* [0]     SYSCFG clock enable */

        volatile uint32_t RESERVED0   : 10;  /* [10:1] */

        volatile uint32_t TIM1EN      : 1;   /* [11]    TIM1 clock enable */
        volatile uint32_t SPI1EN      : 1;   /* [12]    SPI1 clock enable */
        volatile uint32_t TIM8EN      : 1;   /* [13]    TIM8 clock enable */
        volatile uint32_t USART1EN    : 1;   /* [14]    USART1 clock enable */
        volatile uint32_t TIM15EN     : 1;   /* [15]    TIM15 clock enable */
        volatile uint32_t TIM16EN     : 1;   /* [16]    TIM16 clock enable */
        volatile uint32_t TIM17EN     : 1;   /* [17]    TIM17 clock enable */

        volatile uint32_t RESERVED1   : 2;   /* [19:18] */

        volatile uint32_t SAI1EN      : 1;   /* [20]    SAI1 clock enable */

        volatile uint32_t RESERVED2   : 1;   /* [21] */

        volatile uint32_t HRTIM1EN    : 1;   /* [22]    HRTIM1 clock enable */

        volatile uint32_t RESERVED3   : 2;   /* [24:23] */

        volatile uint32_t DFSDMEN     : 1;   /* [25]    DFSDM clock enable */

        volatile uint32_t RESERVED4   : 1;   /* [26] */

        volatile uint32_t ADC5EN      : 1;   /* [27]    ADC5 clock enable */

        volatile uint32_t RESERVED5   : 4;   /* [31:28] */

    } var;

} RCC_APB2ENR_TypeDef;

/*******************************************************************************
 * RCC AHB1 Peripheral Clock Sleep Enable Register (RCC_AHB1SMENR)
 * Offset: 0x68
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t DMA1SMEN      : 1;   /* [0]     DMA1 clock enable during Sleep mode */
        volatile uint32_t DMA2SMEN      : 1;   /* [1]     DMA2 clock enable during Sleep mode */
        volatile uint32_t DMAMUX1SMEN   : 1;   /* [2]     DMAMUX1 clock enable during Sleep mode */

        volatile uint32_t RESERVED0     : 29;  /* [31:3] */

    } var;

} RCC_AHB1SMENR_TypeDef;

/*******************************************************************************
 * RCC AHB2 Peripheral Clock Sleep Enable Register (RCC_AHB2SMENR)
 * Offset: 0x6C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t GPIOASMEN     : 1;   /* [0]     GPIOA clock enable during Sleep mode */
        volatile uint32_t GPIOBSMEN     : 1;   /* [1]     GPIOB clock enable during Sleep mode */
        volatile uint32_t GPIOCSMEN     : 1;   /* [2]     GPIOC clock enable during Sleep mode */
        volatile uint32_t GPIODSMEN     : 1;   /* [3]     GPIOD clock enable during Sleep mode */
        volatile uint32_t GPIOESMEN     : 1;   /* [4]     GPIOE clock enable during Sleep mode */
        volatile uint32_t GPIOFSMEN     : 1;   /* [5]     GPIOF clock enable during Sleep mode */
        volatile uint32_t GPIOGSMEN     : 1;   /* [6]     GPIOG clock enable during Sleep mode */

        volatile uint32_t RESERVED0     : 6;   /* [12:7] */

        volatile uint32_t ADC12SMEN     : 1;   /* [13]    ADC1/ADC2 clock enable during Sleep mode */
        volatile uint32_t ADC345SMEN    : 1;   /* [14]    ADC3/ADC4/ADC5 clock enable during Sleep mode */

        volatile uint32_t DAC1SMEN      : 1;   /* [15]    DAC1 clock enable during Sleep mode */

        volatile uint32_t RESERVED1     : 16;  /* [31:16] */

    } var;

} RCC_AHB2SMENR_TypeDef;

/*******************************************************************************
 * RCC AHB3 Peripheral Clock Sleep Enable Register (RCC_AHB3SMENR)
 * Offset: 0x70
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t FMCSMEN       : 1;   /* [0]     FMC clock enable during Sleep mode */

        volatile uint32_t RESERVED0     : 31;  /* [31:1] */

    } var;

} RCC_AHB3SMENR_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Clock Sleep Enable Register 1 (RCC_APB1SMENR1)
 * Offset: 0x78
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t TIM2SMEN      : 1;   /* [0]     TIM2 clock enable during Sleep mode */
        volatile uint32_t TIM3SMEN      : 1;   /* [1]     TIM3 clock enable during Sleep mode */
        volatile uint32_t TIM4SMEN      : 1;   /* [2]     TIM4 clock enable during Sleep mode */
        volatile uint32_t TIM5SMEN      : 1;   /* [3]     TIM5 clock enable during Sleep mode */
        volatile uint32_t TIM6SMEN      : 1;   /* [4]     TIM6 clock enable during Sleep mode */
        volatile uint32_t TIM7SMEN      : 1;   /* [5]     TIM7 clock enable during Sleep mode */

        volatile uint32_t RESERVED0     : 2;   /* [7:6] */

        volatile uint32_t CRSSMEN       : 1;   /* [8]     CRS clock enable during Sleep mode */

        volatile uint32_t RESERVED1     : 2;   /* [10:9] */

        volatile uint32_t RTCAPBSMEN    : 1;   /* [11]    RTC APB clock enable during Sleep mode */
        volatile uint32_t WWDGSMEN      : 1;   /* [12]    Window watchdog clock enable during Sleep mode */

        volatile uint32_t RESERVED2     : 1;   /* [13] */

        volatile uint32_t SPI2SMEN      : 1;   /* [14]    SPI2 clock enable during Sleep mode */
        volatile uint32_t SPI3SMEN      : 1;   /* [15]    SPI3 clock enable during Sleep mode */

        volatile uint32_t USART2SMEN    : 1;   /* [16]    USART2 clock enable during Sleep mode */
        volatile uint32_t USART3SMEN    : 1;   /* [17]    USART3 clock enable during Sleep mode */
        volatile uint32_t UART4SMEN     : 1;   /* [18]    UART4 clock enable during Sleep mode */
        volatile uint32_t UART5SMEN     : 1;   /* [19]    UART5 clock enable during Sleep mode */

        volatile uint32_t I2C1SMEN      : 1;   /* [20]    I2C1 clock enable during Sleep mode */
        volatile uint32_t I2C2SMEN      : 1;   /* [21]    I2C2 clock enable during Sleep mode */

        volatile uint32_t USBSMEN       : 1;   /* [22]    USB clock enable during Sleep mode */

        volatile uint32_t RESERVED3     : 1;   /* [23] */

        volatile uint32_t FDCANSMEN     : 1;   /* [24]    FDCAN clock enable during Sleep mode */

        volatile uint32_t RESERVED4     : 1;   /* [25] */

        volatile uint32_t PWRSMEN       : 1;   /* [26]    PWR clock enable during Sleep mode */
        volatile uint32_t DAC1SMEN      : 1;   /* [27]    DAC1 clock enable during Sleep mode */
        volatile uint32_t OPAMPSMEN     : 1;   /* [28]    OPAMP clock enable during Sleep mode */
        volatile uint32_t LPTIM1SMEN    : 1;   /* [29]    LPTIM1 clock enable during Sleep mode */

        volatile uint32_t RESERVED5     : 2;   /* [31:30] */

    } var;

} RCC_APB1SMENR1_TypeDef;

/*******************************************************************************
 * RCC APB1 Peripheral Clock Sleep Enable Register 2 (RCC_APB1SMENR2)
 * Offset: 0x7C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LPUART1SMEN   : 1;   /* [0]     LPUART1 clock enable during Sleep mode */

        volatile uint32_t RESERVED0     : 3;   /* [3:1] */

        volatile uint32_t I2C3SMEN      : 1;   /* [4]     I2C3 clock enable during Sleep mode */

        volatile uint32_t RESERVED1     : 3;   /* [7:5] */

        volatile uint32_t LPTIM2SMEN    : 1;   /* [8]     LPTIM2 clock enable during Sleep mode */

        volatile uint32_t RESERVED2     : 12;  /* [20:9] */

        volatile uint32_t LPUART2SMEN   : 1;   /* [21]    LPUART2 clock enable during Sleep mode */

        volatile uint32_t RESERVED3     : 10;  /* [31:22] */

    } var;

} RCC_APB1SMENR2_TypeDef;

/*******************************************************************************
 * RCC APB2 Peripheral Clock Sleep Enable Register (RCC_APB2SMENR)
 * Offset: 0x80
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t SYSCFGSMEN   : 1;   /* [0]     SYSCFG clock enable during Sleep mode */

        volatile uint32_t RESERVED0    : 10;  /* [10:1] */

        volatile uint32_t TIM1SMEN     : 1;   /* [11]    TIM1 clock enable during Sleep mode */
        volatile uint32_t SPI1SMEN     : 1;   /* [12]    SPI1 clock enable during Sleep mode */
        volatile uint32_t TIM8SMEN     : 1;   /* [13]    TIM8 clock enable during Sleep mode */
        volatile uint32_t USART1SMEN   : 1;   /* [14]    USART1 clock enable during Sleep mode */
        volatile uint32_t TIM15SMEN    : 1;   /* [15]    TIM15 clock enable during Sleep mode */
        volatile uint32_t TIM16SMEN    : 1;   /* [16]    TIM16 clock enable during Sleep mode */
        volatile uint32_t TIM17SMEN    : 1;   /* [17]    TIM17 clock enable during Sleep mode */

        volatile uint32_t RESERVED1    : 2;   /* [19:18] */

        volatile uint32_t SAI1SMEN     : 1;   /* [20]    SAI1 clock enable during Sleep mode */

        volatile uint32_t RESERVED2    : 1;   /* [21] */

        volatile uint32_t HRTIM1SMEN   : 1;   /* [22]    HRTIM1 clock enable during Sleep mode */

        volatile uint32_t RESERVED3    : 2;   /* [24:23] */

        volatile uint32_t DFSDMSMEN    : 1;   /* [25]    DFSDM clock enable during Sleep mode */

        volatile uint32_t RESERVED4    : 1;   /* [26] */

        volatile uint32_t ADC5SMEN     : 1;   /* [27]    ADC5 clock enable during Sleep mode */

        volatile uint32_t RESERVED5    : 4;   /* [31:28] */

    } var;

} RCC_APB2SMENR_TypeDef;

/*******************************************************************************
 * RCC Peripheral Independent Clock Configuration Register (RCC_CCIPR)
 * Offset: 0x88
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t USART1SEL    : 2;   /* [1:0] */
        volatile uint32_t USART2SEL    : 2;   /* [3:2] */
        volatile uint32_t USART3SEL    : 2;   /* [5:4] */
        volatile uint32_t UART4SEL     : 2;   /* [7:6] */
        volatile uint32_t UART5SEL     : 2;   /* [9:8] */
        volatile uint32_t LPUART1SEL   : 2;   /* [11:10] */
        volatile uint32_t I2C1SEL      : 2;   /* [13:12] */
        volatile uint32_t I2C2SEL      : 2;   /* [15:14] */
        volatile uint32_t I2C3SEL      : 2;   /* [17:16] */
        volatile uint32_t LPTIM1SEL    : 2;   /* [19:18] */
        volatile uint32_t SAI1SEL      : 2;   /* [21:20] */
        volatile uint32_t I2S23SEL     : 2;   /* [23:22] */
        volatile uint32_t FDCANSEL     : 2;   /* [25:24] */
        volatile uint32_t CLK48SEL     : 2;   /* [27:26] */
        volatile uint32_t ADC12SEL     : 2;   /* [29:28] */
        volatile uint32_t ADC345SEL    : 2;   /* [31:30] */

    } var;

} RCC_CCIPR_TypeDef;

/*******************************************************************************
 * RCC Backup Domain Control Register (RCC_BDCR)
 * Offset: 0x90
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSEON        : 1;   /* [0] */
        volatile uint32_t LSERDY       : 1;   /* [1] */
        volatile uint32_t LSEBYP       : 1;   /* [2] */
        volatile uint32_t LSEDRV       : 2;   /* [4:3] */
        volatile uint32_t LSECSSON     : 1;   /* [5] */
        volatile uint32_t LSECSSD      : 1;   /* [6] */
        volatile uint32_t RESERVED0    : 1;   /* [7] */
        volatile uint32_t RTCSEL       : 2;   /* [9:8] */
        volatile uint32_t RESERVED1    : 5;   /* [14:10] */
        volatile uint32_t RTCEN        : 1;   /* [15] */
        volatile uint32_t BDRST        : 1;   /* [16] */
        volatile uint32_t RESERVED2    : 7;   /* [23:17] */
        volatile uint32_t LSCOEN       : 1;   /* [24] */
        volatile uint32_t LSCOSEL      : 1;   /* [25] */
        volatile uint32_t RESERVED3    : 6;   /* [31:26] */

    } var;

} RCC_BDCR_TypeDef;

/*******************************************************************************
 * RCC Control and Status Register (RCC_CSR)
 * Offset: 0x94
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t LSION        : 1;   /* [0] */
        volatile uint32_t LSIRDY       : 1;   /* [1] */
        volatile uint32_t RESERVED0    : 21;  /* [22:2] */

        volatile uint32_t RMVF         : 1;   /* [23] */

        volatile uint32_t OBLRSTF      : 1;   /* [24] */
        volatile uint32_t PINRSTF      : 1;   /* [25] */
        volatile uint32_t BORRSTF      : 1;   /* [26] */
        volatile uint32_t SFTRSTF      : 1;   /* [27] */
        volatile uint32_t IWDGRSTF     : 1;   /* [28] */
        volatile uint32_t WWDGRSTF     : 1;   /* [29] */
        volatile uint32_t LPWRRSTF     : 1;   /* [30] */

        volatile uint32_t RESERVED1    : 1;   /* [31] */

    } var;

} RCC_CSR_TypeDef;

/*******************************************************************************
 * RCC Clock Recovery RC Register (RCC_CRRCR)
 * Offset: 0x98
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t HSI48ON      : 1;   /* [0] */
        volatile uint32_t HSI48RDY     : 1;   /* [1] */

        volatile uint32_t RESERVED0    : 30;  /* [31:2] */

    } var;

} RCC_CRRCR_TypeDef;

/*******************************************************************************
 * RCC Peripheral Independent Clock Configuration Register 2 (RCC_CCIPR2)
 * Offset: 0x9C
 ******************************************************************************/

typedef union
{
    volatile uint32_t reg;

    struct
    {
        volatile uint32_t I2C4SEL      : 2;   /* [1:0] */

        volatile uint32_t RESERVED0    : 2;   /* [3:2] */

        volatile uint32_t QSPISEL      : 2;   /* [5:4] */

        volatile uint32_t RESERVED1    : 26;  /* [31:6] */

    } var;

} RCC_CCIPR2_TypeDef;

typedef struct
{
    RCC_CR_TypeDef            CR;             /* 0x0000 */
    RCC_ICSCR_TypeDef         ICSCR;          /* 0x0004 */
    RCC_CFGR_TypeDef          CFGR;           /* 0x0008 */
    RCC_PLLCFGR_TypeDef       PLLCFGR;        /* 0x000C */

    volatile uint32_t         RESERVED0;      /* 0x0010 */

    RCC_CIER_TypeDef          CIER;           /* 0x0018 */
    RCC_CIFR_TypeDef          CIFR;           /* 0x001C */
    RCC_CICR_TypeDef          CICR;           /* 0x0020 */

    volatile uint32_t         RESERVED1;      /* 0x0024 */

    RCC_AHB1RSTR_TypeDef      AHB1RSTR;       /* 0x0028 */
    RCC_AHB2RSTR_TypeDef      AHB2RSTR;       /* 0x002C */
    RCC_AHB3RSTR_TypeDef      AHB3RSTR;       /* 0x0030 */

    volatile uint32_t         RESERVED2;      /* 0x0034 */

    RCC_APB1RSTR1_TypeDef     APB1RSTR1;      /* 0x0038 */
    RCC_APB1RSTR2_TypeDef     APB1RSTR2;      /* 0x003C */
    RCC_APB2RSTR_TypeDef      APB2RSTR;       /* 0x0040 */

    volatile uint32_t         RESERVED3;      /* 0x0044 */

    RCC_AHB1ENR_TypeDef       AHB1ENR;        /* 0x0048 */
    RCC_AHB2ENR_TypeDef       AHB2ENR;        /* 0x004C */
    RCC_AHB3ENR_TypeDef       AHB3ENR;        /* 0x0050 */

    volatile uint32_t         RESERVED4;      /* 0x0054 */

    RCC_APB1ENR1_TypeDef      APB1ENR1;       /* 0x0058 */
    RCC_APB1ENR2_TypeDef      APB1ENR2;       /* 0x005C */
    RCC_APB2ENR_TypeDef       APB2ENR;        /* 0x0060 */

    volatile uint32_t         RESERVED5;      /* 0x0064 */

    RCC_AHB1SMENR_TypeDef     AHB1SMENR;      /* 0x0068 */
    RCC_AHB2SMENR_TypeDef     AHB2SMENR;      /* 0x006C */
    RCC_AHB3SMENR_TypeDef     AHB3SMENR;      /* 0x0070 */

    volatile uint32_t         RESERVED6;      /* 0x0074 */

    RCC_APB1SMENR1_TypeDef    APB1SMENR1;     /* 0x0078 */
    RCC_APB1SMENR2_TypeDef    APB1SMENR2;     /* 0x007C */
    RCC_APB2SMENR_TypeDef     APB2SMENR;      /* 0x0080 */

    volatile uint32_t         RESERVED7;      /* 0x0084 */

    RCC_CCIPR_TypeDef         CCIPR;          /* 0x0088 */

    volatile uint32_t         RESERVED8;      /* 0x008C */

    RCC_BDCR_TypeDef          BDCR;           /* 0x0090 */
    RCC_CSR_TypeDef           CSR;            /* 0x0094 */
    RCC_CRRCR_TypeDef         CRRCR;          /* 0x0098 */
    RCC_CCIPR2_TypeDef        CCIPR2;         /* 0x009C */

} RCC_BitField_TypeDef;

#endif

/*** EOF ***/

