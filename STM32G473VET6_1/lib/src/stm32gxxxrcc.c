/******************************************************************************
	STM32 GXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-GXXX
Date: 04062026
*******************************************************************************/
/*** File Library ***/
#include "stm32gxxxrcc.h"

/*** File Procedure & Function Header ***/
static void RCC_Flash_SetLatency(uint32_t sysclk);
void STM32GXXX_Rcc_Pwr_Clock(uint8_t state);
void STM32GXXX_Rcc_Write_Enable(void);
void STM32GXXX_Rcc_Write_Disable(void);
uint8_t STM32GXXX_Rcc_PLL_Select(uint8_t hclock);
/*** Procedure & Function Header ***/
void STM32GXXX_RCC_nvic(uint8_t state);
/*** RCC Procedure & Function Header ***/
// PLL
void STM32GXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq);
void STM32GXXX_Rcc_PLL_CLK_Enable(void);
void STM32GXXX_Rcc_PLL_SAI1_Enable(void);
// RCC
void rcc_start(void);
void STM32GXXX_Rcc_HEnable(uint8_t hclock);
void STM32GXXX_Rcc_HSelect(uint8_t hclock);
void STM32GXXX_Rcc_LEnable(uint8_t lclock);
void STM32GXXX_Rcc_LSelect(uint8_t lclock);
void STM32GXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2);
void STM32GXXX_RTC_ClockSelect(uint8_t rtc);

/*******   0 -> HSI    1->HSE   *********/
#ifndef H_Clock_Source
	#define H_Clock_Source 2
#endif
/****************************************/
/****   PLL ON -> 1    PLL OFF = 0   ****/
#ifndef PLL_ON_OFF
	#define PLL_ON_OFF 0
#endif

/*** RCC Procedure & Function Definition ***/
void rcc_start(void)
{
    /* Enable primary clock source */
    STM32GXXX_Rcc_HEnable(H_Clock_Source);
    //STM32GXXX_Rcc_HEnable(3);

    /* Select PLL source */
    STM32GXXX_Rcc_PLL_Select(H_Clock_Source);
    //STM32GXXX_Rcc_PLL_Select(1);

    /* Derive PLL parameters */
    uint32_t input = get_pll_source();
    uint32_t pllm = input / 1000000UL;

    if (pllm < 2)  pllm = 2;
    if (pllm > 63) pllm = 63;

    /* Configure PLL (must be disabled internally) */
    STM32GXXX_PLL_Division(pllm, 240, 2, 4);

    if (PLL_ON_OFF)
    {
        /* Compute expected SYSCLK (PLLR = 2 assumed) */
        uint32_t vco = (input / pllm) * 240;
        uint32_t sysclk = vco / 2;

        /* Flash latency MUST match final SYSCLK */
        RCC_Flash_SetLatency(sysclk);

        /* Enable PLL */
        STM32GXXX_Rcc_PLL_CLK_Enable();

        /* Switch SYSCLK to PLL (PLLR path) */
        STM32GXXX_Rcc_HSelect(3);
    }
    else
    {
        /* Direct switch to oscillator */
        STM32GXXX_Rcc_HSelect(H_Clock_Source);
        //STM32GXXX_Rcc_HSelect(1);
    }

    /* Set prescalers AFTER SYSCLK is stable (cleaner model) */
    STM32GXXX_Prescaler(1, 1, 1);
    STM32GXXX_RTC_ClockSelect(1);
}

