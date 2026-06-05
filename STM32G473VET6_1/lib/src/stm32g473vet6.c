/**********************************************************************
	STM32G473VET6
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32G473VET6
Date:     04062026
**********************************************************************/
#include "stm32g473vet6.h"

/******************************************************************
 * CORE
 ******************************************************************/
static CORE_Block core = {
    .nvic = NVIC,
    .scb = SCB,
    .systick = SysTick,
    .dwt = DWT,
    .itm = ITM,
	.tpi = TPI,
	.mpu = MPU,
	.coredebug = CoreDebug
};

static SYSTEM_Block system = {
    .rcc = RCC,
    .flash = FLASH,
    .pwr = PWR,
    .syscfg = SYSCFG,
	.crs = CRS
};

static GPIO_Block gpio = {
    .a = GPIOA,
    .b = GPIOB,
    .c = GPIOC,
    .d = GPIOD,
    .e = GPIOE,
    .f = GPIOF,
    .g = GPIOG,
    .h = NULL
};

static TIM_Block tim = {
    .tim1 = TIM1,
    .tim8 = TIM8,

    .tim2 = TIM2,
    .tim3 = TIM3,
    .tim4 = TIM4,
    .tim5 = TIM5,

    .tim6 = TIM6,
    .tim7 = TIM7,

    .tim9 = NULL,
    .tim10 = NULL,
    .tim11 = NULL,

    .tim12 = NULL,
    .tim13 = NULL,
    .tim14 = NULL,

    .tim15 = TIM15,
    .tim16 = TIM16,
    .tim17 = TIM17,

    .tim20 = NULL   // G4/H7 high-end
};

static DMA_Block dma = {
	.dma1 = DMA1,
	.dma1_ch1 = DMA1_Channel1,
	.dma1_ch2 = DMA1_Channel2,
	.dma1_ch3 = DMA1_Channel3,
	.dma1_ch4 = DMA1_Channel4,
	.dma1_ch5 = DMA1_Channel5,
	.dma1_ch6 = DMA1_Channel6,
	.dma1_ch7 = DMA1_Channel7,

	.dma2 = DMA2,
	.dma2_ch1 = DMA2_Channel1,
	.dma2_ch2 = DMA2_Channel2,
	.dma2_ch3 = DMA2_Channel3,
	.dma2_ch4 = DMA2_Channel4,
	.dma2_ch5 = DMA2_Channel5,
	.dma2_ch6 = DMA2_Channel6,
	.dma2_ch7 = DMA2_Channel7,

	.dmamux1 = DMAMUX1,
	.dmamux1_ch1 = DMAMUX1_Channel0,
	.dmamux1_ch2 = DMAMUX1_Channel1,
	.dmamux1_ch3 = DMAMUX1_Channel2,
	.dmamux1_ch4 = DMAMUX1_Channel3,
	.dmamux1_ch5 = DMAMUX1_Channel4,
	.dmamux1_ch6 = DMAMUX1_Channel5,
	.dmamux1_ch7 = DMAMUX1_Channel6
};

static ANALOG_Block analog = {
    .adc1 = ADC1,
    .adc2 = ADC2,
    .adc3 = ADC3,

    .adc12_common = ADC12_COMMON,
    .adc345_common = ADC345_COMMON,

    .dac1 = DAC1,
    .comp = COMP1,
    .opamp = OPAMP
};

static COMM_Block comm = {
    .usart1 = USART1,
    .usart2 = USART2,
    .usart3 = USART3,
    .uart4 = UART4,
    .uart5 = UART5,
    .lpuart1 = LPUART1,

    .spi1 = SPI1,
    .spi2 = SPI2,
    .spi3 = SPI3,

    .i2c1 = I2C1,
    .i2c2 = I2C2,
    .i2c3 = I2C3,

    .fdcan1 = FDCAN2,
    .fdcan2 = FDCAN2,

    .sai1 = SAI1,
    .sai2 = NULL,

    .qspi = NULL
};

static EXT_Block ext = {
    .usb_fs = USB,
    //.usb_hs = USB_HS,

    .rng = RNG
    //.eth = ETH,
    //.can1 = CAN1,
    //.fdcan1 = FDCAN1
};

static WD_Block wd = {
    .iwdg = IWDG,
    .wwdg = WWDG
};

