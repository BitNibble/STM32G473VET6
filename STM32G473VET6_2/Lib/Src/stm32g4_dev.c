/**********************************************************************
	stm32g4_dev.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G4 Family
**********************************************************************/
#include "stm32g4_dev.h"

/*** clock ***/
static inline uint32_t get_pll_source(void)
{
    uint32_t src = exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_Pos);

    /* On G4: 00=No clock, 01=Reserved, 10=HSI16, 11=HSE */
    return (src == 3U) ? HSE_VALUE : HSI_VALUE;
}

static inline uint8_t get_pllm(void)
{
    /* PLLM mapping on G4: 0001=/2, 0010=/3... so M = value + 1 */
    uint32_t m = exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_Msk, RCC_PLLCFGR_PLLM_Pos);
    return (uint8_t)(m + 1U);
}

static inline uint16_t get_plln(void)
{
    return (uint16_t)exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_Pos);
}

static inline uint8_t get_pllp(void)
{
    uint32_t p = exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk, RCC_PLLCFGR_PLLP_Pos);
    // Hardware rule: values 0 and 1 are invalid/reserved on STM32G4.
    // If read as 0 or 1, the PLLP output clock path is effectively disabled.
    if (p < 2U) return 0;
    return (uint8_t)p;
}

static inline uint8_t get_pllq(void)
{
    /* Output divisor = (value + 1) * 2 */
    uint32_t q = exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk, RCC_PLLCFGR_PLLQ_Pos);
    return (uint8_t)((q + 1U) * 2U);
}

static inline uint8_t get_pllr(void)
{
    /* Output divisor = (value + 1) * 2 */
    uint32_t r = exe()->get_field(RCC->PLLCFGR, RCC_PLLCFGR_PLLR_Msk, RCC_PLLCFGR_PLLR_Pos);
    return (uint8_t)((r + 1U) * 2U);
}

static inline uint32_t get_pll_vco_in(void)
{
    uint32_t m = get_pllm();
    if (m == 0) return 0;
    return get_pll_source() / m;
}

static inline uint32_t get_pll_vco_out(void)
{
    return get_pll_vco_in() * get_plln();
}

static inline uint32_t get_pllclk(void)
{
    uint32_t divisor = get_pllr();
    if (divisor == 0) return 0;
    return get_pll_vco_out() / divisor;
}

static inline uint32_t get_sysclk(void)
{
    uint32_t sws = exe()->get_field(RCC->CFGR, RCC_CFGR_SWS_Msk, RCC_CFGR_SWS_Pos);

    switch (sws)
    {
        case 1:  return HSI_VALUE;
        case 2:  return HSE_VALUE;
        case 3:  return get_pllclk();
        default: return HSI_VALUE;
    }
}

static inline uint32_t get_hclk(void)
{
    static const uint16_t ahb_presc_table[16] =
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 4, 8, 16, 64, 128, 256, 512
    };

    uint32_t hpre = exe()->get_field(RCC->CFGR, RCC_CFGR_HPRE_Msk, RCC_CFGR_HPRE_Pos);
    return get_sysclk() / ahb_presc_table[hpre & 0x0FU];
}

static uint8_t get_systickpre(void) {
    uint32_t value = exe()->get_field(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk, SysTick_CTRL_CLKSOURCE_Pos);
    return value ? 1 : 8; /* Standard ARM Cortex rule: 1 = Core Clock, 0 = External Reference (/8) */
}

static uint32_t get_systickclk(void) {
    return get_hclk() / get_systickpre();
}

static inline uint32_t get_pclk1(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};
    uint32_t ppre1 = exe()->get_field(RCC->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_Pos);
    return get_hclk() / apb_presc[ppre1 & 0x07U];
}

static inline uint32_t get_pclk2(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};
    uint32_t ppre2 = exe()->get_field(RCC->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_Pos);
    return get_hclk() / apb_presc[ppre2 & 0x07U];
}

