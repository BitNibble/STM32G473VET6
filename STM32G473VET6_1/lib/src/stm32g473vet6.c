/**********************************************************************
Family:   STM32G4xx Universal Accessor Library
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: Fits entire STM32G4 Family (G431, G441, G471, G473, G474, etc.)
Date:     04062026
**********************************************************************/
#include "stm32g473vet6.h"

/******************************************************************
 * CORE
 ******************************************************************/
static CORE_Block core = {
    .nvic      = NVIC,
    .scb       = SCB,
    .systick   = SysTick,
    .dwt       = DWT,
    .itm       = ITM,
    .tpi       = TPI,
    .mpu       = MPU,
    .coredebug = CoreDebug
};

static SYSTEM_Block sys = {
    .rcc    = RCC,
    .flash  = FLASH,
    .pwr    = PWR,
    .syscfg = SYSCFG,
    .crs    = CRS
};

static GPIO_Block gpio = {
    .a = GPIOA,
    .b = GPIOB,
    .c = GPIOC,
#ifdef GPIOD
    .d = GPIOD,
#endif
#ifdef GPIOE
    .e = GPIOE,
#endif
#ifdef GPIOF
    .f = GPIOF,
#endif
#ifdef GPIOG
    .g = GPIOG,
#endif
#ifdef GPIOH
    .h = GPIOH,
#endif
};

static TIM_Block tim = {
    /* Advanced */
    .tim1  = TIM1,
#ifdef TIM8
    .tim8  = TIM8,
#endif
#ifdef TIM20
    .tim20 = TIM20,
#endif

    /* General purpose */
    .tim2  = TIM2,
    .tim3  = TIM3,
#ifdef TIM4
    .tim4  = TIM4,
#endif
#ifdef TIM5
    .tim5  = TIM5,
#endif

    /* Basic */
    .tim6  = TIM6,
    .tim7  = TIM7,

    /* Lite */
    .tim15 = TIM15,
    .tim16 = TIM16,
    .tim17 = TIM17
};

static DMA_Block dma = {
    .dma1     = DMA1,
    .dma1_ch1 = DMA1_Channel1,
    .dma1_ch2 = DMA1_Channel2,
    .dma1_ch3 = DMA1_Channel3,
    .dma1_ch4 = DMA1_Channel4,
    .dma1_ch5 = DMA1_Channel5,
    .dma1_ch6 = DMA1_Channel6,
#ifdef DMA1_Channel7
    .dma1_ch7 = DMA1_Channel7,
#endif

#ifdef DMA2
    .dma2     = DMA2,
    .dma2_ch1 = DMA2_Channel1,
    .dma2_ch2 = DMA2_Channel2,
    .dma2_ch3 = DMA2_Channel3,
    .dma2_ch4 = DMA2_Channel4,
    .dma2_ch5 = DMA2_Channel5,
    .dma2_ch6 = DMA2_Channel6,
#ifdef DMA2_Channel7
    .dma2_ch7 = DMA2_Channel7,
#endif
#endif

    .dmamux1     = DMAMUX1,
    .dmamux1_ch1 = DMAMUX1_Channel0,
    .dmamux1_ch2 = DMAMUX1_Channel1,
    .dmamux1_ch3 = DMAMUX1_Channel2,
    .dmamux1_ch4 = DMAMUX1_Channel3,
    .dmamux1_ch5 = DMAMUX1_Channel4,
    .dmamux1_ch6 = DMAMUX1_Channel5,
#ifdef DMAMUX1_Channel7
    .dmamux1_ch7 = DMAMUX1_Channel6,
#endif
};

static ANALOG_Block analog = {
    .adc1          = ADC1,
#ifdef ADC2
    .adc2          = ADC2,
#endif
#ifdef ADC3
    .adc3          = ADC3,
#endif
#ifdef ADC4
    .adc4          = ADC4,
#endif
#ifdef ADC5
    .adc5          = ADC5,
#endif

    .adc12_common  = ADC12_COMMON,
#ifdef ADC345_COMMON
    .adc345_common = ADC345_COMMON,
#endif

    .dac1          = DAC1,
#ifdef DAC2
    .dac2          = DAC2,
#endif
#ifdef DAC3
    .dac3          = DAC3,
#endif
#ifdef DAC4
    .dac4          = DAC4,
#endif
    .comp          = COMP1,
    .opamp         = OPAMP
};

