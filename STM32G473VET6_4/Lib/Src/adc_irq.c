/******************************************************************************
	adc_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "stm32x_irq.h"
#include <stm32g4xx.h>

void ADC1_2_IRQHandler(void)
{
    uint32_t isr1 = ADC1->ISR;
    uint32_t isr2 = ADC2->ISR;

    /****************************************************************
     * ADC1
     ****************************************************************/
    /* End Of Conversion */
    if (isr1 & ADC_ISR_EOC)
    {
        ADC1->ISR = ADC_ISR_EOC;
        (void)ADC1->ISR;

        if (irq()->adc->adc1->eoc != NULL)
        {
            irq()->adc->adc1->eoc();
        }
        else
        {
            adc1_eoc_callback();
        }
    }

    /* End Of Sequence */
    if (isr1 & ADC_ISR_EOS)
    {
        ADC1->ISR = ADC_ISR_EOS;
        (void)ADC1->ISR;

        if (irq()->adc->adc1->eos != NULL)
        {
            irq()->adc->adc1->eos();
        }
        else
        {
            adc1_eos_callback();
        }
    }

    /* Analog Watchdog 1 */
    if (isr1 & ADC_ISR_AWD1)
    {
        ADC1->ISR = ADC_ISR_AWD1;
        (void)ADC1->ISR;

        if (irq()->adc->adc1->awd != NULL)
        {
            irq()->adc->adc1->awd();
        }
        else
        {
            adc1_awd_callback();
        }
    }

    /* Overrun */
    if (isr1 & ADC_ISR_OVR)
    {
        ADC1->ISR = ADC_ISR_OVR;
        (void)ADC1->ISR;

        if (irq()->adc->adc1->overrun != NULL)
        {
            irq()->adc->adc1->overrun();
        }
        else
        {
            adc1_overrun_callback();
        }
    }

    /****************************************************************
     * ADC2
     ****************************************************************/
    /* End Of Conversion */
    if (isr2 & ADC_ISR_EOC)
    {
        ADC2->ISR = ADC_ISR_EOC;
        (void)ADC2->ISR;

        if (irq()->adc->adc2->eoc != NULL)
        {
            irq()->adc->adc2->eoc();
        }
        else
        {
            adc2_eoc_callback();
        }
    }

    /* End Of Sequence */
    if (isr2 & ADC_ISR_EOS)
    {
        ADC2->ISR = ADC_ISR_EOS;
        (void)ADC2->ISR;

        if (irq()->adc->adc2->eos != NULL)
        {
            irq()->adc->adc2->eos();
        }
        else
        {
            adc2_eos_callback();
        }
    }

    /* Analog Watchdog 1 */
    if (isr2 & ADC_ISR_AWD1)
    {
        ADC2->ISR = ADC_ISR_AWD1;
        (void)ADC2->ISR;

        if (irq()->adc->adc2->awd != NULL)
        {
            irq()->adc->adc2->awd();
        }
        else
        {
            adc2_awd_callback();
        }
    }

    /* Overrun */
    if (isr2 & ADC_ISR_OVR)
    {
        ADC2->ISR = ADC_ISR_OVR;
        (void)ADC2->ISR;

        if (irq()->adc->adc2->overrun != NULL)
        {
            irq()->adc->adc2->overrun();
        }
        else
        {
            adc2_overrun_callback();
        }
    }
}