static inline uint32_t get_timclk1(void)
{
    uint32_t ppre1 = exe()->get_field(RCC->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_Pos);
    /* If APB1 Prescaler is 1, Timer Clock = PCLK1. Otherwise, Timer Clock = HCLK (PCLK1 * Prescaler) */
    if ((ppre1 & 0x04U) == 0U) {
        return get_pclk1();
    }
    return get_hclk();
}

static inline uint32_t get_timclk2(void)
{
    uint32_t ppre2 = exe()->get_field(RCC->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_Pos);
    /* If APB2 Prescaler is 1, Timer Clock = PCLK2. Otherwise, Timer Clock = HCLK (PCLK2 * Prescaler) */
    if ((ppre2 & 0x04U) == 0U) {
        return get_pclk2();
    }
    return get_hclk();
}

static uint32_t get_adc12_hclk(void)
{
    return get_hclk();
}

static inline uint32_t _get_adc12_sel(void)
{
    return exe()->get_field( RCC->CCIPR, RCC_CCIPR_ADC12SEL_Msk, RCC_CCIPR_ADC12SEL_Pos );
}

static uint32_t get_adc12_ker_ck_input(void)
{
    switch (_get_adc12_sel())
    {
        case 0:
            return get_sysclk();

        case 1:
            {
                /* Hardfault protection barrier check against division by zero */
                uint32_t pllp = get_pllp();
                if (pllp == 0) return 0;
                return get_pll_vco_out() / pllp;
            }

        default:
            return 0;
    }
}

static uint32_t get_adc12_ker_ck(void)
{
    uint32_t input = get_adc12_ker_ck_input();
    if (input == 0) return 0;

    uint32_t ckmode = exe()->get_field( ADC12_COMMON->CCR, ADC_CCR_CKMODE_Msk, ADC_CCR_CKMODE_Pos );

    /* PRESC only applies in asynchronous mode */
    if (ckmode == 0)
    {
        /* Added official STM32G4 non-linear ADC clock prescaler lookup array mapping */
        static const uint16_t adc_presc_table[16] = {
            1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256, 256, 256, 256, 256
        };
        uint32_t presc = exe()->get_field( ADC12_COMMON->CCR, ADC_CCR_PRESC_Msk, ADC_CCR_PRESC_Pos );
        return input / adc_presc_table[presc & 0x0FU];
    }

    /* synchronous mode: kernel clock bypassed */
    return input;
}

static uint32_t get_freq_adc12(void)
{
    uint32_t hclk = get_hclk();
    uint32_t ckmode = exe()->get_field( ADC12_COMMON->CCR, ADC_CCR_CKMODE_Msk, ADC_CCR_CKMODE_Pos );

    switch (ckmode)
    {
        case 0: return get_adc12_ker_ck();
        case 1: return hclk;
        case 2: return hclk / 2U;
        case 3: return hclk / 4U;
        default: return 0;
    }
}

/*** enable ***/
static void enable_dev_fpu(void) {
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
    #endif
}
static void enable_dev_battery_charging(void) {
    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_PWREN);
    volatile uint32_t tmpreg = RCC->APB1ENR1 & RCC_APB1ENR1_PWREN;
    (void)tmpreg;
    SET_BIT(PWR->CR4, PWR_CR4_VBRS);
    SET_BIT(PWR->CR4, PWR_CR4_VBE);
    (void)PWR->CR4;
}

