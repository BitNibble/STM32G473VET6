/******************************************************************************
	dma_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "dma_irq.h"
#include "stm32x_irq.h"
#include <stm32g4xx.h>

/******************************************************************************
 * DMA1
 ******************************************************************************/

/* Channel 1 */
void dma1_ch1_gif_callback(void) {}
void dma1_ch1_tc_callback(void)  {}
void dma1_ch1_ht_callback(void)  {}
void dma1_ch1_te_callback(void)  {}

/* Channel 2 */
void dma1_ch2_gif_callback(void) {}
void dma1_ch2_tc_callback(void)  {}
void dma1_ch2_ht_callback(void)  {}
void dma1_ch2_te_callback(void)  {}

/* Channel 3 */
void dma1_ch3_gif_callback(void) {}
void dma1_ch3_tc_callback(void)  {}
void dma1_ch3_ht_callback(void)  {}
void dma1_ch3_te_callback(void)  {}

/* Channel 4 */
void dma1_ch4_gif_callback(void) {}
void dma1_ch4_tc_callback(void)  {}
void dma1_ch4_ht_callback(void)  {}
void dma1_ch4_te_callback(void)  {}

/* Channel 5 */
void dma1_ch5_gif_callback(void) {}
void dma1_ch5_tc_callback(void)  {}
void dma1_ch5_ht_callback(void)  {}
void dma1_ch5_te_callback(void)  {}

/* Channel 6 */
void dma1_ch6_gif_callback(void) {}
void dma1_ch6_tc_callback(void)  {}
void dma1_ch6_ht_callback(void)  {}
void dma1_ch6_te_callback(void)  {}

/* Channel 7 */
void dma1_ch7_gif_callback(void) {}
void dma1_ch7_tc_callback(void)  {}
void dma1_ch7_ht_callback(void)  {}
void dma1_ch7_te_callback(void)  {}

/******************************************************************************
 * DMA2
 ******************************************************************************/

/* Channel 1 */
void dma2_ch1_gif_callback(void) {}
void dma2_ch1_tc_callback(void)  {}
void dma2_ch1_ht_callback(void)  {}
void dma2_ch1_te_callback(void)  {}

/* Channel 2 */
void dma2_ch2_gif_callback(void) {}
void dma2_ch2_tc_callback(void)  {}
void dma2_ch2_ht_callback(void)  {}
void dma2_ch2_te_callback(void)  {}

/* Channel 3 */
void dma2_ch3_gif_callback(void) {}
void dma2_ch3_tc_callback(void)  {}
void dma2_ch3_ht_callback(void)  {}
void dma2_ch3_te_callback(void)  {}

/* Channel 4 */
void dma2_ch4_gif_callback(void) {}
void dma2_ch4_tc_callback(void)  {}
void dma2_ch4_ht_callback(void)  {}
void dma2_ch4_te_callback(void)  {}

/* Channel 5 */
void dma2_ch5_gif_callback(void) {}
void dma2_ch5_tc_callback(void)  {}
void dma2_ch5_ht_callback(void)  {}
void dma2_ch5_te_callback(void)  {}

/* Channel 6 */
void dma2_ch6_gif_callback(void) {}
void dma2_ch6_tc_callback(void)  {}
void dma2_ch6_ht_callback(void)  {}
void dma2_ch6_te_callback(void)  {}

/* Channel 7 */
void dma2_ch7_gif_callback(void) {}
void dma2_ch7_tc_callback(void)  {}
void dma2_ch7_ht_callback(void)  {}
void dma2_ch7_te_callback(void)  {}

void DMA1_CH1_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF1)
    {
        DMA1->IFCR = DMA_IFCR_CGIF1;

        /* Bus synchronization barrier */
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch1->gif != NULL)
        {
            irq()->dma->dma1->ch1->gif();
        }
        else
        {
            dma1_ch1_gif_callback();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF1)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF1;

        /* Bus synchronization barrier */
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch1->tc != NULL)
        {
            irq()->dma->dma1->ch1->tc();
        }
        else
        {
            dma1_ch1_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF1)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF1;

        /* Bus synchronization barrier */
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch1->ht != NULL)
        {
            irq()->dma->dma1->ch1->ht();
        }
        else
        {
            dma1_ch1_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF1)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF1;

        /* Bus synchronization barrier */
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch1->te != NULL)
        {
            irq()->dma->dma1->ch1->te();
        }
        else
        {
            dma1_ch1_te_callback();
        }
    }
}