static COMM_Block comm = {
    .usart1  = USART1,
    .usart2  = USART2,
#ifdef USART3
    .usart3  = USART3,
#endif
#ifdef UART4
    .uart4   = UART4,
#endif
#ifdef UART5
    .uart5   = UART5,
#endif
    .lpuart1 = LPUART1,

    .spi1    = SPI1,
    .spi2    = SPI2,
#ifdef SPI3
    .spi3    = SPI3,
#endif
#ifdef SPI4
    .spi4    = SPI4,
#endif

    .i2c1    = I2C1,
    .i2c2    = I2C2,
#ifdef I2C3
    .i2c3    = I2C3,
#endif
#ifdef I2C4
    .i2c4    = I2C4,
#endif

#ifdef FDCAN1
    .fdcan1  = FDCAN1,
#endif
#ifdef FDCAN2
    .fdcan2  = FDCAN2,
#endif
#ifdef FDCAN3
    .fdcan3  = FDCAN3,
#endif

#ifdef SAI1
    .sai1    = SAI1,
#endif

#ifdef QUADSPI
    .qspi    = QUADSPI,
#endif
};

static EXT_Block ext = {
#ifdef USB
    .usb_fs = USB,
#endif
#ifdef RNG
    .rng    = RNG
#endif
};

static WD_Block wd = {
    .iwdg = IWDG,
    .wwdg = WWDG
};

static MEMORY_Block memory = {
    .crc = CRC,
#ifdef FMC_BANK1_R
    .fmc = FMC_BANK1_R
#endif
};

static EVENT_Block event = {
    .exti      = EXTI,
    .dmamux1   = DMAMUX1,
    .dmamux_rg = DMAMUX1_RequestGenerator0
};

/******************************************************************
 * DEVICE INSTANCE
 ******************************************************************/
static const STM32_DEVICE device = {
    .core   = &core,
    .sys = &sys,
    .gpio   = &gpio,
    .timer  = &tim,
    .dma    = &dma,
    .analog = &analog,
    .comm   = &comm,
    .ext    = &ext,
    .wd     = &wd,
    .memory = &memory,
    .event  = &event,
};

/******************************************************************
 * ACCESS
 ******************************************************************/
const STM32_DEVICE* dev(void)
{
    return &device;
}

/************************** CLOCK QUERY ****************************/
/*=========================================================
  PLL SOURCE
=========================================================*/
inline uint32_t get_pll_source(void)
{
    uint32_t src = get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_Pos);

    /* On G4: 00=No clock, 01=Reserved, 10=HSI16, 11=HSE */
    return (src == 3U) ? HSE_VALUE : HSI_VALUE;
}

/*=========================================================
  PLL CONFIG READBACK
=========================================================*/
inline uint8_t get_pllm(void)
{
    /* PLLM mapping on G4: 0001=/2, 0010=/3... so M = value + 1 */
    uint32_t m = get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLM_Msk, RCC_PLLCFGR_PLLM_Pos);
    return (uint8_t)(m + 1U);
}

inline uint16_t get_plln(void)
{
    return (uint16_t)get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, RCC_PLLCFGR_PLLN_Pos);
}

/* PLLP */
inline uint8_t get_pllp(void)
{
    uint32_t p = get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLP_Msk, RCC_PLLCFGR_PLLP_Pos);
    // Hardware rule: values 0 and 1 are invalid/reserved on STM32G4.
    // If read as 0 or 1, the PLLP output clock path is effectively disabled.
    if (p < 2U) return 0;
    return (uint8_t)p;
}


inline uint8_t get_pllq(void)
{
    /* Output divisor = (value + 1) * 2 */
    uint32_t q = get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk, RCC_PLLCFGR_PLLQ_Pos);
    return (uint8_t)((q + 1U) * 2U);
}

inline uint8_t get_pllr(void)
{
    /* Output divisor = (value + 1) * 2 */
    uint32_t r = get_field_value(dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLR_Msk, RCC_PLLCFGR_PLLR_Pos);
    return (uint8_t)((r + 1U) * 2U);
}

/*=========================================================
  PLL FREQUENCY MODEL
=========================================================*/
inline uint32_t get_pll_vco_in(void)
{
    uint32_t m = get_pllm();
    if (m < 1 || m > 16) return 0;
    return get_pll_source() / m;
}

inline uint32_t get_pll_vco_out(void)
{
    return get_pll_vco_in() * get_plln();
}

inline uint32_t get_pllclk(void)
{
    uint32_t divisor = get_pllr();
    if (divisor == 0) return 0;
    return get_pll_vco_out() / divisor;
}

