/******************************************************************************
	i2c_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "i2c_irq.h"
#include "stm32x_irq.h"
#include <stm32g4xx.h>

/******************************************************************************
 * I2C1
 ******************************************************************************/
/* Error interrupts */
void i2c1_berr_callback(void)    {}
void i2c1_arlo_callback(void)    {}
void i2c1_ovr_callback(void)     {}
void i2c1_pecerr_callback(void)  {}
void i2c1_timeout_callback(void) {}
void i2c1_alert_callback(void)   {}

/* Event interrupts */
void i2c1_rx_callback(void)      {}
void i2c1_tx_callback(void)      {}
void i2c1_addr_callback(void)    {}
void i2c1_nack_callback(void)    {}
void i2c1_stop_callback(void)    {}
void i2c1_tc_callback(void)      {}
void i2c1_tcr_callback(void)     {}

/******************************************************************************
 * I2C2
 ******************************************************************************/
/* Error interrupts */
void i2c2_berr_callback(void)    {}
void i2c2_arlo_callback(void)    {}
void i2c2_ovr_callback(void)     {}
void i2c2_pecerr_callback(void)  {}
void i2c2_timeout_callback(void) {}
void i2c2_alert_callback(void)   {}

/* Event interrupts */
void i2c2_rx_callback(void)      {}
void i2c2_tx_callback(void)      {}
void i2c2_addr_callback(void)    {}
void i2c2_nack_callback(void)    {}
void i2c2_stop_callback(void)    {}
void i2c2_tc_callback(void)      {}
void i2c2_tcr_callback(void)     {}

/******************************************************************************
 * I2C3
 ******************************************************************************/
/* Error interrupts */
void i2c3_berr_callback(void)    {}
void i2c3_arlo_callback(void)    {}
void i2c3_ovr_callback(void)     {}
void i2c3_pecerr_callback(void)  {}
void i2c3_timeout_callback(void) {}
void i2c3_alert_callback(void)   {}

/* Event interrupts */
void i2c3_rx_callback(void)      {}
void i2c3_tx_callback(void)      {}
void i2c3_addr_callback(void)    {}
void i2c3_nack_callback(void)    {}
void i2c3_stop_callback(void)    {}
void i2c3_tc_callback(void)      {}
void i2c3_tcr_callback(void)     {}

/******************************************************************************
 * I2C4
 ******************************************************************************/
/* Error interrupts */
void i2c4_berr_callback(void)    {}
void i2c4_arlo_callback(void)    {}
void i2c4_ovr_callback(void)     {}
void i2c4_pecerr_callback(void)  {}
void i2c4_timeout_callback(void) {}
void i2c4_alert_callback(void)   {}

/* Event interrupts */
void i2c4_rx_callback(void)      {}
void i2c4_tx_callback(void)      {}
void i2c4_addr_callback(void)    {}
void i2c4_nack_callback(void)    {}
void i2c4_stop_callback(void)    {}
void i2c4_tc_callback(void)      {}
void i2c4_tcr_callback(void)     {}

void I2C1_EV_IRQHandler(void)
{
    uint32_t isr = I2C1->ISR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (isr & I2C_ISR_RXNE)
    {
        if (irq()->i2c->i2c1->rxne != NULL)
        {
            irq()->i2c->i2c1->rxne();
        }
        else
        {
            i2c1_rx_callback();
        }
    }

    /****************************************************************
     * Transmit Interrupt Status
     ****************************************************************/
    if (isr & I2C_ISR_TXIS)
    {
        if (irq()->i2c->i2c1->txis != NULL)
        {
            irq()->i2c->i2c1->txis();
        }
        else
        {
            i2c1_tx_callback();
        }
    }

    /****************************************************************
     * Address Matched
     ****************************************************************/
    if (isr & I2C_ISR_ADDR)
    {
        I2C1->ICR = I2C_ICR_ADDRCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->addr != NULL)
        {
            irq()->i2c->i2c1->addr();
        }
        else
        {
            i2c1_addr_callback();
        }
    }

    /****************************************************************
     * Not Acknowledge Received
     ****************************************************************/
    if (isr & I2C_ISR_NACKF)
    {
        I2C1->ICR = I2C_ICR_NACKCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->nack != NULL)
        {
            irq()->i2c->i2c1->nack();
        }
        else
        {
            i2c1_nack_callback();
        }
    }

    /****************************************************************
     * Stop Detection
     ****************************************************************/
    if (isr & I2C_ISR_STOPF)
    {
        I2C1->ICR = I2C_ICR_STOPCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->stop != NULL)
        {
            irq()->i2c->i2c1->stop();
        }
        else
        {
            i2c1_stop_callback();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & I2C_ISR_TC)
    {
        if (irq()->i2c->i2c1->tc != NULL)
        {
            irq()->i2c->i2c1->tc();
        }
        else
        {
            i2c1_tc_callback();
        }
    }

    /****************************************************************
     * Transfer Complete Reload
     ****************************************************************/
    if (isr & I2C_ISR_TCR)
    {
        if (irq()->i2c->i2c1->tcr != NULL)
        {
            irq()->i2c->i2c1->tcr();
        }
        else
        {
            i2c1_tcr_callback();
        }
    }
}