void rcc_start_1(void)
{
    STM32GXXX_Rcc_HEnable(2);

    STM32GXXX_Rcc_HSelect(2);
}
// Latency
static void RCC_Flash_SetLatency(uint32_t sysclk)
{
    uint32_t ws;

    if (sysclk <= 30000000)      ws = FLASH_ACR_LATENCY_0WS;
    else if (sysclk <= 60000000) ws = FLASH_ACR_LATENCY_1WS;
    else if (sysclk <= 90000000) ws = FLASH_ACR_LATENCY_2WS;
    else                          ws = FLASH_ACR_LATENCY_3WS;

    set_reg_Msk_Shifted(&dev()->flash->ACR,
                        FLASH_ACR_LATENCY_Msk,
                        ws);

    /* Enable prefetch + caches (G4 recommended setup) */
    set_reg_Msk_Shifted(&dev()->flash->ACR,
                        FLASH_ACR_PRFTEN_Msk,
                        FLASH_ACR_PRFTEN);

    set_reg_Msk_Shifted(&dev()->flash->ACR,
                        FLASH_ACR_ICEN_Msk,
                        FLASH_ACR_ICEN);

    set_reg_Msk_Shifted(&dev()->flash->ACR,
                        FLASH_ACR_DCEN_Msk,
                        FLASH_ACR_DCEN);
}
void STM32GXXX_Rcc_PLL_CLK_Enable(void)
{
    volatile uint32_t timeout = 0xFFFFFF;

    /* Enable PLL */
    set_reg_Msk_Shifted(&dev()->rcc->CR,
                        RCC_CR_PLLON_Msk,
                        RCC_CR_PLLON);

    /* Wait for PLL ready */
    while (!get_reg_Msk_Pos(dev()->rcc->CR,
                            RCC_CR_PLLRDY_Msk,
                            RCC_CR_PLLRDY_Pos))
    {
        if (--timeout == 0)
        {
            /* fatal system condition in your model */
            while (1);
        }
    }
}
void STM32GXXX_Rcc_Pwr_Clock_Enable(void)
{
    set_reg_Msk_Shifted(&dev()->rcc->APB1ENR1,
                        RCC_APB1ENR1_PWREN_Msk,
                        RCC_APB1ENR1_PWREN);
}

