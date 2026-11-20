/******************************************************************************
	usart_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "stm32x_irq.h"
#include <stm32g4xx.h>

void USART1_IRQHandler(void)
{
    uint32_t isr = USART1->ISR;
    uint32_t cr1 = USART1->CR1;
    uint32_t cr3 = USART1->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        USART1->ICR = USART_ICR_PECF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->pe != NULL)
        {
            irq()->uart->usart1->pe();
        }
        else
        {
            usart1_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        USART1->ICR = USART_ICR_FECF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->fe != NULL)
        {
            irq()->uart->usart1->fe();
        }
        else
        {
            usart1_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        USART1->ICR = USART_ICR_NECF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->ne != NULL)
        {
            irq()->uart->usart1->ne();
        }
        else
        {
            usart1_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        USART1->ICR = USART_ICR_ORECF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->ore != NULL)
        {
            irq()->uart->usart1->ore();
        }
        else
        {
            usart1_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        USART1->ICR = USART_ICR_IDLECF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->idle != NULL)
        {
            irq()->uart->usart1->idle();
        }
        else
        {
            usart1_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->usart1->rxne != NULL)
        {
            irq()->uart->usart1->rxne();
        }
        else
        {
            usart1_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->usart1->txe != NULL)
        {
            irq()->uart->usart1->txe();
        }
        else
        {
            usart1_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        USART1->ICR = USART_ICR_TCCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->tc != NULL)
        {
            irq()->uart->usart1->tc();
        }
        else
        {
            usart1_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        USART1->ICR = USART_ICR_CTSCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->cts != NULL)
        {
            irq()->uart->usart1->cts();
        }
        else
        {
            usart1_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        USART1->ICR = USART_ICR_RTOCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->rtof != NULL)
        {
            irq()->uart->usart1->rtof();
        }
        else
        {
            usart1_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        USART1->ICR = USART_ICR_EOBCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->eob != NULL)
        {
            irq()->uart->usart1->eob();
        }
        else
        {
            usart1_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        USART1->ICR = USART_ICR_CMCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->cmf != NULL)
        {
            irq()->uart->usart1->cmf();
        }
        else
        {
            usart1_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        USART1->ICR = USART_ICR_WUCF;
        (void)USART1->ISR;

        if (irq()->uart->usart1->wuf != NULL)
        {
            irq()->uart->usart1->wuf();
        }
        else
        {
            usart1_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->usart1->txfe != NULL)
        {
            irq()->uart->usart1->txfe();
        }
        else
        {
            usart1_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->usart1->rxff != NULL)
        {
            irq()->uart->usart1->rxff();
        }
        else
        {
            usart1_rxff_callback();
        }
    }
}

void USART2_IRQHandler(void)
{
    uint32_t isr = USART2->ISR;
    uint32_t cr1 = USART2->CR1;
    uint32_t cr3 = USART2->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        USART2->ICR = USART_ICR_PECF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->pe != NULL)
        {
            irq()->uart->usart2->pe();
        }
        else
        {
            usart2_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        USART2->ICR = USART_ICR_FECF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->fe != NULL)
        {
            irq()->uart->usart2->fe();
        }
        else
        {
            usart2_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        USART2->ICR = USART_ICR_NECF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->ne != NULL)
        {
            irq()->uart->usart2->ne();
        }
        else
        {
            usart2_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        USART2->ICR = USART_ICR_ORECF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->ore != NULL)
        {
            irq()->uart->usart2->ore();
        }
        else
        {
            usart2_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        USART2->ICR = USART_ICR_IDLECF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->idle != NULL)
        {
            irq()->uart->usart2->idle();
        }
        else
        {
            usart2_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->usart2->rxne != NULL)
        {
            irq()->uart->usart2->rxne();
        }
        else
        {
            usart2_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->usart2->txe != NULL)
        {
            irq()->uart->usart2->txe();
        }
        else
        {
            usart2_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        USART2->ICR = USART_ICR_TCCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->tc != NULL)
        {
            irq()->uart->usart2->tc();
        }
        else
        {
            usart2_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        USART2->ICR = USART_ICR_CTSCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->cts != NULL)
        {
            irq()->uart->usart2->cts();
        }
        else
        {
            usart2_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        USART2->ICR = USART_ICR_RTOCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->rtof != NULL)
        {
            irq()->uart->usart2->rtof();
        }
        else
        {
            usart2_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        USART2->ICR = USART_ICR_EOBCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->eob != NULL)
        {
            irq()->uart->usart2->eob();
        }
        else
        {
            usart2_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        USART2->ICR = USART_ICR_CMCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->cmf != NULL)
        {
            irq()->uart->usart2->cmf();
        }
        else
        {
            usart2_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        USART2->ICR = USART_ICR_WUCF;
        (void)USART2->ISR;

        if (irq()->uart->usart2->wuf != NULL)
        {
            irq()->uart->usart2->wuf();
        }
        else
        {
            usart2_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->usart2->txfe != NULL)
        {
            irq()->uart->usart2->txfe();
        }
        else
        {
            usart2_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->usart2->rxff != NULL)
        {
            irq()->uart->usart2->rxff();
        }
        else
        {
            usart2_rxff_callback();
        }
    }
}

void USART3_IRQHandler(void)
{
    uint32_t isr = USART3->ISR;
    uint32_t cr1 = USART3->CR1;
    uint32_t cr3 = USART3->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        USART3->ICR = USART_ICR_PECF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->pe != NULL)
        {
            irq()->uart->usart3->pe();
        }
        else
        {
            usart3_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        USART3->ICR = USART_ICR_FECF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->fe != NULL)
        {
            irq()->uart->usart3->fe();
        }
        else
        {
            usart3_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        USART3->ICR = USART_ICR_NECF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->ne != NULL)
        {
            irq()->uart->usart3->ne();
        }
        else
        {
            usart3_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        USART3->ICR = USART_ICR_ORECF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->ore != NULL)
        {
            irq()->uart->usart3->ore();
        }
        else
        {
            usart3_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        USART3->ICR = USART_ICR_IDLECF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->idle != NULL)
        {
            irq()->uart->usart3->idle();
        }
        else
        {
            usart3_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->usart3->rxne != NULL)
        {
            irq()->uart->usart3->rxne();
        }
        else
        {
            usart3_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->usart3->txe != NULL)
        {
            irq()->uart->usart3->txe();
        }
        else
        {
            usart3_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        USART3->ICR = USART_ICR_TCCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->tc != NULL)
        {
            irq()->uart->usart3->tc();
        }
        else
        {
            usart3_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        USART3->ICR = USART_ICR_CTSCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->cts != NULL)
        {
            irq()->uart->usart3->cts();
        }
        else
        {
            usart3_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        USART3->ICR = USART_ICR_RTOCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->rtof != NULL)
        {
            irq()->uart->usart3->rtof();
        }
        else
        {
            usart3_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        USART3->ICR = USART_ICR_EOBCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->eob != NULL)
        {
            irq()->uart->usart3->eob();
        }
        else
        {
            usart3_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        USART3->ICR = USART_ICR_CMCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->cmf != NULL)
        {
            irq()->uart->usart3->cmf();
        }
        else
        {
            usart3_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        USART3->ICR = USART_ICR_WUCF;
        (void)USART3->ISR;

        if (irq()->uart->usart3->wuf != NULL)
        {
            irq()->uart->usart3->wuf();
        }
        else
        {
            usart3_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->usart3->txfe != NULL)
        {
            irq()->uart->usart3->txfe();
        }
        else
        {
            usart3_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->usart3->rxff != NULL)
        {
            irq()->uart->usart3->rxff();
        }
        else
        {
            usart3_rxff_callback();
        }
    }
}

void UART4_IRQHandler(void)
{
    uint32_t isr = UART4->ISR;
    uint32_t cr1 = UART4->CR1;
    uint32_t cr3 = UART4->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        UART4->ICR = USART_ICR_PECF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->pe != NULL)
        {
            irq()->uart->uart4->pe();
        }
        else
        {
            uart4_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        UART4->ICR = USART_ICR_FECF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->fe != NULL)
        {
            irq()->uart->uart4->fe();
        }
        else
        {
            uart4_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        UART4->ICR = USART_ICR_NECF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->ne != NULL)
        {
            irq()->uart->uart4->ne();
        }
        else
        {
            uart4_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        UART4->ICR = USART_ICR_ORECF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->ore != NULL)
        {
            irq()->uart->uart4->ore();
        }
        else
        {
            uart4_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        UART4->ICR = USART_ICR_IDLECF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->idle != NULL)
        {
            irq()->uart->uart4->idle();
        }
        else
        {
            uart4_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->uart4->rxne != NULL)
        {
            irq()->uart->uart4->rxne();
        }
        else
        {
            uart4_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->uart4->txe != NULL)
        {
            irq()->uart->uart4->txe();
        }
        else
        {
            uart4_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        UART4->ICR = USART_ICR_TCCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->tc != NULL)
        {
            irq()->uart->uart4->tc();
        }
        else
        {
            uart4_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        UART4->ICR = USART_ICR_CTSCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->cts != NULL)
        {
            irq()->uart->uart4->cts();
        }
        else
        {
            uart4_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        UART4->ICR = USART_ICR_RTOCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->rtof != NULL)
        {
            irq()->uart->uart4->rtof();
        }
        else
        {
            uart4_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        UART4->ICR = USART_ICR_EOBCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->eob != NULL)
        {
            irq()->uart->uart4->eob();
        }
        else
        {
            uart4_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        UART4->ICR = USART_ICR_CMCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->cmf != NULL)
        {
            irq()->uart->uart4->cmf();
        }
        else
        {
            uart4_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        UART4->ICR = USART_ICR_WUCF;
        (void)UART4->ISR;

        if (irq()->uart->uart4->wuf != NULL)
        {
            irq()->uart->uart4->wuf();
        }
        else
        {
            uart4_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->uart4->txfe != NULL)
        {
            irq()->uart->uart4->txfe();
        }
        else
        {
            uart4_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->uart4->rxff != NULL)
        {
            irq()->uart->uart4->rxff();
        }
        else
        {
            uart4_rxff_callback();
        }
    }
}

void UART5_IRQHandler(void)
{
    uint32_t isr = UART5->ISR;
    uint32_t cr1 = UART5->CR1;
    uint32_t cr3 = UART5->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        UART5->ICR = USART_ICR_PECF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->pe != NULL)
        {
            irq()->uart->uart5->pe();
        }
        else
        {
            uart5_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        UART5->ICR = USART_ICR_FECF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->fe != NULL)
        {
            irq()->uart->uart5->fe();
        }
        else
        {
            uart5_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        UART5->ICR = USART_ICR_NECF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->ne != NULL)
        {
            irq()->uart->uart5->ne();
        }
        else
        {
            uart5_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        UART5->ICR = USART_ICR_ORECF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->ore != NULL)
        {
            irq()->uart->uart5->ore();
        }
        else
        {
            uart5_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        UART5->ICR = USART_ICR_IDLECF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->idle != NULL)
        {
            irq()->uart->uart5->idle();
        }
        else
        {
            uart5_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->uart5->rxne != NULL)
        {
            irq()->uart->uart5->rxne();
        }
        else
        {
            uart5_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->uart5->txe != NULL)
        {
            irq()->uart->uart5->txe();
        }
        else
        {
            uart5_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        UART5->ICR = USART_ICR_TCCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->tc != NULL)
        {
            irq()->uart->uart5->tc();
        }
        else
        {
            uart5_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        UART5->ICR = USART_ICR_CTSCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->cts != NULL)
        {
            irq()->uart->uart5->cts();
        }
        else
        {
            uart5_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        UART5->ICR = USART_ICR_RTOCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->rtof != NULL)
        {
            irq()->uart->uart5->rtof();
        }
        else
        {
            uart5_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        UART5->ICR = USART_ICR_EOBCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->eob != NULL)
        {
            irq()->uart->uart5->eob();
        }
        else
        {
            uart5_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        UART5->ICR = USART_ICR_CMCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->cmf != NULL)
        {
            irq()->uart->uart5->cmf();
        }
        else
        {
            uart5_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        UART5->ICR = USART_ICR_WUCF;
        (void)UART5->ISR;

        if (irq()->uart->uart5->wuf != NULL)
        {
            irq()->uart->uart5->wuf();
        }
        else
        {
            uart5_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->uart5->txfe != NULL)
        {
            irq()->uart->uart5->txfe();
        }
        else
        {
            uart5_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->uart5->rxff != NULL)
        {
            irq()->uart->uart5->rxff();
        }
        else
        {
            uart5_rxff_callback();
        }
    }
}

void LPUART1_IRQHandler(void)
{
    uint32_t isr = LPUART1->ISR;
    uint32_t cr1 = LPUART1->CR1;
    uint32_t cr3 = LPUART1->CR3;

    /* Parity Error */
    if ((isr & USART_ISR_PE) && (cr1 & USART_CR1_PEIE))
    {
        LPUART1->ICR = USART_ICR_PECF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->pe != NULL)
        {
            irq()->uart->lpuart1->pe();
        }
        else
        {
            lpuart1_pe_callback();
        }
    }

    /* Framing Error */
    if ((isr & USART_ISR_FE) && (cr3 & USART_CR3_EIE))
    {
        LPUART1->ICR = USART_ICR_FECF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->fe != NULL)
        {
            irq()->uart->lpuart1->fe();
        }
        else
        {
            lpuart1_fe_callback();
        }
    }

    /* Noise Error */
    if ((isr & USART_ISR_NE) && (cr3 & USART_CR3_EIE))
    {
        LPUART1->ICR = USART_ICR_NECF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->ne != NULL)
        {
            irq()->uart->lpuart1->ne();
        }
        else
        {
            lpuart1_ne_callback();
        }
    }

    /* Overrun Error (triggers on RXNEIE or EIE per RM0440) */
    if ((isr & USART_ISR_ORE) && ((cr1 & USART_CR1_RXNEIE_RXFNEIE) || (cr3 & USART_CR3_EIE)))
    {
        LPUART1->ICR = USART_ICR_ORECF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->ore != NULL)
        {
            irq()->uart->lpuart1->ore();
        }
        else
        {
            lpuart1_ore_callback();
        }
    }

    /* Idle Line */
    if ((isr & USART_ISR_IDLE) && (cr1 & USART_CR1_IDLEIE))
    {
        LPUART1->ICR = USART_ICR_IDLECF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->idle != NULL)
        {
            irq()->uart->lpuart1->idle();
        }
        else
        {
            lpuart1_idle_callback();
        }
    }

    /* RX Not Empty / RX FIFO Not Empty */
    if ((isr & USART_ISR_RXNE_RXFNE) && (cr1 & USART_CR1_RXNEIE_RXFNEIE))
    {
        if (irq()->uart->lpuart1->rxne != NULL)
        {
            irq()->uart->lpuart1->rxne();
        }
        else
        {
            lpuart1_rxne_callback();
        }
    }

    /* TX Empty / TX FIFO Not Full */
    if ((isr & USART_ISR_TXE_TXFNF) && (cr1 & USART_CR1_TXEIE_TXFNFIE))
    {
        if (irq()->uart->lpuart1->txe != NULL)
        {
            irq()->uart->lpuart1->txe();
        }
        else
        {
            lpuart1_txe_callback();
        }
    }

    /* Transmission Complete */
    if ((isr & USART_ISR_TC) && (cr1 & USART_CR1_TCIE))
    {
        LPUART1->ICR = USART_ICR_TCCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->tc != NULL)
        {
            irq()->uart->lpuart1->tc();
        }
        else
        {
            lpuart1_tc_callback();
        }
    }

    /* CTS */
    if ((isr & USART_ISR_CTSIF) && (cr3 & USART_CR3_CTSIE))
    {
        LPUART1->ICR = USART_ICR_CTSCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->cts != NULL)
        {
            irq()->uart->lpuart1->cts();
        }
        else
        {
            lpuart1_cts_callback();
        }
    }

    /* Receiver Timeout */
    if ((isr & USART_ISR_RTOF) && (cr1 & USART_CR1_RTOIE))
    {
        LPUART1->ICR = USART_ICR_RTOCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->rtof != NULL)
        {
            irq()->uart->lpuart1->rtof();
        }
        else
        {
            lpuart1_rtof_callback();
        }
    }

    /* End Of Block */
    if ((isr & USART_ISR_EOBF) && (cr1 & USART_CR1_EOBIE))
    {
        LPUART1->ICR = USART_ICR_EOBCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->eob != NULL)
        {
            irq()->uart->lpuart1->eob();
        }
        else
        {
            lpuart1_eob_callback();
        }
    }

    /* Character Match */
    if ((isr & USART_ISR_CMF) && (cr1 & USART_CR1_CMIE))
    {
        LPUART1->ICR = USART_ICR_CMCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->cmf != NULL)
        {
            irq()->uart->lpuart1->cmf();
        }
        else
        {
            lpuart1_cmf_callback();
        }
    }

    /* Wakeup From Stop */
    if ((isr & USART_ISR_WUF) && (cr3 & USART_CR3_WUFIE))
    {
        LPUART1->ICR = USART_ICR_WUCF;
        (void)LPUART1->ISR;

        if (irq()->uart->lpuart1->wuf != NULL)
        {
            irq()->uart->lpuart1->wuf();
        }
        else
        {
            lpuart1_wuf_callback();
        }
    }

    /* TX FIFO Empty */
    if ((isr & USART_ISR_TXFE) && (cr1 & USART_CR1_TXFEIE))
    {
        if (irq()->uart->lpuart1->txfe != NULL)
        {
            irq()->uart->lpuart1->txfe();
        }
        else
        {
            lpuart1_txfe_callback();
        }
    }

    /* RX FIFO Full */
    if ((isr & USART_ISR_RXFF) && (cr1 & USART_CR1_RXFFIE))
    {
        if (irq()->uart->lpuart1->rxff != NULL)
        {
            irq()->uart->lpuart1->rxff();
        }
        else
        {
            lpuart1_rxff_callback();
        }
    }
}

/*** EOF ***/