void I2C1_ER_IRQHandler(void)
{
    uint32_t isr = I2C1->ISR;

    /****************************************************************
     * Bus Error
     ****************************************************************/
    if (isr & I2C_ISR_BERR)
    {
        I2C1->ICR = I2C_ICR_BERRCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->berr != NULL)
        {
            irq()->i2c->i2c1->berr();
        }
        else
        {
            i2c1_berr_callback();
        }
    }

    /****************************************************************
     * Arbitration Lost
     ****************************************************************/
    if (isr & I2C_ISR_ARLO)
    {
        I2C1->ICR = I2C_ICR_ARLOCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->arlo != NULL)
        {
            irq()->i2c->i2c1->arlo();
        }
        else
        {
            i2c1_arlo_callback();
        }
    }

    /****************************************************************
     * Overrun / Underrun
     ****************************************************************/
    if (isr & I2C_ISR_OVR)
    {
        I2C1->ICR = I2C_ICR_OVRCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->ovr != NULL)
        {
            irq()->i2c->i2c1->ovr();
        }
        else
        {
            i2c1_ovr_callback();
        }
    }

    /****************************************************************
     * PEC Error
     ****************************************************************/
    if (isr & I2C_ISR_PECERR)
    {
        I2C1->ICR = I2C_ICR_PECCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->pecerr != NULL)
        {
            irq()->i2c->i2c1->pecerr();
        }
        else
        {
            i2c1_pecerr_callback();
        }
    }

    /****************************************************************
     * Timeout
     ****************************************************************/
    if (isr & I2C_ISR_TIMEOUT)
    {
        I2C1->ICR = I2C_ICR_TIMOUTCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->timeout != NULL)
        {
            irq()->i2c->i2c1->timeout();
        }
        else
        {
            i2c1_timeout_callback();
        }
    }

    /****************************************************************
     * SMBus Alert
     ****************************************************************/
    if (isr & I2C_ISR_ALERT)
    {
        I2C1->ICR = I2C_ICR_ALERTCF;
        (void)I2C1->ISR;

        if (irq()->i2c->i2c1->alert != NULL)
        {
            irq()->i2c->i2c1->alert();
        }
        else
        {
            i2c1_alert_callback();
        }
    }
}