void ADC3_IRQHandler(void)
{
    uint32_t isr = ADC3->ISR;

    /* End Of Conversion */
    if (isr & ADC_ISR_EOC)
    {
        ADC3->ISR = ADC_ISR_EOC;
        (void)ADC3->ISR;

        if (irq()->adc->adc3->eoc != NULL)
        {
            irq()->adc->adc3->eoc();
        }
        else
        {
            adc3_eoc_callback();
        }
    }

    /* End Of Sequence */
    if (isr & ADC_ISR_EOS)
    {
        ADC3->ISR = ADC_ISR_EOS;
        (void)ADC3->ISR;

        if (irq()->adc->adc3->eos != NULL)
        {
            irq()->adc->adc3->eos();
        }
        else
        {
            adc3_eos_callback();
        }
    }

    /* Analog Watchdog 1 */
    if (isr & ADC_ISR_AWD1)
    {
        ADC3->ISR = ADC_ISR_AWD1;
        (void)ADC3->ISR;

        if (irq()->adc->adc3->awd != NULL)
        {
            irq()->adc->adc3->awd();
        }
        else
        {
            adc3_awd_callback();
        }
    }

    /* Overrun */
    if (isr & ADC_ISR_OVR)
    {
        ADC3->ISR = ADC_ISR_OVR;
        (void)ADC3->ISR;

        if (irq()->adc->adc3->overrun != NULL)
        {
            irq()->adc->adc3->overrun();
        }
        else
        {
            adc3_overrun_callback();
        }
    }
}

void ADC4_IRQHandler(void)
{
    uint32_t isr = ADC4->ISR;

    /* End Of Conversion */
    if (isr & ADC_ISR_EOC)
    {
        ADC4->ISR = ADC_ISR_EOC;
        (void)ADC4->ISR;

        if (irq()->adc->adc4->eoc != NULL)
        {
            irq()->adc->adc4->eoc();
        }
        else
        {
            adc4_eoc_callback();
        }
    }

    /* End Of Sequence */
    if (isr & ADC_ISR_EOS)
    {
        ADC4->ISR = ADC_ISR_EOS;
        (void)ADC4->ISR;

        if (irq()->adc->adc4->eos != NULL)
        {
            irq()->adc->adc4->eos();
        }
        else
        {
            adc4_eos_callback();
        }
    }

    /* Analog Watchdog 1 */
    if (isr & ADC_ISR_AWD1)
    {
        ADC4->ISR = ADC_ISR_AWD1;
        (void)ADC4->ISR;

        if (irq()->adc->adc4->awd != NULL)
        {
            irq()->adc->adc4->awd();
        }
        else
        {
            adc4_awd_callback();
        }
    }

    /* Overrun */
    if (isr & ADC_ISR_OVR)
    {
        ADC4->ISR = ADC_ISR_OVR;
        (void)ADC4->ISR;

        if (irq()->adc->adc4->overrun != NULL)
        {
            irq()->adc->adc4->overrun();
        }
        else
        {
            adc4_overrun_callback();
        }
    }
}

void ADC5_IRQHandler(void)
{
    uint32_t isr = ADC5->ISR;

    /* End Of Conversion */
    if (isr & ADC_ISR_EOC)
    {
        ADC5->ISR = ADC_ISR_EOC;
        (void)ADC5->ISR;

        if (irq()->adc->adc5->eoc != NULL)
        {
            irq()->adc->adc5->eoc();
        }
        else
        {
            adc5_eoc_callback();
        }
    }

    /* End Of Sequence */
    if (isr & ADC_ISR_EOS)
    {
        ADC5->ISR = ADC_ISR_EOS;
        (void)ADC5->ISR;

        if (irq()->adc->adc5->eos != NULL)
        {
            irq()->adc->adc5->eos();
        }
        else
        {
            adc5_eos_callback();
        }
    }

    /* Analog Watchdog 1 */
    if (isr & ADC_ISR_AWD1)
    {
        ADC5->ISR = ADC_ISR_AWD1;
        (void)ADC5->ISR;

        if (irq()->adc->adc5->awd != NULL)
        {
            irq()->adc->adc5->awd();
        }
        else
        {
            adc5_awd_callback();
        }
    }

    /* Overrun */
    if (isr & ADC_ISR_OVR)
    {
        ADC5->ISR = ADC_ISR_OVR;
        (void)ADC5->ISR;

        if (irq()->adc->adc5->overrun != NULL)
        {
            irq()->adc->adc5->overrun();
        }
        else
        {
            adc5_overrun_callback();
        }
    }
}

/*** EOF ***/