void DMA1_CH2_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF2)
    {
        DMA1->IFCR = DMA_IFCR_CGIF2;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch2->gif != NULL)
        {
            irq()->dma->dma1->ch2->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF2)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF2;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch2->tc != NULL)
        {
            irq()->dma->dma1->ch2->tc();
        }
        else
        {
            dma1_ch2_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF2)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF2;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch2->ht != NULL)
        {
            irq()->dma->dma1->ch2->ht();
        }
        else
        {
            dma1_ch2_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF2)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF2;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch2->te != NULL)
        {
            irq()->dma->dma1->ch2->te();
        }
        else
        {
            dma1_ch2_te_callback();
        }
    }
}

void DMA1_CH3_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF3)
    {
        DMA1->IFCR = DMA_IFCR_CGIF3;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch3->gif != NULL)
        {
            irq()->dma->dma1->ch3->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF3)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF3;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch3->tc != NULL)
        {
            irq()->dma->dma1->ch3->tc();
        }
        else
        {
            dma1_ch3_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF3)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF3;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch3->ht != NULL)
        {
            irq()->dma->dma1->ch3->ht();
        }
        else
        {
            dma1_ch3_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF3)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF3;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch3->te != NULL)
        {
            irq()->dma->dma1->ch3->te();
        }
        else
        {
            dma1_ch3_te_callback();
        }
    }
}

void DMA1_CH4_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF4)
    {
        DMA1->IFCR = DMA_IFCR_CGIF4;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch4->gif != NULL)
        {
            irq()->dma->dma1->ch4->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF4)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF4;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch4->tc != NULL)
        {
            irq()->dma->dma1->ch4->tc();
        }
        else
        {
            dma1_ch4_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF4)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF4;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch4->ht != NULL)
        {
            irq()->dma->dma1->ch4->ht();
        }
        else
        {
            dma1_ch4_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF4)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF4;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch4->te != NULL)
        {
            irq()->dma->dma1->ch4->te();
        }
        else
        {
            dma1_ch4_te_callback();
        }
    }
}

void DMA1_CH5_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF5)
    {
        DMA1->IFCR = DMA_IFCR_CGIF5;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch5->gif != NULL)
        {
            irq()->dma->dma1->ch5->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF5)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF5;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch5->tc != NULL)
        {
            irq()->dma->dma1->ch5->tc();
        }
        else
        {
            dma1_ch5_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF5)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF5;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch5->ht != NULL)
        {
            irq()->dma->dma1->ch5->ht();
        }
        else
        {
            dma1_ch5_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF5)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF5;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch5->te != NULL)
        {
            irq()->dma->dma1->ch5->te();
        }
        else
        {
            dma1_ch5_te_callback();
        }
    }
}

void DMA1_CH6_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF6)
    {
        DMA1->IFCR = DMA_IFCR_CGIF6;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch6->gif != NULL)
        {
            irq()->dma->dma1->ch6->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF6)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF6;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch6->tc != NULL)
        {
            irq()->dma->dma1->ch6->tc();
        }
        else
        {
            dma1_ch6_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF6)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF6;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch6->ht != NULL)
        {
            irq()->dma->dma1->ch6->ht();
        }
        else
        {
            dma1_ch6_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF6)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF6;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch6->te != NULL)
        {
            irq()->dma->dma1->ch6->te();
        }
        else
        {
            dma1_ch6_te_callback();
        }
    }
}

void DMA1_CH7_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF7)
    {
        DMA1->IFCR = DMA_IFCR_CGIF7;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch7->gif != NULL)
        {
            irq()->dma->dma1->ch7->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF7)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF7;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch7->tc != NULL)
        {
            irq()->dma->dma1->ch7->tc();
        }
        else
        {
            dma1_ch7_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF7)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF7;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch7->ht != NULL)
        {
            irq()->dma->dma1->ch7->ht();
        }
        else
        {
            dma1_ch7_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF7)
    {
        DMA1->IFCR = DMA_IFCR_CTEIF7;
        (void)DMA1->ISR;

        if (irq()->dma->dma1->ch7->te != NULL)
        {
            irq()->dma->dma1->ch7->te();
        }
        else
        {
            dma1_ch7_te_callback();
        }
    }
}

void DMA2_CH1_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF1)
    {
        DMA2->IFCR = DMA_IFCR_CGIF1;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch1->gif != NULL)
        {
            irq()->dma->dma2->ch1->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF1)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF1;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch1->tc != NULL)
        {
            irq()->dma->dma2->ch1->tc();
        }
        else
        {
            dma2_ch1_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF1)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF1;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch1->ht != NULL)
        {
            irq()->dma->dma2->ch1->ht();
        }
        else
        {
            dma2_ch1_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF1)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF1;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch1->te != NULL)
        {
            irq()->dma->dma2->ch1->te();
        }
        else
        {
            dma2_ch1_te_callback();
        }
    }
}