static MEMORY_Block memory = {
    .crc = CRC
    //.fmc = FMC
    //.ospi1 = OSPI1,
    //.ospi2 = OSPI2
};

static EVENT_Block event = {
    .exti = EXTI,
    .dmamux1 = DMAMUX1
    //.dmamux_rg = DMAMUX_RG
};

static CLOCK_Block clock = {
    .rcc = RCC,
    .flash = FLASH,
    .pwr = PWR,
};

/******************************************************************
 * DEVICE INSTANCE
 ******************************************************************/
static const STM32_DEVICE device = {
    .core = &core,
	.system = &system,
	.gpio = &gpio,
	.timer = &tim,
	.dma = &dma,
	.analog = &analog,
	.comm = &comm,
	.ext = &ext,
	.wd = &wd,
	.memory = &memory,
	.event = &event,
	.clock =&clock,
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
    uint32_t src = get_reg_field_value(dev()->system->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_Pos);

    return (src) ? HSE_VALUE : HSI_VALUE;
}

/*=========================================================
  PLL CONFIG READBACK
=========================================================*/

inline uint8_t get_pllm(void)
{
    /* PLLM is encoded as (M - 1) */
    uint32_t m = (dev()->system->rcc->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos;
    return (uint8_t)(m + 1U);
}

inline uint16_t get_plln(void)
{
    return (uint16_t)(
        (dev()->system->rcc->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos
    );
}

/* PLLP: fixed mapping /2 /4 /6 /8 */
inline uint8_t get_pllp(void)
{
    uint32_t p = (dev()->system->rcc->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos;

    switch (p)
    {
        case 0: return 2;
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        default: return 2;
    }
}

inline uint8_t get_pllq(void)
{
    /* PLLQ is encoded as (Q - 1) */
    uint32_t q = (dev()->system->rcc->PLLCFGR & RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos;
    return (uint8_t)(q + 1U);
}

inline uint8_t get_pllr(void)
{
    /* PLLR is NOT linear encoded on STM32G4 */
    uint32_t r = (dev()->system->rcc->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos;

    switch (r)
    {
        case 0: return 2;
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        default: return 2;
    }
}


/*=========================================================
  PLL FREQUENCY MODEL
=========================================================*/

inline uint32_t get_pll_vco_in(void)
{
    uint32_t m = get_pllm();
    if (m == 0) return 0;

    return get_pll_source() / m;
}

inline uint32_t get_pll_vco_out(void)
{
    return get_pll_vco_in() * get_plln();
}

inline uint32_t get_pllclk(void)
{
    return get_pll_vco_out() / get_pllr();
}


/*=========================================================
  SYSTEM CLOCK
=========================================================*/

inline uint32_t get_sysclk(void)
{
    uint32_t sws = (dev()->system->rcc->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos;

    switch (sws)
    {
        case 0: return HSI_VALUE;
        case 1: return HSE_VALUE;
        case 2: return get_pllclk();
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
        1, 1, 1, 1,
        1, 1, 1, 1,
        2, 4, 8, 16,
        64, 128, 256, 512
    };

    uint32_t hpre = (dev()->system->rcc->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos;

    return get_sysclk() / ahb_presc_table[hpre];
}


/*=========================================================
  APB CLOCKS
=========================================================*/

inline uint32_t get_pclk1(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};

    uint32_t ppre1 = (dev()->system->rcc->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

    return get_hclk() / apb_presc[ppre1];
}

inline uint32_t get_pclk2(void)
{
    static const uint8_t apb_presc[8] = {1, 1, 1, 1, 2, 4, 8, 16};

    uint32_t ppre2 = (dev()->system->rcc->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;

    return get_hclk() / apb_presc[ppre2];
}


/*=========================================================
  TIMER CLOCKS (STM32G4 RULE)
=========================================================*/

inline uint32_t get_timclk1(void)
{
    uint32_t ppre1 = (dev()->system->rcc->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;
    uint32_t pclk1 = get_pclk1();

    uint32_t apb_div = (ppre1 < 4U) ? 1U : 2U;

    return pclk1 * apb_div;
}

inline uint32_t get_timclk2(void)
{
    uint32_t ppre2 = (dev()->system->rcc->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;
    uint32_t pclk2 = get_pclk2();

    uint32_t apb_div = (ppre2 < 4U) ? 1U : 2U;

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
void GPIO_clock(GPIO_TypeDef* GPIO, uint8_t enable)
{
    uint32_t mask = 0;

    if (GPIO == GPIOA)      mask = RCC_AHB2ENR_GPIOAEN;
    else if (GPIO == GPIOB) mask = RCC_AHB2ENR_GPIOBEN;
    else if (GPIO == GPIOC) mask = RCC_AHB2ENR_GPIOCEN;
    else if (GPIO == GPIOD) mask = RCC_AHB2ENR_GPIODEN;
    else if (GPIO == GPIOE) mask = RCC_AHB2ENR_GPIOEEN;
    else if (GPIO == GPIOF) mask = RCC_AHB2ENR_GPIOFEN;
    else if (GPIO == GPIOG) mask = RCC_AHB2ENR_GPIOGEN;
#ifdef GPIOH
    else if (GPIO == GPIOH) mask = RCC_AHB2ENR_GPIOHEN;
#endif
    else return;

    if (enable)
        dev()->system->rcc->AHB2ENR |= mask;
    else
    	dev()->system->rcc->AHB2ENR &= ~mask;
}
void GPIO_moder( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t mode )
{
	if(pin < WORD_BITS && mode < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1 << BLOCK_SIZE) - 1;
		const uint8_t Pos = pin * BLOCK_SIZE;
		mode &= BLOCK;
		GPIO->MODER &= ~(BLOCK << Pos);
		GPIO->MODER |= (mode << Pos);
	}
}
void GPIO_otype( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t otype )
{
    if(pin < WORD_BITS && otype < TWO){
    	GPIO->OTYPER &= ~(1 << pin);
    	GPIO->OTYPER |= ( otype << pin );
    }
}
void GPIO_ospeed( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t ospeed )
{
	if(pin < WORD_BITS && ospeed < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		ospeed &= BLOCK;
		GPIO->OSPEEDR &= ~( BLOCK << Pos );
		GPIO->OSPEEDR |= ( ospeed << Pos );
	}
}
void GPIO_pupd( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t pupd )
{
	if(pin < WORD_BITS && pupd < NIBBLE_BITS){
		const uint8_t BLOCK_SIZE = TWO;
		const uint8_t BLOCK = (1 << BLOCK_SIZE) - 1;
		const uint16_t Pos = (pin * BLOCK_SIZE);
		pupd &= BLOCK;
		GPIO->PUPDR &= ~( BLOCK << Pos );
		GPIO->PUPDR |= ( pupd << Pos );
	}
}
void GPIO_lck(GPIO_TypeDef* GPIO, uint16_t hpins)
{
    uint32_t tmp;

    GPIO->LCKR = hpins | (1U << 16);
    GPIO->LCKR = hpins;
    GPIO->LCKR = hpins | (1U << 16);

    tmp = GPIO->LCKR;
    (void)tmp;

    tmp = GPIO->LCKR;
    (void)tmp;
}
void GPIO_af( GPIO_TypeDef* GPIO, uint8_t pin, uint8_t af )
{
	if(pin < WORD_BITS && af < WORD_BITS){
		const uint8_t BLOCK_SIZE = NIBBLE_BITS;
    	const uint8_t BLOCK = (1 << BLOCK_SIZE) - 1;
    	const uint8_t index = (pin * BLOCK_SIZE) / DWORD_BITS;
    	const uint16_t Pos = (pin * BLOCK_SIZE) % DWORD_BITS;

    	af &= BLOCK;
    	if(index < TWO){
    		GPIO->AFR[index] &= ~( BLOCK << Pos );
    		GPIO->AFR[index] |= ( af << Pos );
    	}
	}
}
inline void set_hpins(GPIO_TypeDef* reg, uint16_t hpins) {
    reg->BSRR = hpins;
}
inline void clear_hpins(GPIO_TypeDef* reg, uint16_t hpins) {
    reg->BSRR = (uint32_t)(hpins << WORD_BITS);
}
inline void set_pin(GPIO_TypeDef* reg, uint8_t pin) {
    reg->BSRR = (1 << pin);
}
inline void clear_pin(GPIO_TypeDef* reg, uint8_t pin) {
    reg->BSRR = ((uint32_t)(1 << pin)) << WORD_BITS;
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