void I2C2_EV_IRQHandler(void)
{
    uint32_t isr = I2C2->ISR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (isr & I2C_ISR_RXNE)
    {
        if (irq()->i2c->i2c2->rxne != NULL)
        {
            irq()->i2c->i2c2->rxne();
        }
        else
        {
            i2c2_rx_callback();
        }
    }

    /****************************************************************
     * Transmit Interrupt Status
     ****************************************************************/
    if (isr & I2C_ISR_TXIS)
    {
        if (irq()->i2c->i2c2->txis != NULL)
        {
            irq()->i2c->i2c2->txis();
        }
        else
        {
            i2c2_tx_callback();
        }
    }

    /****************************************************************
     * Address Matched
     ****************************************************************/
    if (isr & I2C_ISR_ADDR)
    {
        I2C2->ICR = I2C_ICR_ADDRCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->addr != NULL)
        {
            irq()->i2c->i2c2->addr();
        }
        else
        {
            i2c2_addr_callback();
        }
    }

    /****************************************************************
     * Not Acknowledge Received
     ****************************************************************/
    if (isr & I2C_ISR_NACKF)
    {
        I2C2->ICR = I2C_ICR_NACKCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->nack != NULL)
        {
            irq()->i2c->i2c2->nack();
        }
        else
        {
            i2c2_nack_callback();
        }
    }

    /****************************************************************
     * Stop Detection
     ****************************************************************/
    if (isr & I2C_ISR_STOPF)
    {
        I2C2->ICR = I2C_ICR_STOPCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->stop != NULL)
        {
            irq()->i2c->i2c2->stop();
        }
        else
        {
            i2c2_stop_callback();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & I2C_ISR_TC)
    {
        if (irq()->i2c->i2c2->tc != NULL)
        {
            irq()->i2c->i2c2->tc();
        }
        else
        {
            i2c2_tc_callback();
        }
    }

    /****************************************************************
     * Transfer Complete Reload
     ****************************************************************/
    if (isr & I2C_ISR_TCR)
    {
        if (irq()->i2c->i2c2->tcr != NULL)
        {
            irq()->i2c->i2c2->tcr();
        }
        else
        {
            i2c2_tcr_callback();
        }
    }
}

void I2C2_ER_IRQHandler(void)
{
    uint32_t isr = I2C2->ISR;

    /****************************************************************
     * Bus Error
     ****************************************************************/
    if (isr & I2C_ISR_BERR)
    {
        I2C2->ICR = I2C_ICR_BERRCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->berr != NULL)
        {
            irq()->i2c->i2c2->berr();
        }
        else
        {
            i2c2_berr_callback();
        }
    }

    /****************************************************************
     * Arbitration Lost
     ****************************************************************/
    if (isr & I2C_ISR_ARLO)
    {
        I2C2->ICR = I2C_ICR_ARLOCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->arlo != NULL)
        {
            irq()->i2c->i2c2->arlo();
        }
        else
        {
            i2c2_arlo_callback();
        }
    }

    /****************************************************************
     * Overrun / Underrun
     ****************************************************************/
    if (isr & I2C_ISR_OVR)
    {
        I2C2->ICR = I2C_ICR_OVRCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->ovr != NULL)
        {
            irq()->i2c->i2c2->ovr();
        }
        else
        {
            i2c2_ovr_callback();
        }
    }

    /****************************************************************
     * PEC Error
     ****************************************************************/
    if (isr & I2C_ISR_PECERR)
    {
        I2C2->ICR = I2C_ICR_PECCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->pecerr != NULL)
        {
            irq()->i2c->i2c2->pecerr();
        }
        else
        {
            i2c2_pecerr_callback();
        }
    }

    /****************************************************************
     * Timeout
     ****************************************************************/
    if (isr & I2C_ISR_TIMEOUT)
    {
        I2C2->ICR = I2C_ICR_TIMOUTCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->timeout != NULL)
        {
            irq()->i2c->i2c2->timeout();
        }
        else
        {
            i2c2_timeout_callback();
        }
    }

    /****************************************************************
     * SMBus Alert
     ****************************************************************/
    if (isr & I2C_ISR_ALERT)
    {
        I2C2->ICR = I2C_ICR_ALERTCF;
        (void)I2C2->ISR;

        if (irq()->i2c->i2c2->alert != NULL)
        {
            irq()->i2c->i2c2->alert();
        }
        else
        {
            i2c2_alert_callback();
        }
    }
}

