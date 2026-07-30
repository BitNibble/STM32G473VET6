/******************************************************************************
	usart_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "usart_irq.h"
#include "stm32_irq.h"
#include <stm32g4xx.h>
/******************************************************************************
 * USART1
 ******************************************************************************/
void usart1_pe_callback(void)   {}
void usart1_fe_callback(void)   {}
void usart1_ne_callback(void)   {}
void usart1_ore_callback(void)  {}

void usart1_idle_callback(void) {}
void usart1_rxne_callback(void) {}
void usart1_txe_callback(void)  {}
void usart1_tc_callback(void)   {}

void usart1_cts_callback(void)  {}
void usart1_rtof_callback(void) {}
void usart1_eob_callback(void)  {}
void usart1_cmf_callback(void)  {}
void usart1_wuf_callback(void)  {}

void usart1_txfe_callback(void) {}
void usart1_rxff_callback(void) {}

/******************************************************************************
 * USART2
 ******************************************************************************/
void usart2_pe_callback(void)   {}
void usart2_fe_callback(void)   {}
void usart2_ne_callback(void)   {}
void usart2_ore_callback(void)  {}

void usart2_idle_callback(void) {}
void usart2_rxne_callback(void) {}
void usart2_txe_callback(void)  {}
void usart2_tc_callback(void)   {}

void usart2_cts_callback(void)  {}
void usart2_rtof_callback(void) {}
void usart2_eob_callback(void)  {}
void usart2_cmf_callback(void)  {}
void usart2_wuf_callback(void)  {}

void usart2_txfe_callback(void) {}
void usart2_rxff_callback(void) {}

/******************************************************************************
 * USART3
 ******************************************************************************/
void usart3_pe_callback(void)   {}
void usart3_fe_callback(void)   {}
void usart3_ne_callback(void)   {}
void usart3_ore_callback(void)  {}

void usart3_idle_callback(void) {}
void usart3_rxne_callback(void) {}
void usart3_txe_callback(void)  {}
void usart3_tc_callback(void)   {}

void usart3_cts_callback(void)  {}
void usart3_rtof_callback(void) {}
void usart3_eob_callback(void)  {}
void usart3_cmf_callback(void)  {}
void usart3_wuf_callback(void)  {}

void usart3_txfe_callback(void) {}
void usart3_rxff_callback(void) {}

/******************************************************************************
 * UART4
 ******************************************************************************/
void uart4_pe_callback(void)    {}
void uart4_fe_callback(void)    {}
void uart4_ne_callback(void)    {}
void uart4_ore_callback(void)   {}

void uart4_idle_callback(void)  {}
void uart4_rxne_callback(void)  {}
void uart4_txe_callback(void)   {}
void uart4_tc_callback(void)    {}

void uart4_cts_callback(void)   {}
void uart4_rtof_callback(void)  {}
void uart4_eob_callback(void)   {}
void uart4_cmf_callback(void)   {}
void uart4_wuf_callback(void)   {}

void uart4_txfe_callback(void)  {}
void uart4_rxff_callback(void)  {}

/******************************************************************************
 * UART5
 ******************************************************************************/
void uart5_pe_callback(void)    {}
void uart5_fe_callback(void)    {}
void uart5_ne_callback(void)    {}
void uart5_ore_callback(void)   {}

void uart5_idle_callback(void)  {}
void uart5_rxne_callback(void)  {}
void uart5_txe_callback(void)   {}
void uart5_tc_callback(void)    {}

void uart5_cts_callback(void)   {}
void uart5_rtof_callback(void)  {}
void uart5_eob_callback(void)   {}
void uart5_cmf_callback(void)   {}
void uart5_wuf_callback(void)   {}

void uart5_txfe_callback(void)  {}
void uart5_rxff_callback(void)  {}

/******************************************************************************
 * LPUART1
 ******************************************************************************/
void lpuart1_pe_callback(void)   {}
void lpuart1_fe_callback(void)   {}
void lpuart1_ne_callback(void)   {}
void lpuart1_ore_callback(void)  {}

void lpuart1_idle_callback(void) {}
void lpuart1_rxne_callback(void) {}
void lpuart1_txe_callback(void)  {}
void lpuart1_tc_callback(void)   {}