static void enable_dev_peripheral(const void *peripheral_base) {
    if (peripheral_base == NULL) return;

    /*
     * By casting to a uint32_t, the compiler recognizes these as contiguous
     * hardware base integers and optimizes this block into an instant O(1) jump table.
     */
    switch ((uint32_t)peripheral_base) {
        /* Core Elements */
        case SYSCFG_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);   break;
        case FLASH_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN);     break;

        /* GPIO Subsystems */
        case GPIOA_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);     break;
        case GPIOB_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);     break;
        case GPIOC_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);     break;
        case GPIOD_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN);     break;
        case GPIOE_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);     break;
        case GPIOF_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN);     break;
        case GPIOG_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN);     break;

        /* Core AHB1 Engines */
        case DMA1_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);       break;
        case DMA2_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);       break;
        case DMAMUX1_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN); break;
        case CORDIC_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN);   break;
        case FMAC_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN);       break;
        case CRC_BASE: SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);         break;

        /* Storage Bus Subsystems */
        case QSPI_BASE: SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);       break;
        case FMC_Bank1_R_BASE: SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN); break;

        /* APB2 High Performance Timers */
        case TIM1_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);       break;
        case TIM8_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);       break;
        case TIM15_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN);     break;
        case TIM16_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN);     break;
        case TIM17_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN);     break;
        case TIM20_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN);     break;

        /* APB1 Standard Timers */
        case TIM2_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);     break;
        case TIM3_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);     break;
        case TIM4_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);     break;
        case TIM5_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN);     break;
        case TIM6_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN);     break;
        case TIM7_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN);     break;
        case LPTIM1_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN); break;

        /* Communications Lines Matrix */
        case USART1_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);   break;
        case USART2_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); break;
        case USART3_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); break;
        case UART4_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);   break;
        case UART5_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);   break;

        /* I2C Direct Blocks */
        case I2C1_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);     break;
        case I2C2_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN);     break;
        case I2C3_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN);     break;
        case I2C4_BASE: SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN);     break;

        /* SPI Standard Buses */
        case SPI1_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);       break;
        case SPI2_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN);     break;
        case SPI3_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN);     break;
        case SPI4_BASE: SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);       break;

        /* Interconnectivity Channels */
        case FDCAN1_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN);  break;
        case CRS_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN);       break;
        case USB_BASE: SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN);       break;

        /* Analog Converters Base Elements */
        case ADC1_BASE: /* fallthrough */
        case ADC2_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN);      break;
        case ADC3_BASE: /* fallthrough */
        case ADC4_BASE: /* fallthrough */
        case ADC5_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN);     break;
        case DAC1_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN);       break;
        case DAC2_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN);       break;
        case DAC3_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN);       break;
        case DAC4_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN);       break;
        case RNG_BASE: SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);         break;

        default:                                                         break;
    }

    /* Flush write buffer and stall until RCC bus bridge completes */
    __DSB();
    volatile uint32_t dummy = RCC->APB1ENR1;
    (void)dummy;

}

/*** disable ***/
static void disable_dev_fpu(void)              { SCB->CPACR &= ~((3UL << 10*2)|(3UL << 11*2)); }
static void disable_dev_battery_charging(void) { CLEAR_BIT(PWR->CR4, PWR_CR4_VBE | PWR_CR4_VBRS); }

