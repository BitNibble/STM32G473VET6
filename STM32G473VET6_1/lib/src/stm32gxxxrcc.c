/******************************************************************************
	STM32 GXXX RCC
Author: <sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-G473VET6
Date: 04062026
*******************************************************************************/
/*** File Library ***/
#include "stm32gxxxrcc.h"
#include "armsystick.h"

typedef enum
{
    RCC_CLK_HSI = 1,
    RCC_CLK_HSE = 2,
    RCC_CLK_HSEBYP = 3
} mcu_enable_clk;
typedef enum
{
    RCC_HCLK_HSI = 1,
    RCC_HCLK_HSE = 2,
    RCC_HCLK_PLL = 3
} mcu_select_sysclk;
typedef enum
{
    RCC_CLK_LSI = 1,
    RCC_CLK_LSE = 2,
	RCC_CLK_LSEBYP = 3
} rtc_enable_clk;
typedef enum
{
    RTC_CLK_LSI = 1,
    RTC_CLK_LSE = 2,
	RTC_CLK_HSE = 3
} rtc_select_clk;
/*** File Procedure & Function Header ***/
static void RCC_Flash_SetLatency(uint32_t sysclk);
void STM32GXXX_Rcc_Pwr_Clock(uint8_t state);
void STM32GXXX_Rcc_Write_Enable(void);
void STM32GXXX_Rcc_Write_Disable(void);
void STM32GXXX_Rcc_PLL_Source(uint8_t hclock);
/*** Procedure & Function Header ***/
void STM32GXXX_RCC_nvic(uint8_t state);
/*** RCC Procedure & Function Header ***/
// PLL
void STM32GXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq, uint8_t pllr);
void STM32GXXX_Rcc_PLL_CLK_Enable(void);
void STM32GXXX_Rcc_PLL_SAI1_Enable(void);
// RCC
void STM32GXXX_Rcc_HEnable(uint8_t hclock);
void STM32GXXX_Rcc_HSelect(uint8_t hclock);
void STM32GXXX_Rcc_LEnable(uint8_t lclock);
void STM32GXXX_Rcc_LSelect(uint8_t lclock);
void STM32GXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2);
void STM32GXXX_RTC_ClockSelect(uint8_t rtc);

/*** RCC Procedure & Function Definition ***/
void rcc_start(void)
{
	uint8_t multiply = 120; // (plln >= 8 && plln <= 127)
	uint8_t devide = 2;
    /* Enable primary clock source safely */
    STM32GXXX_Rcc_HEnable(H_Clock_Source);

    /* Select PLL source clock type */
    STM32GXXX_Rcc_PLL_Source(H_Clock_Source);

    uint32_t input = get_pll_source();
    uint32_t pllm = input / 1000000;
    //uint32_t pllm = input / 2000000;
    //uint32_t pllm = input / 4000000;
    //uint32_t pllm = input / 8000000;

    if (pllm < 1)  pllm = 1;
    if (pllm > 16) pllm = 16;

    /* Configure PLL (M, N, P, Q, R) */
    STM32GXXX_PLL_Division((uint8_t)pllm, multiply, 2, 2, devide);

    if (PLL_ON_OFF)
    {
        uint32_t vco = (input / pllm) * multiply;
        uint32_t sysclk = vco / devide;

        /* Flash latency MUST match final target SYSCLK frequency BEFORE switching */
        RCC_Flash_SetLatency(sysclk);

        /* Enable PLL circuit and wait for physical lock */
        STM32GXXX_Rcc_PLL_CLK_Enable();

        /* RCC_HCLK_PLL */
        STM32GXXX_Rcc_HSelect(RCC_HCLK_PLL);
    }
    else
    {
        STM32GXXX_Rcc_HSelect(H_Clock_Source);
    }
    /* (AHB=1, APB1=1, APB2=1) */
    STM32GXXX_Prescaler(1, 1, 1);
    /* SysTick Time Constants */
    systick_Configure();
}