void lpuart1_cts_callback(void)  {}
void lpuart1_rtof_callback(void) {}
void lpuart1_eob_callback(void)  {}
void lpuart1_cmf_callback(void)  {}
void lpuart1_wuf_callback(void)  {}

void lpuart1_txfe_callback(void) {}
void lpuart1_rxff_callback(void) {}

void USART1_IRQHandler(void)
{
    uint32_t isr = USART1->ISR;

    /****************************************************************
     * Parity Error
     ****************************************************************/
    if (isr & USART_ISR_PE)
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

    /****************************************************************
     * Framing Error
     ****************************************************************/
    if (isr & USART_ISR_FE)
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

    /****************************************************************
     * Noise Error
     ****************************************************************/
    if (isr & USART_ISR_NE)
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

    /****************************************************************
     * Overrun Error
     ****************************************************************/
    if (isr & USART_ISR_ORE)
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

    /****************************************************************
     * Idle Line
     ****************************************************************/
    if (isr & USART_ISR_IDLE)
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

    /****************************************************************
     * RX Not Empty
     ****************************************************************/
    if (isr & USART_ISR_RXNE_RXFNE)
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

    /****************************************************************
     * TX Empty
     ****************************************************************/
    if (isr & USART_ISR_TXE_TXFNF)
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

    /****************************************************************
     * Transmission Complete
     ****************************************************************/
    if (isr & USART_ISR_TC)
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

    /****************************************************************
     * CTS
     ****************************************************************/
    if (isr & USART_ISR_CTSIF)
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

    /****************************************************************
     * Receiver Timeout
     ****************************************************************/
    if (isr & USART_ISR_RTOF)
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

    /****************************************************************
     * End Of Block
     ****************************************************************/
    if (isr & USART_ISR_EOBF)
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

    /****************************************************************
     * Character Match
     ****************************************************************/
    if (isr & USART_ISR_CMF)
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

    /****************************************************************
     * Wakeup From Stop
     ****************************************************************/
    if (isr & USART_ISR_WUF)
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

    /****************************************************************
     * TX FIFO Empty
     ****************************************************************/
    if (isr & USART_ISR_TXFE)
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

    /****************************************************************
     * RX FIFO Full
     ****************************************************************/
    if (isr & USART_ISR_RXFF)
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

    /* Parity Error */
    if (isr & USART_ISR_PE)
    {
        USART2->ICR = USART_ICR_PECF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->parity_error != NULL)
        {
            irq()->uart->usart2->parity_error();
        }
        else
        {
            usart2_pe_callback();
        }
    }

    /* Framing Error */
    if (isr & USART_ISR_FE)
    {
        USART2->ICR = USART_ICR_FECF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->framing_error != NULL)
        {
            irq()->uart->usart2->framing_error();
        }
        else
        {
            usart2_fe_callback();
        }
    }

    /* Noise Error */
    if (isr & USART_ISR_NE)
    {
        USART2->ICR = USART_ICR_NECF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->noise_error != NULL)
        {
            irq()->uart->usart2->noise_error();
        }
        else
        {
            usart2_ne_callback();
        }
    }

    /* Overrun Error */
    if (isr & USART_ISR_ORE)
    {
        USART2->ICR = USART_ICR_ORECF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->overrun_error != NULL)
        {
            irq()->uart->usart2->overrun_error();
        }
        else
        {
            usart2_ore_callback();
        }
    }

    /* Idle Line */
    if (isr & USART_ISR_IDLE)
    {
        USART2->ICR = USART_ICR_IDLECF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->idle != NULL)
        {
            irq()->uart->usart2->idle();
        }
        else
        {
            usart2_idle_callback();
        }
    }

    /* RX Not Empty */
    if (isr & USART_ISR_RXNE_RXFNE)
    {
        if (irq()->uart->usart2->rx != NULL)
        {
            irq()->uart->usart2->rx();
        }
        else
        {
            usart2_rxne_callback();
        }
    }

    /* Transmission Complete */
    if (isr & USART_ISR_TC)
    {
        USART2->ICR = USART_ICR_TCCF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->tc != NULL)
        {
            irq()->uart->usart2->tc();
        }
        else
        {
            usart2_tc_callback();
        }
    }

    /* TX Empty */
    if (isr & USART_ISR_TXE_TXFNF)
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

    /* CTS */
    if (isr & USART_ISR_CTSIF)
    {
        USART2->ICR = USART_ICR_CTSCF;
        (void)USART2->ICR;

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
    if (isr & USART_ISR_RTOF)
    {
        USART2->ICR = USART_ICR_RTOCF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->receiver_timeout != NULL)
        {
            irq()->uart->usart2->receiver_timeout();
        }
        else
        {
            usart2_rtof_callback();
        }
    }

    /* End Of Block */
    if (isr & USART_ISR_EOBF)
    {
        USART2->ICR = USART_ICR_EOBCF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->end_of_block != NULL)
        {
            irq()->uart->usart2->end_of_block();
        }
        else
        {
            usart2_eob_callback();
        }
    }

    /* Wake Up */
    if (isr & USART_ISR_WUF)
    {
        USART2->ICR = USART_ICR_WUCF;
        (void)USART2->ICR;

        if (irq()->uart->usart2->wake_up != NULL)
        {
            irq()->uart->usart2->wake_up();
        }
        else
        {
            usart2_wuf_callback();
        }
    }
}