void STM32GXXX_Rcc_Pwr_Clock_Disable(void)
{
    set_reg_Msk_Shifted(&dev()->rcc->APB1ENR1,
                        RCC_APB1ENR1_PWREN_Msk,
                        0U);
}
void STM32GXXX_Rcc_Write_Enable(void)
{
    STM32GXXX_Rcc_Pwr_Clock_Enable();

    set_reg_Msk_Shifted(&dev()->pwr->CR1,
                        PWR_CR1_DBP_Msk,
                        PWR_CR1_DBP);
}
void STM32GXXX_Rcc_Write_Disable(void)
{
    set_reg_Msk_Shifted(&dev()->pwr->CR1,
                        PWR_CR1_DBP_Msk,
                        0U);
}
// RCC
void STM32GXXX_Rcc_HEnable(uint8_t hclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = hclock;

    // Enable CSSON
    if(hclock == 2 || hclock == 3) {
        set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_CSSON_Msk, RCC_CR_CSSON); // Clock security system enable
    }

    while(rdy)
    {
        switch(choice)
        {
            case 1: // HSION: Internal high-speed clock enable
                if(set) {
                	set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSION_Msk, RCC_CR_HSION); // Enable HSI
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CR & RCC_CR_HSIRDY) { // Wait for HSIRDY
                    rdy = 0;
                }
                else {
                	timeout--;
                	if(!timeout){
                		//choice = 1; set = 1;
                		rdy = 0;
                	}
                }
                break;

            case 2: // HSEON: External high-speed clock enable
                if(set) {
                	set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSEON_Msk, RCC_CR_HSEON); // Enable HSE
                    timeout = 0xFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CR & RCC_CR_HSERDY) { // Wait for HSERDY
                    rdy = 0;
                }
                else {
                	timeout--;
                	if(!timeout){
                		choice = 1; set = 1;
                	}
                }
                break;

            case 3: // HSEBYP: HSE clock bypass
                set_reg_Msk_Shifted(&dev()->rcc->CR, RCC_CR_HSEBYP_Msk, RCC_CR_HSEBYP); // Enable HSE bypass
                choice = 2; // Switch to enabling HSE
                break;

            default: // Invalid value, default to HSI
                choice = 1;
                break;
        }
    }
}
void STM32GXXX_Rcc_HSelect(uint8_t hclock)
{
	uint8_t choice = hclock;
	uint8_t verify = 0; uint32_t timeout = 0xFFFFFF;
		switch(choice){
			case 1: // HSI selected as system clock
				set_reg_Msk_Shifted(&dev()->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSI);
				verify = 1;
				break;

			case 2: // HSE oscillator selected as system clock
				set_reg_Msk_Shifted(&dev()->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSE);
				verify = 1;
				break;

			case 3: // PLL_R selected as system clock
				set_reg_Msk_Shifted(&dev()->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);
				verify = 1;
				break;

			default:
				set_reg_Msk_Shifted(&dev()->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSI);
				choice = 1;
				verify = 1;
				break;
		}
	if(verify) { while((get_reg_Msk(dev()->rcc->CFGR, RCC_CFGR_SWS) != choice) && timeout){timeout--;} }
}
uint8_t STM32GXXX_Rcc_PLL_Select(uint8_t hclock)
{
    /* Disable PLL before configuration */
    set_reg_Msk_Shifted(&dev()->rcc->CR,
                        RCC_CR_PLLON_Msk,
                        0U);

    while (get_reg_Msk_Pos(dev()->rcc->CR,
                            RCC_CR_PLLRDY_Msk,
                            RCC_CR_PLLRDY_Pos));

    switch (hclock)
    {
        case 1: /* HSI16 as PLL source */
            set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                                RCC_PLLCFGR_PLLSRC_Msk,
                                RCC_PLLCFGR_PLLSRC_HSI);
            break;

        case 2: /* HSE as PLL source */
            set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                                RCC_PLLCFGR_PLLSRC_Msk,
                                RCC_PLLCFGR_PLLSRC_HSE);
            break;

        default: /* fallback to HSI */
            set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                                RCC_PLLCFGR_PLLSRC_Msk,
                                RCC_PLLCFGR_PLLSRC_HSI);
            break;
    }

    return (uint8_t)get_reg_Msk_Pos(dev()->rcc->PLLCFGR,
                                     RCC_PLLCFGR_PLLSRC_Msk,
                                     RCC_PLLCFGR_PLLSRC_Pos);
}
void STM32GXXX_Rcc_LEnable(uint8_t lclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = lclock;

    while(rdy)
    {
        switch(choice)
        {
            case 1: // LSION: Internal low-speed oscillator enable
                if(set)
                {
                    dev()->rcc->CSR |= RCC_CSR_LSION; // Enable LSI
                    timeout = 0xFFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->CSR & RCC_CSR_LSIRDY) // Wait for LSIRDY
                {
                    rdy = 0; // LSI ready
                }
                else {
                	timeout--;
                	if(!timeout){
                		rdy = 0;
                	}
                }
                break;

            case 2: // LSEON: External low-speed oscillator enable
                if(set)
                {
                    STM32GXXX_Rcc_Write_Enable();
                    dev()->rcc->BDCR |= RCC_BDCR_LSEON; // Enable LSE
                    STM32GXXX_Rcc_Write_Disable();
                    timeout = 0xFFFFFF;
                    set = 0;
                }
                else if(dev()->rcc->BDCR & RCC_BDCR_LSERDY) // Wait for LSERDY
                {
                    rdy = 0; // LSE ready
                }
                else {
                	timeout--;
                	if(!timeout){
                		choice = 1; set = 1;
                	}
                }
                break;

            case 3: // LSEBYP: External low-speed oscillator bypass
                if(set)
                {
                    STM32GXXX_Rcc_Write_Enable();
                    dev()->rcc->BDCR |= RCC_BDCR_LSEBYP; // Enable LSE bypass
                    STM32GXXX_Rcc_Write_Disable();
                }
                choice = 2; // Switch to enabling LSE
                break;

            default: // Default to enabling LSI (0)
            	choice = 1;
                break;
        }
    }
}
void STM32GXXX_Rcc_LSelect(uint8_t lclock)
{
    STM32GXXX_Rcc_Write_Enable();

    switch (lclock)
    {
        case 1: /* LSI */
            set_reg_Msk_Shifted(&dev()->rcc->BDCR,
                                RCC_BDCR_RTCSEL_Msk,
                                2 << RCC_BDCR_RTCSEL_Pos);
            break;

        case 2: /* LSE */
            set_reg_Msk_Shifted(&dev()->rcc->BDCR,
                                RCC_BDCR_RTCSEL_Msk,
								1 << RCC_BDCR_RTCSEL_Pos);
            break;

        case 3: /* HSE / 32 */
            set_reg_Msk_Shifted(&dev()->rcc->BDCR,
                                RCC_BDCR_RTCSEL_Msk,
								3 << RCC_BDCR_RTCSEL_Pos);
            break;

        default:
            set_reg_Msk_Shifted(&dev()->rcc->BDCR,
                                RCC_BDCR_RTCSEL_Msk,
								1 << RCC_BDCR_RTCSEL_Pos);
            break;
    }

    STM32GXXX_Rcc_Write_Disable();
}
void _STM32GXXX_ppre2(uint8_t ppre2)
{
    uint32_t val;

    switch (ppre2)
    {
        case 1:
            val = RCC_CFGR_PPRE2_DIV1;
            break;

        case 2:
            val = RCC_CFGR_PPRE2_DIV2;
            break;

        case 4:
            val = RCC_CFGR_PPRE2_DIV4;
            break;

        case 8:
            val = RCC_CFGR_PPRE2_DIV8;
            break;

        case 16:
            val = RCC_CFGR_PPRE2_DIV16;
            break;

        default:
            val = RCC_CFGR_PPRE2_DIV1;
            break;
    }

    set_reg_Msk_Shifted(&dev()->rcc->CFGR,
                        RCC_CFGR_PPRE2_Msk,
                        val);
}
void _STM32GXXX_ppre1(uint8_t ppre1)
{
    uint32_t val;

    switch (ppre1)
    {
        case 1:
            val = RCC_CFGR_PPRE1_DIV1;
            break;

        case 2:
            val = RCC_CFGR_PPRE1_DIV2;
            break;

        case 4:
            val = RCC_CFGR_PPRE1_DIV4;
            break;

        case 8:
            val = RCC_CFGR_PPRE1_DIV8;
            break;

        case 16:
            val = RCC_CFGR_PPRE1_DIV16;
            break;

        default:
            val = RCC_CFGR_PPRE1_DIV1;
            break;
    }

    set_reg_Msk_Shifted(&dev()->rcc->CFGR,
                        RCC_CFGR_PPRE1_Msk,
                        val);
}
void _STM32GXXX_ahbpre(uint16_t ahbpre)
{
    uint32_t val;

    switch (ahbpre)
    {
        case 1:
            val = RCC_CFGR_HPRE_DIV1;
            break;

        case 2:
            val = RCC_CFGR_HPRE_DIV2;
            break;

        case 4:
            val = RCC_CFGR_HPRE_DIV4;
            break;

        case 8:
            val = RCC_CFGR_HPRE_DIV8;
            break;

        case 16:
            val = RCC_CFGR_HPRE_DIV16;
            break;

        case 64:
            val = RCC_CFGR_HPRE_DIV64;
            break;

        case 128:
            val = RCC_CFGR_HPRE_DIV128;
            break;

        case 256:
            val = RCC_CFGR_HPRE_DIV256;
            break;

        case 512:
            val = RCC_CFGR_HPRE_DIV512;
            break;

        default:
            val = RCC_CFGR_HPRE_DIV1;
            break;
    }

    set_reg_Msk_Shifted(&dev()->rcc->CFGR,
                        RCC_CFGR_HPRE_Msk,
                        val);
}
void STM32GXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2)
{
    /* AHB */
    _STM32GXXX_ahbpre(ahbpre);

    /* APB2 */
    _STM32GXXX_ppre2(ppre2);

    /* APB1 */
    _STM32GXXX_ppre1(ppre1);
}
void STM32GXXX_RTC_ClockSelect(uint8_t rtc)
{
    STM32GXXX_Rcc_Write_Enable();

    uint32_t val = (rtc & 0x3U) << RCC_BDCR_RTCSEL_Pos;

    set_reg_Msk_Shifted(&dev()->rcc->BDCR,
                        RCC_BDCR_RTCSEL_Msk,
                        val);

    STM32GXXX_Rcc_Write_Disable();
}
void _STM32GXXX_pllr(uint8_t pllr)
{
    uint32_t val;

    switch (pllr)
    {
        case 2:
            val = 0;
            break;

        case 4:
            val = 1;
            break;

        case 6:
            val = 2;
            break;

        case 8:
            val = 3;
            break;

        default:
            val = 0;
            break;
    }

    set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                        RCC_PLLCFGR_PLLR_Msk,
                        val << RCC_PLLCFGR_PLLR_Pos);
}
// PLL
void STM32GXXX_PLL_Division(uint8_t pllm,
                            uint16_t plln,
                            uint8_t pllr,
                            uint8_t pllq)
{
    /* Disable PLL */
    set_reg_Msk_Shifted(&dev()->rcc->CR,
                        RCC_CR_PLLON_Msk,
                        0U);

    /* Wait until PLL stops */
    while (get_reg_Msk_Pos(dev()->rcc->CR,
                            RCC_CR_PLLRDY_Msk,
                            RCC_CR_PLLRDY_Pos));

    /* PLLM */
    set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                        RCC_PLLCFGR_PLLM_Msk,
                        (uint32_t)pllm << RCC_PLLCFGR_PLLM_Pos);

    /* PLLN */
    set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                        RCC_PLLCFGR_PLLN_Msk,
                        (uint32_t)plln << RCC_PLLCFGR_PLLN_Pos);

    /* PLLR */
    _STM32GXXX_pllr(pllr);

    /* PLLQ */
    set_reg_Msk_Shifted(&dev()->rcc->PLLCFGR,
                        RCC_PLLCFGR_PLLQ_Msk,
                        (uint32_t)pllq << RCC_PLLCFGR_PLLQ_Pos);
}
/*** RCC Bit Mapping Definition ***/
/*** Other ***/
void STM32GXXX_RCC_nvic(uint8_t state)
{
    if (state)
    {
        NVIC_EnableIRQ(RCC_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(RCC_IRQn);
    }
}
/*** Extended ***/
static STM32GXXX_RCC_PLL STM32GXXX_rcc_pll_setup = {
	.division = STM32GXXX_PLL_Division,
	.enable = STM32GXXX_Rcc_PLL_CLK_Enable
};
/*** HANDLER ***/
static STM32GXXX_RCC_HANDLER STM32GXXX_rcc_setup = {
	.pll = &STM32GXXX_rcc_pll_setup,

	.inic = rcc_start,
	.henable = STM32GXXX_Rcc_HEnable,
	.hselect = STM32GXXX_Rcc_HSelect,
	.lenable = STM32GXXX_Rcc_LEnable,
	.lselect = STM32GXXX_Rcc_LSelect,
	.prescaler = STM32GXXX_Prescaler,

	.nvic = STM32GXXX_RCC_nvic
};

STM32GXXX_RCC_HANDLER* rcc(void){ return &STM32GXXX_rcc_setup; };

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

/*** EOF ***/