void DMA2_CH2_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF2)
    {
        DMA2->IFCR = DMA_IFCR_CGIF2;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch2->gif != NULL)
        {
            irq()->dma->dma2->ch2->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF2)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF2;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch2->tc != NULL)
        {
            irq()->dma->dma2->ch2->tc();
        }
        else
        {
            dma2_ch2_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF2)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF2;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch2->ht != NULL)
        {
            irq()->dma->dma2->ch2->ht();
        }
        else
        {
            dma2_ch2_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF2)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF2;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch2->te != NULL)
        {
            irq()->dma->dma2->ch2->te();
        }
        else
        {
            dma2_ch2_te_callback();
        }
    }
}

void DMA2_CH3_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF3)
    {
        DMA2->IFCR = DMA_IFCR_CGIF3;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch3->gif != NULL)
        {
            irq()->dma->dma2->ch3->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF3)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF3;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch3->tc != NULL)
        {
            irq()->dma->dma2->ch3->tc();
        }
        else
        {
            dma2_ch3_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF3)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF3;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch3->ht != NULL)
        {
            irq()->dma->dma2->ch3->ht();
        }
        else
        {
            dma2_ch3_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF3)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF3;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch3->te != NULL)
        {
            irq()->dma->dma2->ch3->te();
        }
        else
        {
            dma2_ch3_te_callback();
        }
    }
}

void DMA2_CH4_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF4)
    {
        DMA2->IFCR = DMA_IFCR_CGIF4;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch4->gif != NULL)
        {
            irq()->dma->dma2->ch4->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF4)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF4;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch4->tc != NULL)
        {
            irq()->dma->dma2->ch4->tc();
        }
        else
        {
            dma2_ch4_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF4)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF4;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch4->ht != NULL)
        {
            irq()->dma->dma2->ch4->ht();
        }
        else
        {
            dma2_ch4_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF4)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF4;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch4->te != NULL)
        {
            irq()->dma->dma2->ch4->te();
        }
        else
        {
            dma2_ch4_te_callback();
        }
    }
}

void DMA2_CH5_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF5)
    {
        DMA2->IFCR = DMA_IFCR_CGIF5;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch5->gif != NULL)
        {
            irq()->dma->dma2->ch5->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF5)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF5;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch5->tc != NULL)
        {
            irq()->dma->dma2->ch5->tc();
        }
        else
        {
            dma2_ch5_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF5)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF5;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch5->ht != NULL)
        {
            irq()->dma->dma2->ch5->ht();
        }
        else
        {
            dma2_ch5_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF5)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF5;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch5->te != NULL)
        {
            irq()->dma->dma2->ch5->te();
        }
        else
        {
            dma2_ch5_te_callback();
        }
    }
}

void DMA2_CH6_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF6)
    {
        DMA2->IFCR = DMA_IFCR_CGIF6;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch6->gif != NULL)
        {
            irq()->dma->dma2->ch6->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF6)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF6;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch6->tc != NULL)
        {
            irq()->dma->dma2->ch6->tc();
        }
        else
        {
            dma2_ch6_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF6)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF6;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch6->ht != NULL)
        {
            irq()->dma->dma2->ch6->ht();
        }
        else
        {
            dma2_ch6_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF6)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF6;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch6->te != NULL)
        {
            irq()->dma->dma2->ch6->te();
        }
        else
        {
            dma2_ch6_te_callback();
        }
    }
}

void DMA2_CH7_IRQHandler(void)
{
    uint32_t isr = DMA2->ISR;

    /****************************************************************
     * Global Interrupt
     ****************************************************************/
    if (isr & DMA_ISR_GIF7)
    {
        DMA2->IFCR = DMA_IFCR_CGIF7;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch7->gif != NULL)
        {
            irq()->dma->dma2->ch7->gif();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & DMA_ISR_TCIF7)
    {
        DMA2->IFCR = DMA_IFCR_CTCIF7;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch7->tc != NULL)
        {
            irq()->dma->dma2->ch7->tc();
        }
        else
        {
            dma2_ch7_tc_callback();
        }
    }

    /****************************************************************
     * Half Transfer
     ****************************************************************/
    if (isr & DMA_ISR_HTIF7)
    {
        DMA2->IFCR = DMA_IFCR_CHTIF7;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch7->ht != NULL)
        {
            irq()->dma->dma2->ch7->ht();
        }
        else
        {
            dma2_ch7_ht_callback();
        }
    }

    /****************************************************************
     * Transfer Error
     ****************************************************************/
    if (isr & DMA_ISR_TEIF7)
    {
        DMA2->IFCR = DMA_IFCR_CTEIF7;
        (void)DMA2->ISR;

        if (irq()->dma->dma2->ch7->te != NULL)
        {
            irq()->dma->dma2->ch7->te();
        }
        else
        {
            dma2_ch7_te_callback();
        }
    }
}

/*** EOF ***/