void USART3_IRQHandler(void)
{
    uint32_t isr = USART3->ISR;

    /* Parity Error */
    if (isr & USART_ISR_PE)
    {
        USART3->ICR = USART_ICR_PECF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->parity_error != NULL)
        {
            irq()->uart->usart3->parity_error();
        }
        else
        {
            usart3_pe_callback();
        }
    }

    /* Framing Error */
    if (isr & USART_ISR_FE)
    {
        USART3->ICR = USART_ICR_FECF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->framing_error != NULL)
        {
            irq()->uart->usart3->framing_error();
        }
        else
        {
            usart3_fe_callback();
        }
    }

    /* Noise Error */
    if (isr & USART_ISR_NE)
    {
        USART3->ICR = USART_ICR_NECF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->noise_error != NULL)
        {
            irq()->uart->usart3->noise_error();
        }
        else
        {
            usart3_ne_callback();
        }
    }

    /* Overrun Error */
    if (isr & USART_ISR_ORE)
    {
        USART3->ICR = USART_ICR_ORECF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->overrun_error != NULL)
        {
            irq()->uart->usart3->overrun_error();
        }
        else
        {
            usart3_ore_callback();
        }
    }

    /* Idle Line */
    if (isr & USART_ISR_IDLE)
    {
        USART3->ICR = USART_ICR_IDLECF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->idle != NULL)
        {
            irq()->uart->usart3->idle();
        }
        else
        {
            usart3_idle_callback();
        }
    }

    /* RX Not Empty */
    if (isr & USART_ISR_RXNE_RXFNE)
    {
        if (irq()->uart->usart3->rx != NULL)
        {
            irq()->uart->usart3->rx();
        }
        else
        {
            usart3_rxne_callback();
        }
    }

    /* Transmission Complete */
    if (isr & USART_ISR_TC)
    {
        USART3->ICR = USART_ICR_TCCF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->tc != NULL)
        {
            irq()->uart->usart3->tc();
        }
        else
        {
            usart3_tc_callback();
        }
    }

    /* TX Empty */
    if (isr & USART_ISR_TXE_TXFNF)
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

    /* CTS */
    if (isr & USART_ISR_CTSIF)
    {
        USART3->ICR = USART_ICR_CTSCF;
        (void)USART3->ICR;

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
    if (isr & USART_ISR_RTOF)
    {
        USART3->ICR = USART_ICR_RTOCF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->receiver_timeout != NULL)
        {
            irq()->uart->usart3->receiver_timeout();
        }
        else
        {
            usart3_rtof_callback();
        }
    }

    /* End Of Block */
    if (isr & USART_ISR_EOBF)
    {
        USART3->ICR = USART_ICR_EOBCF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->end_of_block != NULL)
        {
            irq()->uart->usart3->end_of_block();
        }
        else
        {
            usart3_eob_callback();
        }
    }

    /* Wake Up */
    if (isr & USART_ISR_WUF)
    {
        USART3->ICR = USART_ICR_WUCF;
        (void)USART3->ICR;

        if (irq()->uart->usart3->wake_up != NULL)
        {
            irq()->uart->usart3->wake_up();
        }
        else
        {
            usart3_wuf_callback();
        }
    }
}