static void disable_dev_peripheral(const void *peripheral_base) {
    if (peripheral_base == NULL) return;

    /*
     * By casting to a uint32_t, the compiler recognizes these as contiguous
     * hardware base integers and optimizes this block into an instant O(1) jump table.
     */
    switch ((uint32_t)peripheral_base) {
        /* Core Elements */
        case SYSCFG_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);   break;
        case FLASH_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FLASHEN);     break;

        /* GPIO Subsystems */
        case GPIOA_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);     break;
        case GPIOB_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);     break;
        case GPIOC_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);     break;
        case GPIOD_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN);     break;
        case GPIOE_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);     break;
        case GPIOF_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOFEN);     break;
        case GPIOG_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOGEN);     break;

        /* Core AHB1 Engines */
        case DMA1_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);       break;
        case DMA2_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);       break;
        case DMAMUX1_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMAMUX1EN); break;
        case CORDIC_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CORDICEN);   break;
        case FMAC_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_FMACEN);       break;
        case CRC_BASE: CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);         break;

        /* Storage Bus Subsystems */
        case QSPI_BASE: CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);       break;
        case FMC_Bank1_R_BASE: CLEAR_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN); break;

        /* APB2 High Performance Timers */
        case TIM1_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);       break;
        case TIM8_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);       break;
        case TIM15_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM15EN);     break;
        case TIM16_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM16EN);     break;
        case TIM17_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM17EN);     break;
        case TIM20_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM20EN);     break;

        /* APB1 Standard Timers */
        case TIM2_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);     break;
        case TIM3_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);     break;
        case TIM4_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);     break;
        case TIM5_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM5EN);     break;
        case TIM6_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM6EN);     break;
        case TIM7_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM7EN);     break;
        case LPTIM1_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_LPTIM1EN); break;

        /* Communications Lines Matrix */
        case USART1_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);   break;
        case USART2_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN); break;
        case USART3_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN); break;
        case UART4_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);   break;
        case UART5_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);   break;

        /* I2C Direct Blocks */
        case I2C1_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);     break;
        case I2C2_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN);     break;
        case I2C3_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C3EN);     break;
        case I2C4_BASE: CLEAR_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN);     break;

        /* SPI Standard Buses */
        case SPI1_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);       break;
        case SPI2_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN);     break;
        case SPI3_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN);     break;
        case SPI4_BASE: CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);       break;

        /* Interconnectivity Channels */
        case FDCAN1_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_FDCANEN);  break;
        case CRS_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_CRSEN);       break;
        case USB_BASE: CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBEN);       break;

        /* Analog Converters Base Elements */
        case ADC1_BASE: /* fallthrough */
        case ADC2_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN);      break;
        case ADC3_BASE: /* fallthrough */
        case ADC4_BASE: /* fallthrough */
        case ADC5_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADC345EN);     break;
        case DAC1_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC1EN);       break;
        case DAC2_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC2EN);       break;
        case DAC3_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC3EN);       break;
        case DAC4_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DAC4EN);       break;
        case RNG_BASE: CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);         break;

        default:                                                           break;
    }

    /* Force register flush synchronization */
    __DSB();
}

/*** clock ***/
static DEV_get get_setup = {
	.pll_source = get_pll_source,
	.pllm = get_pllm,
	.plln = get_plln,
	.pllp = get_pllp,
	.pllq = get_pllq,
	.pllr = get_pllr,
	.pll_vco_in = get_pll_vco_in,
	.pll_vco_out = get_pll_vco_out,
	.pllclk = get_pllclk,
	.sysclk = get_sysclk,
	.hclk = get_hclk,
	.systickclk = get_systickclk,
	.pclk1 = get_pclk1,
	.pclk2 = get_pclk2,
	.timclk1 = get_timclk1,
	.timclk2 = get_timclk2,
	.adc12_hclk = get_adc12_hclk,
	.adc12_ker_ck_input = get_adc12_ker_ck_input,
	.adc12_ker_ck = get_adc12_ker_ck,
	.freq_adc12 = get_freq_adc12
};

/*** generic ***/
static DEV_run run_setup = {
	.enable_fpu = enable_dev_fpu,
	.enable_battery_charging = enable_dev_battery_charging,
	.disable_fpu = disable_dev_fpu,
	.disable_battery_charging = disable_dev_battery_charging,
};

/*** DEV HANDLER ***/
static DEV_Handle device = {
	.get = &get_setup,
	.enable_peripheral = enable_dev_peripheral,
	.disable_peripheral = disable_dev_peripheral,
	.enable_irq = __NVIC_EnableIRQ,
	.disable_irq = __NVIC_DisableIRQ,
	.irq_setpriority = __NVIC_SetPriority,
	.run = &run_setup
};

/*** DEV ACCESSOR FUNCTION ***/
DEV_Handle* dev(void) { return &device; }

/*** EOF ***/