/*=========================================================
  SYSTEM CLOCK
=========================================================*/
inline uint32_t get_sysclk(void)
{
    uint32_t sws = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_SWS_Msk, RCC_CFGR_SWS_Pos);

    switch (sws)
    {
        case 1:  return HSI_VALUE;
        case 2:  return HSE_VALUE;
        case 3:  return get_pllclk();
        default: return HSI_VALUE;
    }
}

/*=========================================================
  AHB CLOCK (HCLK)
=========================================================*/
inline uint32_t get_hclk(void)
{
    static const uint16_t ahb_presc_table[16] =
    {
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 4, 8, 16, 64, 128, 256, 512
    };

    uint32_t hpre = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_HPRE_Msk, RCC_CFGR_HPRE_Pos);
    return get_sysclk() / ahb_presc_table[hpre & 0x0FU];
}

/*=========================================================
  APB CLOCKS
=========================================================*/
uint8_t get_systickpre(void) {
    uint32_t value = get_field_value(dev()->core->systick->CTRL, SysTick_CTRL_CLKSOURCE_Msk, SysTick_CTRL_CLKSOURCE_Pos);
    return value ? 8 : 1;
}

uint32_t get_systickclk(void) {
    return get_hclk() / get_systickpre();
}

inline uint32_t get_pclk1(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};
    uint32_t ppre1 = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_Pos);
    return get_hclk() / apb_presc[ppre1 & 0x07U];
}

inline uint32_t get_pclk2(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};
    uint32_t ppre2 = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_Pos);
    return get_hclk() / apb_presc[ppre2 & 0x07U];
}

/*=========================================================
  TIMER CLOCKS (STM32G4 RULE)
=========================================================*/
inline uint32_t get_timclk1(void)
{
    uint32_t ppre1 = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_PPRE1_Msk, RCC_CFGR_PPRE1_Pos);
    uint32_t pclk1 = get_pclk1();
    uint32_t apb_div = ((ppre1 & 0x04U) == 0U) ? 1U : 2U;
    return pclk1 * apb_div;
}

inline uint32_t get_timclk2(void)
{
    uint32_t ppre2 = get_field_value(dev()->sys->rcc->CFGR, RCC_CFGR_PPRE2_Msk, RCC_CFGR_PPRE2_Pos);
    uint32_t pclk2 = get_pclk2();
    uint32_t apb_div = ((ppre2 & 0x04U) == 0U) ? 1U : 2U;
    return pclk2 * apb_div;
}

/************************* Generic UTILS ***************************/
U_word writeHLbyte(uint16_t v)
{
    U_word w;
    w.par.h = v >> 8;
    w.par.l = v & 0xFF;
    return w;
}

/************************** GPIO UTILS *****************************/
/*** STM32G473VET6 ***/
#ifndef TWO
	#define TWO 2UL
#endif
#ifndef NIBBLE_BITS
	#define NIBBLE_BITS 4UL
#endif
#ifndef WORD_BITS
	#define WORD_BITS 16UL
#endif
#ifndef DWORD_BITS
	#define DWORD_BITS 32UL
#endif

void GPIO_clock(GPIO_TypeDef* GPIO, uint8_t enable)
{
    uint32_t mask = 0;

    if (GPIO == GPIOA)      mask = RCC_AHB2ENR_GPIOAEN;
    else if (GPIO == GPIOB) mask = RCC_AHB2ENR_GPIOBEN;
    else if (GPIO == GPIOC) mask = RCC_AHB2ENR_GPIOCEN;
    else if (GPIO == GPIOD) mask = RCC_AHB2ENR_GPIODEN;
    else if (GPIO == GPIOE) mask = RCC_AHB2ENR_GPIOEEN;
    else if (GPIO == GPIOF) mask = RCC_AHB2ENR_GPIOFEN;
#ifdef GPIOG
    else if (GPIO == GPIOG) mask = RCC_AHB2ENR_GPIOGEN;
#endif
#ifdef GPIOH
    else if (GPIO == GPIOH) mask = RCC_AHB2ENR_GPIOHEN;
#endif
    else return;

    if (enable)
        dev()->sys->rcc->AHB2ENR |= mask;
    else
    	dev()->sys->rcc->AHB2ENR &= ~mask;
}

void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = pin * BLOCK_SIZE;

		uint32_t temp = GPIO->MODER;
		temp &= ~(BLOCK << Pos);
		temp |= ((uint32_t)mode << Pos);
		GPIO->MODER = temp;
	}
}

void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype )
{
    if(pin < WORD_BITS && otype < TWO){
        uint32_t temp = GPIO->OTYPER;
    	temp &= ~(1UL << pin);
    	temp |= ( (uint32_t)otype << pin );
    	GPIO->OTYPER = temp;
    }
}