void UART4_IRQHandler(void)
{
    uint32_t isr = UART4->ISR;

    /* Parity Error */
    if (isr & USART_ISR_PE)
    {
        UART4->ICR = USART_ICR_PECF;

        if (irq()->uart->uart4->parity_error != NULL)
        {
            irq()->uart->uart4->parity_error();
        }
        else
        {
            uart4_pe_callback();
        }
    }

    /* Framing Error */
    if (isr & USART_ISR_FE)
    {
        UART4->ICR = USART_ICR_FECF;

        if (irq()->uart->uart4->framing_error != NULL)
        {
            irq()->uart->uart4->framing_error();
        }
        else
        {
            uart4_fe_callback();
        }
    }

    /* Noise Error */
    if (isr & USART_ISR_NE)
    {
        UART4->ICR = USART_ICR_NECF;

        if (irq()->uart->uart4->noise_error != NULL)
        {
            irq()->uart->uart4->noise_error();
        }
        else
        {
            uart4_ne_callback();
        }
    }

    /* Overrun Error */
    if (isr & USART_ISR_ORE)
    {
        UART4->ICR = USART_ICR_ORECF;

        if (irq()->uart->uart4->overrun_error != NULL)
        {
            irq()->uart->uart4->overrun_error();
        }
        else
        {
            uart4_ore_callback();
        }
    }

    /* Idle Line */
    if (isr & USART_ISR_IDLE)
    {
        UART4->ICR = USART_ICR_IDLECF;

        if (irq()->uart->uart4->idle != NULL)
        {
            irq()->uart->uart4->idle();
        }
        else
        {
            uart4_idle_callback();
        }
    }

    /* RX Not Empty */
    if (isr & USART_ISR_RXNE_RXFNE)
    {
        if (irq()->uart->uart4->rx != NULL)
        {
            irq()->uart->uart4->rx();
        }
        else
        {
            uart4_rxne_callback();
        }
    }

    /* TX Empty */
    if (isr & USART_ISR_TXE_TXFNF)
    {
        if (irq()->uart->uart4->tx != NULL)
        {
            irq()->uart->uart4->tx();
        }
        else
        {
            uart4_txe_callback();
        }
    }

    /* Transmission Complete */
    if (isr & USART_ISR_TC)
    {
        UART4->ICR = USART_ICR_TCCF;

        if (irq()->uart->uart4->tc != NULL)
        {
            irq()->uart->uart4->tc();
        }
        else
        {
            uart4_tc_callback();
        }
    }

    /* Character Match */
    if (isr & USART_ISR_CMF)
    {
        UART4->ICR = USART_ICR_CMCF;

        if (irq()->uart->uart4->character_match != NULL)
        {
            irq()->uart->uart4->character_match();
        }
        else
        {
            uart4_cmf_callback();
        }
    }

    /* Receiver Timeout */
    if (isr & USART_ISR_RTOF)
    {
        UART4->ICR = USART_ICR_RTOCF;

        if (irq()->uart->uart4->receiver_timeout != NULL)
        {
            irq()->uart->uart4->receiver_timeout();
        }
        else
        {
            uart4_rtof_callback();
        }
    }

    /* End Of Block */
    if (isr & USART_ISR_EOBF)
    {
        UART4->ICR = USART_ICR_EOBCF;

        if (irq()->uart->uart4->end_of_block != NULL)
        {
            irq()->uart->uart4->end_of_block();
        }
        else
        {
            uart4_eob_callback();
        }
    }

    /* CTS */
    if (isr & USART_ISR_CTSIF)
    {
        UART4->ICR = USART_ICR_CTSCF;

        if (irq()->uart->uart4->cts != NULL)
        {
            irq()->uart->uart4->cts();
        }
        else
        {
            uart4_cts_callback();
        }
    }

    /* Wakeup from Stop */
    if (isr & USART_ISR_WUF)
    {
        UART4->ICR = USART_ICR_WUCF;

        if (irq()->uart->uart4->wakeup != NULL)
        {
            irq()->uart->uart4->wakeup();
        }
        else
        {
            uart4_wuf_callback();
        }
    }
}