void rcc_start_test(void)
{
    STM32GXXX_Rcc_HEnable(2);
    STM32GXXX_Rcc_HSelect(2);
}
// Latency
static void RCC_Flash_SetLatency(uint32_t sysclk)
{
    uint32_t ws;
    if (sysclk <= 34000000UL)       ws = FLASH_ACR_LATENCY_0WS;
    else if (sysclk <= 68000000UL)  ws = FLASH_ACR_LATENCY_1WS;
    else if (sysclk <= 102000000UL) ws = FLASH_ACR_LATENCY_2WS;
    else if (sysclk <= 136000000UL) ws = FLASH_ACR_LATENCY_3WS;
    else                            ws = FLASH_ACR_LATENCY_4WS;
    set_reg_field_encoded(&dev()->sys->flash->ACR, FLASH_ACR_LATENCY_Msk, ws);
    /* Enable prefetch + caches (G4 recommended setup) */
    set_reg_field_encoded(&dev()->sys->flash->ACR, FLASH_ACR_PRFTEN_Msk, FLASH_ACR_PRFTEN);
    set_reg_field_encoded(&dev()->sys->flash->ACR, FLASH_ACR_ICEN_Msk, FLASH_ACR_ICEN);
    set_reg_field_encoded(&dev()->sys->flash->ACR, FLASH_ACR_DCEN_Msk, FLASH_ACR_DCEN);
}
void STM32GXXX_Rcc_PLL_CLK_Enable(void)
{
    volatile uint32_t timeout = 0x3FFFFF;
    set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_PLLON_Msk, RCC_CR_PLLON);
    while (!get_reg_field_value(dev()->sys->rcc->CR, RCC_CR_PLLRDY_Msk, RCC_CR_PLLRDY_Pos)) {
        if (--timeout == 0) { while (1); }
    }
}
void STM32GXXX_Rcc_Pwr_Clock_Enable(void)
{
    set_reg_field_encoded(&dev()->sys->rcc->APB1ENR1, RCC_APB1ENR1_PWREN_Msk, RCC_APB1ENR1_PWREN);
}
void STM32GXXX_Rcc_Pwr_Clock_Disable(void)
{
    set_reg_field_encoded(&dev()->sys->rcc->APB1ENR1, RCC_APB1ENR1_PWREN_Msk, 0U);
}
void STM32GXXX_Rcc_Write_Enable(void)
{
    STM32GXXX_Rcc_Pwr_Clock_Enable();

    set_reg_field_encoded(&dev()->sys->pwr->CR1, PWR_CR1_DBP_Msk, PWR_CR1_DBP);
}
void STM32GXXX_Rcc_Write_Disable(void)
{
    set_reg_field_encoded(&dev()->sys->pwr->CR1, PWR_CR1_DBP_Msk, 0U);
}
// RCC
void STM32GXXX_Rcc_HEnable(uint8_t clock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = clock;
    while(rdy) {
        switch(choice) {
            case RCC_CLK_HSI: // HSION: Internal high-speed clock enable
                if(set) {
                    set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_HSION_Msk, RCC_CR_HSION); // Enable HSI
                    timeout = 0x1FFFFF;
                    set = 0;
                }
                else if(dev()->sys->rcc->CR & RCC_CR_HSIRDY) { // Wait for HSIRDY
                    rdy = 0;
                }
                else {
                    timeout--;
                    if(!timeout){
                        rdy = 0; // Terminate execution to avoid an infinite loop
                    }
                }
            break;
            case RCC_CLK_HSE: // HSEON: External high-speed clock enable
                if(set) {
                    set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_HSEON_Msk, RCC_CR_HSEON); // Enable HSE
                    timeout = 0x1FFFFF;
                    set = 0;
                }
                else if(dev()->sys->rcc->CR & RCC_CR_HSERDY) { // Wait for HSERDY
                    rdy = 0;
                }
                else {
                    timeout--;
                    if(!timeout){
                        choice = RCC_CLK_HSI; set = 1; // Fallback to safe internal HSI
                    }
                }
            break;

            case RCC_CLK_HSEBYP: // HSEBYP: HSE clock bypass
                set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_HSEBYP_Msk, RCC_CR_HSEBYP); // Enable HSE bypass
                choice = RCC_CLK_HSE; // Switch to enabling HSE path
                break;

            default: // Invalid value, default to HSI
                choice = RCC_CLK_HSI;
            break;
        }
    }
    if (choice == RCC_CLK_HSE) {
        if (dev()->sys->rcc->CR & RCC_CR_HSERDY) {
            set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_CSSON_Msk, RCC_CR_CSSON);
        }
    }
}
void STM32GXXX_Rcc_HSelect(uint8_t hclock)
{
	uint32_t choice = RCC_CFGR_SWS_HSI;
	uint32_t timeout = 0x3FFFFF;
		switch(hclock) {
			case RCC_HCLK_HSI: // HSI selected as system clock
				set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSI);
				break;
			case RCC_HCLK_HSE: // HSE oscillator selected as system clock
				set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSE);
				choice = RCC_CFGR_SWS_HSE;
				break;
			case RCC_HCLK_PLL: // PLL_R (Main PLL Output) selected as system clock
			    set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_PLL);
			    choice = RCC_CFGR_SWS_PLL;
			    break;
			default:
				set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_SW_Msk, RCC_CFGR_SW_HSI);
				break;
		}
	while( (_mask(dev()->sys->rcc->CFGR, RCC_CFGR_SWS_Msk) != choice ) && timeout){timeout--;}
}
void STM32GXXX_Rcc_PLL_Source(uint8_t hclock)
{
    /* Disable PLL before configuration */
    set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_PLLON_Msk, 0U);
    while (get_reg_field_value(dev()->sys->rcc->CR, RCC_CR_PLLRDY_Msk, RCC_CR_PLLRDY_Pos));

    switch (hclock) {
        case RCC_CLK_HSI: /* HSI16 as PLL source [2] */
            set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_HSI);
            break;
        case RCC_CLK_HSE: /* HSE as PLL source [3] */
            set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_HSE);
            break;
        default: /* fallback to HSI */
            set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLSRC_Msk, RCC_PLLCFGR_PLLSRC_HSI);
            break;
    }
}
void STM32GXXX_Rcc_LEnable(uint8_t lclock)
{
    uint8_t set = 1;
    uint8_t rdy = 1;
    uint32_t timeout;
    uint8_t choice = lclock;
    while(rdy) {
        switch(choice) {
            case RCC_CLK_LSI: // LSION: Internal low-speed oscillator enable
                if(set)
                {
                    dev()->sys->rcc->CSR |= RCC_CSR_LSION; // Enable LSI
                    timeout = 0x1FFFFF;
                    set = 0;
                }
                else if(dev()->sys->rcc->CSR & RCC_CSR_LSIRDY) // Wait for LSIRDY
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
            case RCC_CLK_LSE: // LSEON: External low-speed oscillator enable
                if(set)
                {
                    STM32GXXX_Rcc_Write_Enable();
                    dev()->sys->rcc->BDCR |= RCC_BDCR_LSEON; // Enable LSE
                    STM32GXXX_Rcc_Write_Disable();
                    timeout = 0x1FFFFF;
                    set = 0;
                }
                else if(dev()->sys->rcc->BDCR & RCC_BDCR_LSERDY) // Wait for LSERDY
                {
                    rdy = 0; // LSE ready
                }
                else {
                	timeout--;
                	if(!timeout){
                		choice = RCC_CLK_LSI; set = 1;
                	}
                }
                break;
            case RCC_CLK_LSEBYP: // LSEBYP: External low-speed oscillator bypass
                STM32GXXX_Rcc_Write_Enable();
                dev()->sys->rcc->BDCR |= RCC_BDCR_LSEBYP; // Enable LSE bypass
                STM32GXXX_Rcc_Write_Disable();
                choice = RCC_CLK_LSE; // Switch to enabling LSE
                break;
            default: // Default to enabling LSI (0)
            	choice = RCC_CLK_LSI;
                break;
        }
    }
}
void STM32GXXX_Rcc_LSelect(uint8_t lclock)
{
    STM32GXXX_Rcc_Write_Enable();
    switch (lclock) {
        case RTC_CLK_LSE: /* LSE */
            set_reg_field_encoded(&dev()->sys->rcc->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_0);
            break;
        case RTC_CLK_LSI: /* LSI */
            set_reg_field_encoded(&dev()->sys->rcc->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_1);
            break;
        case RTC_CLK_HSE: /* HSE / 32 */
            set_reg_field_encoded(&dev()->sys->rcc->BDCR, RCC_BDCR_RTCSEL_Msk, 3 << RCC_BDCR_RTCSEL_Pos);
            break;
        default:
            set_reg_field_encoded(&dev()->sys->rcc->BDCR, RCC_BDCR_RTCSEL_Msk, RCC_BDCR_RTCSEL_1);
            break;
    }
    STM32GXXX_Rcc_Write_Disable();
}
void _STM32GXXX_ppre2(uint8_t ppre2)
{
    uint32_t val;
    switch (ppre2) {
        case 1: val = RCC_CFGR_PPRE2_DIV1; break;
        case 2: val = RCC_CFGR_PPRE2_DIV2; break;
        case 4: val = RCC_CFGR_PPRE2_DIV4; break;
        case 8: val = RCC_CFGR_PPRE2_DIV8; break;
        case 16: val = RCC_CFGR_PPRE2_DIV16; break;
        default: val = RCC_CFGR_PPRE2_DIV1; break;
    }
    set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_PPRE2_Msk, val);
}
void _STM32GXXX_ppre1(uint8_t ppre1)
{
    uint32_t val;
    switch (ppre1) {
        case 1: val = RCC_CFGR_PPRE1_DIV1; break;
        case 2: val = RCC_CFGR_PPRE1_DIV2; break;
        case 4: val = RCC_CFGR_PPRE1_DIV4; break;
        case 8: val = RCC_CFGR_PPRE1_DIV8; break;
        case 16: val = RCC_CFGR_PPRE1_DIV16; break;
        default: val = RCC_CFGR_PPRE1_DIV1; break;
    }
    set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_PPRE1_Msk, val);
}
void _STM32GXXX_ahbpre(uint16_t ahbpre)
{
    uint32_t val;
    switch (ahbpre) {
        case 1: val = RCC_CFGR_HPRE_DIV1; break;
        case 2: val = RCC_CFGR_HPRE_DIV2; break;
        case 4: val = RCC_CFGR_HPRE_DIV4; break;
        case 8: val = RCC_CFGR_HPRE_DIV8; break;
        case 16: val = RCC_CFGR_HPRE_DIV16; break;
        case 64: val = RCC_CFGR_HPRE_DIV64; break;
        case 128: val = RCC_CFGR_HPRE_DIV128; break;
        case 256: val = RCC_CFGR_HPRE_DIV256; break;
        case 512: val = RCC_CFGR_HPRE_DIV512; break;
        default: val = RCC_CFGR_HPRE_DIV1; break;
    }
    set_reg_field_encoded(&dev()->sys->rcc->CFGR, RCC_CFGR_HPRE_Msk, val);
}
void STM32GXXX_Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2)
{
    _STM32GXXX_ahbpre(ahbpre);
    _STM32GXXX_ppre2(ppre2);
    _STM32GXXX_ppre1(ppre1);
}
void _STM32GXXX_pllm(uint8_t pllm)
{
    uint32_t val_m;
    if (pllm >= 1 && pllm <= 16) { val_m = pllm - 1; } else { val_m = 0; }
    set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLM_Msk, val_m << RCC_PLLCFGR_PLLM_Pos);
}
void _STM32GXXX_plln(uint8_t plln)
{
	uint32_t val_n;
	if (plln >= 8 && plln <= 127) { val_n = plln; } else { val_n = 16; }
	set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, val_n << RCC_PLLCFGR_PLLN_Pos);
}
void _STM32GXXX_pllp(uint8_t pllp)
{
    uint32_t val_p;
    if (pllp >= 2 && pllp <= 31) { val_p = pllp; } else { val_p = 2; }
    set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLP_Msk, val_p << RCC_PLLCFGR_PLLP_Pos);
}
void _STM32GXXX_pllq(uint8_t pllq)
{
    uint32_t val_q;
    switch (pllq) {
        case 2:  val_q = 0; break;
        case 4:  val_q = 1; break;
        case 6:  val_q = 2; break;
        case 8:  val_q = 3; break;
        default: val_q = 0; break; // Safe default (/2)
    }
    set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk, val_q << RCC_PLLCFGR_PLLQ_Pos);
}
void _STM32GXXX_pllr(uint8_t pllr)
{
    uint32_t val_r;
    switch (pllr) {
		case 2:  val_r = 0; break;
		case 4:  val_r = 1; break;
		case 6:  val_r = 2; break;
		case 8:  val_r = 3; break;
		default: val_r = 0; break; // Safe default (/2)
	}
    set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLR_Msk, val_r << RCC_PLLCFGR_PLLR_Pos);
}
// PLL
void STM32GXXX_PLL_Division(uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq, uint8_t pllr)
{
    /* Disable PLL */
    set_reg_field_encoded(&dev()->sys->rcc->CR, RCC_CR_PLLON_Msk, 0U);
    while (get_reg_field_value(dev()->sys->rcc->CR, RCC_CR_PLLRDY_Msk, RCC_CR_PLLRDY_Pos));

    _STM32GXXX_pllm(pllm);
    _STM32GXXX_plln(plln);
    _STM32GXXX_pllp(pllp);
    _STM32GXXX_pllq(pllq);
    _STM32GXXX_pllr(pllr);
	set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLREN_Msk, RCC_PLLCFGR_PLLREN);
	set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLQEN_Msk, RCC_PLLCFGR_PLLQEN);
	set_reg_field_encoded(&dev()->sys->rcc->PLLCFGR, RCC_PLLCFGR_PLLPEN_Msk, RCC_PLLCFGR_PLLPEN);
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
	.prescaler = STM32GXXX_Prescaler
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