void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed )
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = (pin * BLOCK_SIZE);

		uint32_t temp = GPIO->OSPEEDR;
		temp &= ~( BLOCK << Pos );
		temp |= ( (uint32_t)ospeed << Pos );
		GPIO->OSPEEDR = temp;
	}
}

void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd )
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		const uint8_t Pos = (pin * BLOCK_SIZE);

		uint32_t temp = GPIO->PUPDR;
		temp &= ~( BLOCK << Pos );
		temp |= ( (uint32_t)pupd << Pos );
		GPIO->PUPDR = temp;
	}
}

void GPIO_hmoder( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t mode )
{
	if(mode < NIBBLE_BITS) {
		uint32_t hmoder = GPIO->MODER;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for (uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				uint8_t Pos = pin * BLOCK_SIZE;
				hmoder &= ~(BLOCK << Pos);
				hmoder |= ((uint32_t)mode << Pos);
			}
		}
		GPIO->MODER = hmoder;
	}
}

void GPIO_hotype( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t otype )
{
	if(otype < TWO) {
		uint32_t hotype = GPIO->OTYPER;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if(hpin & (1UL << pin)) {
				hotype &= ~(1UL << pin);
				hotype |= ( (uint32_t)otype << pin );
			}
		}
		GPIO->OTYPER = hotype;
	}
}

void GPIO_hospeed( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t ospeed )
{
	if(ospeed < NIBBLE_BITS) {
		uint32_t hospeed = GPIO->OSPEEDR;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				uint8_t Pos = (pin * BLOCK_SIZE);
				hospeed &= ~( BLOCK << Pos );
				hospeed |= ( (uint32_t)ospeed << Pos );
			}
		}
		GPIO->OSPEEDR = hospeed;
	}
}

void GPIO_hpupd( GPIO_TypeDef* GPIO, uint16_t hpin, uint8_t pupd )
{
	if(pupd < NIBBLE_BITS){
		uint32_t hpupd = GPIO->PUPDR;
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
		for(uint8_t pin = 0; pin < WORD_BITS; pin++)
		{
			if (hpin & (1UL << pin)) {
				const uint8_t Pos = (pin * BLOCK_SIZE);
				hpupd &= ~( BLOCK << Pos );
				hpupd |= ( (uint32_t)pupd << Pos );
			}
		}
		GPIO->PUPDR = hpupd;
	}
}

void GPIO_lck(GPIO_TypeDef* GPIO, uint16_t hpin)
{
    uint32_t tmp;

    GPIO->LCKR = hpin | (1UL << 16);
    GPIO->LCKR = hpin;
    GPIO->LCKR = hpin | (1UL << 16);

    tmp = GPIO->LCKR;
    (void)tmp;

    tmp = GPIO->LCKR;
    (void)tmp;
}

void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af )
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    	const uint8_t BLOCK = (1U << BLOCK_SIZE) - 1U;
    	const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
    	const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

    	if(index < TWO){
    	    uint32_t temp = GPIO->AFR[index];
    		temp &= ~( BLOCK << Pos );
    		temp |= ( ((uint32_t)af & BLOCK) << Pos );
    		GPIO->AFR[index] = temp;
    	}
	}
}

inline void set_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    reg->BSRR = hpin;
}
inline void clear_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    // Cast hpin to 32-bit first, then safely shift into the upper 16 bits
    reg->BSRR = ((uint32_t)hpin << WORD_BITS);
}
inline void toggle_hpin(GPIO_TypeDef* reg, uint16_t hpin) {
    reg->ODR ^= hpin;
}
inline void set_pin(GPIO_TypeDef* reg, uint8_t pin) {
    // 1UL guarantees safe, unsigned 32-bit shifting
    reg->BSRR = (1UL << pin);
}
inline void clear_pin(GPIO_TypeDef* reg, uint8_t pin) {
    // Directly shift 1UL to its final destination in the upper BRy half (pin + 16)
    reg->BSRR = (1UL << (pin + WORD_BITS));
}

/************************** FPU ENABLE *****************************/
inline void fpu_enable(void)
{
    /* Enable full access to CP10 and CP11 (FPU) */
    dev()->core->scb->CPACR |= (0xFU << 20);

    /* Optional: instruction barrier */
    __DSB();
    __ISB();
}

/*** EOF ***/
/**
 * Singleton and Multiple Independent instance objects.
 * Enabling an interrupt and not defining its request procedure blocks the program.
 * RCC only gets a clean slate when powered off.
 **/