void UART5_IRQHandler(void)
{
    uint32_t isr = UART5->ISR;

    // Parity Error
    if (isr & USART_ISR_PE)
    {
        UART5->ICR = USART_ICR_PECF;

        if (irq()->uart->uart5->parity_error != NULL)
        {
            irq()->uart->uart5->parity_error();
        }
        else
        {
            uart5_pe_callback();
        }
    }

    // Framing Error
    if (isr & USART_ISR_FE)
    {
        UART5->ICR = USART_ICR_FECF;

        if (irq()->uart->uart5->framing_error != NULL)
        {
            irq()->uart->uart5->framing_error();
        }
        else
        {
            uart5_fe_callback();
        }
    }

    // Noise Error
    if (isr & USART_ISR_NE)
    {
        UART5->ICR = USART_ICR_NECF;

        if (irq()->uart->uart5->noise_error != NULL)
        {
            irq()->uart->uart5->noise_error();
        }
        else
        {
            uart5_ne_callback();
        }
    }

    // Overrun Error
    if (isr & USART_ISR_ORE)
    {
        UART5->ICR = USART_ICR_ORECF;

        if (irq()->uart->uart5->overrun_error != NULL)
        {
            irq()->uart->uart5->overrun_error();
        }
        else
        {
            uart5_ore_callback();
        }
    }

    // Idle Line
    if (isr & USART_ISR_IDLE)
    {
        UART5->ICR = USART_ICR_IDLECF;

        if (irq()->uart->uart5->idle != NULL)
        {
            irq()->uart->uart5->idle();
        }
        else
        {
            uart5_idle_callback();
        }
    }

    // RX Not Empty
    if (isr & USART_ISR_RXNE_RXFNE)
    {
        if (irq()->uart->uart5->rx != NULL)
        {
            irq()->uart->uart5->rx();
        }
        else
        {
            uart5_rxne_callback();
        }
    }

    // TX Empty
    if (isr & USART_ISR_TXE_TXFNF)
    {
        if (irq()->uart->uart5->tx != NULL)
        {
            irq()->uart->uart5->tx();
        }
        else
        {
            uart5_txe_callback();
        }
    }

    // Transmission Complete
    if (isr & USART_ISR_TC)
    {
        UART5->ICR = USART_ICR_TCCF;

        if (irq()->uart->uart5->tc != NULL)
        {
            irq()->uart->uart5->tc();
        }
        else
        {
            uart5_tc_callback();
        }
    }

    // Character Match
    if (isr & USART_ISR_CMF)
    {
        UART5->ICR = USART_ICR_CMCF;

        if (irq()->uart->uart5->character_match != NULL)
        {
            irq()->uart->uart5->character_match();
        }
        else
        {
            uart5_cmf_callback();
        }
    }

    // Receiver Timeout
    if (isr & USART_ISR_RTOF)
    {
        UART5->ICR = USART_ICR_RTOCF;

        if (irq()->uart->uart5->receiver_timeout != NULL)
        {
            irq()->uart->uart5->receiver_timeout();
        }
        else
        {
            uart5_rtof_callback();
        }
    }

    // End Of Block
    if (isr & USART_ISR_EOBF)
    {
        UART5->ICR = USART_ICR_EOBCF;

        if (irq()->uart->uart5->end_of_block != NULL)
        {
            irq()->uart->uart5->end_of_block();
        }
        else
        {
            uart5_eob_callback();
        }
    }

    // CTS
    if (isr & USART_ISR_CTSIF)
    {
        UART5->ICR = USART_ICR_CTSCF;

        if (irq()->uart->uart5->cts != NULL)
        {
            irq()->uart->uart5->cts();
        }
        else
        {
            uart5_cts_callback();
        }
    }

    // Wakeup from Stop
    if (isr & USART_ISR_WUF)
    {
        UART5->ICR = USART_ICR_WUCF;

        if (irq()->uart->uart5->wakeup != NULL)
        {
            irq()->uart->uart5->wakeup();
        }
        else
        {
            uart5_wuf_callback();
        }
    }
}