void I2C3_EV_IRQHandler(void)
{
    uint32_t isr = I2C3->ISR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (isr & I2C_ISR_RXNE)
    {
        if (irq()->i2c->i2c3->rxne != NULL)
        {
            irq()->i2c->i2c3->rxne();
        }
        else
        {
            i2c3_rx_callback();
        }
    }

    /****************************************************************
     * Transmit Interrupt Status
     ****************************************************************/
    if (isr & I2C_ISR_TXIS)
    {
        if (irq()->i2c->i2c3->txis != NULL)
        {
            irq()->i2c->i2c3->txis();
        }
        else
        {
            i2c3_tx_callback();
        }
    }

    /****************************************************************
     * Address Matched
     ****************************************************************/
    if (isr & I2C_ISR_ADDR)
    {
        I2C3->ICR = I2C_ICR_ADDRCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->addr != NULL)
        {
            irq()->i2c->i2c3->addr();
        }
        else
        {
            i2c3_addr_callback();
        }
    }

    /****************************************************************
     * Not Acknowledge Received
     ****************************************************************/
    if (isr & I2C_ISR_NACKF)
    {
        I2C3->ICR = I2C_ICR_NACKCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->nack != NULL)
        {
            irq()->i2c->i2c3->nack();
        }
        else
        {
            i2c3_nack_callback();
        }
    }

    /****************************************************************
     * Stop Detection
     ****************************************************************/
    if (isr & I2C_ISR_STOPF)
    {
        I2C3->ICR = I2C_ICR_STOPCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->stop != NULL)
        {
            irq()->i2c->i2c3->stop();
        }
        else
        {
            i2c3_stop_callback();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & I2C_ISR_TC)
    {
        if (irq()->i2c->i2c3->tc != NULL)
        {
            irq()->i2c->i2c3->tc();
        }
        else
        {
            i2c3_tc_callback();
        }
    }

    /****************************************************************
     * Transfer Complete Reload
     ****************************************************************/
    if (isr & I2C_ISR_TCR)
    {
        if (irq()->i2c->i2c3->tcr != NULL)
        {
            irq()->i2c->i2c3->tcr();
        }
        else
        {
            i2c3_tcr_callback();
        }
    }
}

void I2C3_ER_IRQHandler(void)
{
    uint32_t isr = I2C3->ISR;

    /****************************************************************
     * Bus Error
     ****************************************************************/
    if (isr & I2C_ISR_BERR)
    {
        I2C3->ICR = I2C_ICR_BERRCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->berr != NULL)
        {
            irq()->i2c->i2c3->berr();
        }
        else
        {
            i2c3_berr_callback();
        }
    }

    /****************************************************************
     * Arbitration Lost
     ****************************************************************/
    if (isr & I2C_ISR_ARLO)
    {
        I2C3->ICR = I2C_ICR_ARLOCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->arlo != NULL)
        {
            irq()->i2c->i2c3->arlo();
        }
        else
        {
            i2c3_arlo_callback();
        }
    }

    /****************************************************************
     * Overrun / Underrun
     ****************************************************************/
    if (isr & I2C_ISR_OVR)
    {
        I2C3->ICR = I2C_ICR_OVRCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->ovr != NULL)
        {
            irq()->i2c->i2c3->ovr();
        }
        else
        {
            i2c3_ovr_callback();
        }
    }

    /****************************************************************
     * PEC Error
     ****************************************************************/
    if (isr & I2C_ISR_PECERR)
    {
        I2C3->ICR = I2C_ICR_PECCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->pecerr != NULL)
        {
            irq()->i2c->i2c3->pecerr();
        }
        else
        {
            i2c3_pecerr_callback();
        }
    }

    /****************************************************************
     * Timeout
     ****************************************************************/
    if (isr & I2C_ISR_TIMEOUT)
    {
        I2C3->ICR = I2C_ICR_TIMOUTCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->timeout != NULL)
        {
            irq()->i2c->i2c3->timeout();
        }
        else
        {
            i2c3_timeout_callback();
        }
    }

    /****************************************************************
     * SMBus Alert
     ****************************************************************/
    if (isr & I2C_ISR_ALERT)
    {
        I2C3->ICR = I2C_ICR_ALERTCF;
        (void)I2C3->ISR;

        if (irq()->i2c->i2c3->alert != NULL)
        {
            irq()->i2c->i2c3->alert();
        }
        else
        {
            i2c3_alert_callback();
        }
    }
}