void LPUART1_IRQHandler(void)
{
    uint32_t isr = LPUART1->ISR;

    // Parity Error
    if (isr & USART_ISR_PE)
    {
        LPUART1->ICR = USART_ICR_PECF;

        if (irq()->uart->lpuart1->parity_error != NULL)
        {
            irq()->uart->lpuart1->parity_error();
        }
        else
        {
            lpuart1_pe_callback();
        }
    }

    // Framing Error
    if (isr & USART_ISR_FE)
    {
        LPUART1->ICR = USART_ICR_FECF;

        if (irq()->uart->lpuart1->framing_error != NULL)
        {
            irq()->uart->lpuart1->framing_error();
        }
        else
        {
            lpuart1_fe_callback();
        }
    }

    // Noise Error
    if (isr & USART_ISR_NE)
    {
        LPUART1->ICR = USART_ICR_NECF;

        if (irq()->uart->lpuart1->noise_error != NULL)
        {
            irq()->uart->lpuart1->noise_error();
        }
        else
        {
            lpuart1_ne_callback();
        }
    }

    // Overrun Error
    if (isr & USART_ISR_ORE)
    {
        LPUART1->ICR = USART_ICR_ORECF;

        if (irq()->uart->lpuart1->overrun_error != NULL)
        {
            irq()->uart->lpuart1->overrun_error();
        }
        else
        {
            lpuart1_ore_callback();
        }
    }

    // Idle Line
    if (isr & USART_ISR_IDLE)
    {
        LPUART1->ICR = USART_ICR_IDLECF;

        if (irq()->uart->lpuart1->idle != NULL)
        {
            irq()->uart->lpuart1->idle();
        }
        else
        {
            lpuart1_idle_callback();
        }
    }

    // RX Not Empty
    if (isr & USART_ISR_RXNE_RXFNE)
    {
        if (irq()->uart->lpuart1->rx != NULL)
        {
            irq()->uart->lpuart1->rx();
        }
        else
        {
            lpuart1_rxne_callback();
        }
    }

    // TX Empty
    if (isr & USART_ISR_TXE_TXFNF)
    {
        if (irq()->uart->lpuart1->tx != NULL)
        {
            irq()->uart->lpuart1->tx();
        }
        else
        {
            lpuart1_txe_callback();
        }
    }

    // Transmission Complete
    if (isr & USART_ISR_TC)
    {
        LPUART1->ICR = USART_ICR_TCCF;

        if (irq()->uart->lpuart1->tc != NULL)
        {
            irq()->uart->lpuart1->tc();
        }
        else
        {
            lpuart1_tc_callback();
        }
    }

    // Character Match
    if (isr & USART_ISR_CMF)
    {
        LPUART1->ICR = USART_ICR_CMCF;

        if (irq()->uart->lpuart1->character_match != NULL)
        {
            irq()->uart->lpuart1->character_match();
        }
        else
        {
            lpuart1_cmf_callback();
        }
    }

    // Receiver Timeout
    if (isr & USART_ISR_RTOF)
    {
        LPUART1->ICR = USART_ICR_RTOCF;

        if (irq()->uart->lpuart1->receiver_timeout != NULL)
        {
            irq()->uart->lpuart1->receiver_timeout();
        }
        else
        {
            lpuart1_rtof_callback();
        }
    }

    // End Of Block
    if (isr & USART_ISR_EOBF)
    {
        LPUART1->ICR = USART_ICR_EOBCF;

        if (irq()->uart->lpuart1->end_of_block != NULL)
        {
            irq()->uart->lpuart1->end_of_block();
        }
        else
        {
            lpuart1_eob_callback();
        }
    }

    // CTS
    if (isr & USART_ISR_CTSIF)
    {
        LPUART1->ICR = USART_ICR_CTSCF;

        if (irq()->uart->lpuart1->cts != NULL)
        {
            irq()->uart->lpuart1->cts();
        }
        else
        {
            lpuart1_cts_callback();
        }
    }

    // Wake up from Stop
    if (isr & USART_ISR_WUF)
    {
        LPUART1->ICR = USART_ICR_WUCF;

        if (irq()->uart->lpuart1->wakeup != NULL)
        {
            irq()->uart->lpuart1->wakeup();
        }
        else
        {
            lpuart1_wuf_callback();
        }
    }
}

/*** EOF ***/