void I2C4_EV_IRQHandler(void)
{
    uint32_t isr = I2C4->ISR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (isr & I2C_ISR_RXNE)
    {
        if (irq()->i2c->i2c4->rxne != NULL)
        {
            irq()->i2c->i2c4->rxne();
        }
        else
        {
            i2c4_rx_callback();
        }
    }

    /****************************************************************
     * Transmit Interrupt Status
     ****************************************************************/
    if (isr & I2C_ISR_TXIS)
    {
        if (irq()->i2c->i2c4->txis != NULL)
        {
            irq()->i2c->i2c4->txis();
        }
        else
        {
            i2c4_tx_callback();
        }
    }

    /****************************************************************
     * Address Matched
     ****************************************************************/
    if (isr & I2C_ISR_ADDR)
    {
        I2C4->ICR = I2C_ICR_ADDRCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->addr != NULL)
        {
            irq()->i2c->i2c4->addr();
        }
        else
        {
            i2c4_addr_callback();
        }
    }

    /****************************************************************
     * Not Acknowledge Received
     ****************************************************************/
    if (isr & I2C_ISR_NACKF)
    {
        I2C4->ICR = I2C_ICR_NACKCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->nack != NULL)
        {
            irq()->i2c->i2c4->nack();
        }
        else
        {
            i2c4_nack_callback();
        }
    }

    /****************************************************************
     * Stop Detection
     ****************************************************************/
    if (isr & I2C_ISR_STOPF)
    {
        I2C4->ICR = I2C_ICR_STOPCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->stop != NULL)
        {
            irq()->i2c->i2c4->stop();
        }
        else
        {
            i2c4_stop_callback();
        }
    }

    /****************************************************************
     * Transfer Complete
     ****************************************************************/
    if (isr & I2C_ISR_TC)
    {
        if (irq()->i2c->i2c4->tc != NULL)
        {
            irq()->i2c->i2c4->tc();
        }
        else
        {
            i2c4_tc_callback();
        }
    }

    /****************************************************************
     * Transfer Complete Reload
     ****************************************************************/
    if (isr & I2C_ISR_TCR)
    {
        if (irq()->i2c->i2c4->tcr != NULL)
        {
            irq()->i2c->i2c4->tcr();
        }
        else
        {
            i2c4_tcr_callback();
        }
    }
}

void I2C4_ER_IRQHandler(void)
{
    uint32_t isr = I2C4->ISR;

    /****************************************************************
     * Bus Error
     ****************************************************************/
    if (isr & I2C_ISR_BERR)
    {
        I2C4->ICR = I2C_ICR_BERRCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->berr != NULL)
        {
            irq()->i2c->i2c4->berr();
        }
        else
        {
            i2c4_berr_callback();
        }
    }

    /****************************************************************
     * Arbitration Lost
     ****************************************************************/
    if (isr & I2C_ISR_ARLO)
    {
        I2C4->ICR = I2C_ICR_ARLOCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->arlo != NULL)
        {
            irq()->i2c->i2c4->arlo();
        }
        else
        {
            i2c4_arlo_callback();
        }
    }

    /****************************************************************
     * Overrun / Underrun
     ****************************************************************/
    if (isr & I2C_ISR_OVR)
    {
        I2C4->ICR = I2C_ICR_OVRCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->ovr != NULL)
        {
            irq()->i2c->i2c4->ovr();
        }
        else
        {
            i2c4_ovr_callback();
        }
    }

    /****************************************************************
     * PEC Error
     ****************************************************************/
    if (isr & I2C_ISR_PECERR)
    {
        I2C4->ICR = I2C_ICR_PECCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->pecerr != NULL)
        {
            irq()->i2c->i2c4->pecerr();
        }
        else
        {
            i2c4_pecerr_callback();
        }
    }

    /****************************************************************
     * Timeout
     ****************************************************************/
    if (isr & I2C_ISR_TIMEOUT)
    {
        I2C4->ICR = I2C_ICR_TIMOUTCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->timeout != NULL)
        {
            irq()->i2c->i2c4->timeout();
        }
        else
        {
            i2c4_timeout_callback();
        }
    }

    /****************************************************************
     * SMBus Alert
     ****************************************************************/
    if (isr & I2C_ISR_ALERT)
    {
        I2C4->ICR = I2C_ICR_ALERTCF;
        (void)I2C4->ISR;

        if (irq()->i2c->i2c4->alert != NULL)
        {
            irq()->i2c->i2c4->alert();
        }
        else
        {
            i2c4_alert_callback();
        }
    }
}

/*** EOF ***/

