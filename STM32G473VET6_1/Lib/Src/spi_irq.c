/******************************************************************************
	spi_irq.c
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: STM32GXXX
*******************************************************************************/
#include "spi_irq.h"
#include "stm32x_irq.h"
#include <stm32g4xx.h>

/******************************************************************************
 * SPI1
 ******************************************************************************/
void spi1_rxne_callback(void)   {}
void spi1_txe_callback(void)    {}

void spi1_ovr_callback(void)    {}
void spi1_modf_callback(void)   {}
void spi1_crcerr_callback(void) {}
void spi1_fre_callback(void)    {}

/******************************************************************************
 * SPI2
 ******************************************************************************/
void spi2_rxne_callback(void)   {}
void spi2_txe_callback(void)    {}

void spi2_ovr_callback(void)    {}
void spi2_modf_callback(void)   {}
void spi2_crcerr_callback(void) {}
void spi2_fre_callback(void)    {}

/******************************************************************************
 * SPI3
 ******************************************************************************/
void spi3_rxne_callback(void)   {}
void spi3_txe_callback(void)    {}

void spi3_ovr_callback(void)    {}
void spi3_modf_callback(void)   {}
void spi3_crcerr_callback(void) {}
void spi3_fre_callback(void)    {}

/******************************************************************************
 * SPI4
 ******************************************************************************/
void spi4_rxne_callback(void)   {}
void spi4_txe_callback(void)    {}

void spi4_ovr_callback(void)    {}
void spi4_modf_callback(void)   {}
void spi4_crcerr_callback(void) {}
void spi4_fre_callback(void)    {}

void SPI1_IRQHandler(void)
{
    uint32_t sr = SPI1->SR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (sr & SPI_SR_RXNE)
    {
        if (irq()->spi->spi1->rxne != NULL)
        {
            irq()->spi->spi1->rxne();
        }
        else
        {
            spi1_rxne_callback();
        }
    }

    /****************************************************************
     * Transmit Buffer Empty
     ****************************************************************/
    if (sr & SPI_SR_TXE)
    {
        if (irq()->spi->spi1->txe != NULL)
        {
            irq()->spi->spi1->txe();
        }
        else
        {
            spi1_txe_callback();
        }
    }

    /****************************************************************
     * Overrun Error
     ****************************************************************/
    if (sr & SPI_SR_OVR)
    {
        (void)SPI1->DR;
        (void)SPI1->SR;

        if (irq()->spi->spi1->ovr != NULL)
        {
            irq()->spi->spi1->ovr();
        }
        else
        {
            spi1_ovr_callback();
        }
    }

    /****************************************************************
     * Mode Fault
     ****************************************************************/
    if (sr & SPI_SR_MODF)
    {
        (void)SPI1->SR;
        CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);

        if (irq()->spi->spi1->modf != NULL)
        {
            irq()->spi->spi1->modf();
        }
        else
        {
            spi1_modf_callback();
        }
    }

    /****************************************************************
     * CRC Error
     ****************************************************************/
    if (sr & SPI_SR_CRCERR)
    {
        CLEAR_BIT(SPI1->SR, SPI_SR_CRCERR);
        (void)SPI1->SR;

        if (irq()->spi->spi1->crcerr != NULL)
        {
            irq()->spi->spi1->crcerr();
        }
        else
        {
            spi1_crcerr_callback();
        }
    }

    /****************************************************************
     * Frame Format Error
     ****************************************************************/
    if (sr & SPI_SR_FRE)
    {
        (void)SPI1->SR;

        if (irq()->spi->spi1->fre != NULL)
        {
            irq()->spi->spi1->fre();
        }
        else
        {
            spi1_fre_callback();
        }
    }
}

void SPI2_IRQHandler(void)
{
    uint32_t sr = SPI2->SR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (sr & SPI_SR_RXNE)
    {
        if (irq()->spi->spi2->rxne != NULL)
        {
            irq()->spi->spi2->rxne();
        }
        else
        {
            spi2_rxne_callback();
        }
    }

    /****************************************************************
     * Transmit Buffer Empty
     ****************************************************************/
    if (sr & SPI_SR_TXE)
    {
        if (irq()->spi->spi2->txe != NULL)
        {
            irq()->spi->spi2->txe();
        }
        else
        {
            spi2_txe_callback();
        }
    }

    /****************************************************************
     * Overrun Error
     ****************************************************************/
    if (sr & SPI_SR_OVR)
    {
        (void)SPI2->DR;
        (void)SPI2->SR;

        if (irq()->spi->spi2->ovr != NULL)
        {
            irq()->spi->spi2->ovr();
        }
        else
        {
            spi2_ovr_callback();
        }
    }

    /****************************************************************
     * Mode Fault
     ****************************************************************/
    if (sr & SPI_SR_MODF)
    {
        (void)SPI2->SR;
        CLEAR_BIT(SPI2->CR1, SPI_CR1_SPE);

        if (irq()->spi->spi2->modf != NULL)
        {
            irq()->spi->spi2->modf();
        }
        else
        {
            spi2_modf_callback();
        }
    }

    /****************************************************************
     * CRC Error
     ****************************************************************/
    if (sr & SPI_SR_CRCERR)
    {
        CLEAR_BIT(SPI2->SR, SPI_SR_CRCERR);
        (void)SPI2->SR;

        if (irq()->spi->spi2->crcerr != NULL)
        {
            irq()->spi->spi2->crcerr();
        }
        else
        {
            spi2_crcerr_callback();
        }
    }

    /****************************************************************
     * Frame Format Error
     ****************************************************************/
    if (sr & SPI_SR_FRE)
    {
        (void)SPI2->SR;

        if (irq()->spi->spi2->fre != NULL)
        {
            irq()->spi->spi2->fre();
        }
        else
        {
            spi2_fre_callback();
        }
    }
}

void SPI3_IRQHandler(void)
{
    uint32_t sr = SPI3->SR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (sr & SPI_SR_RXNE)
    {
        if (irq()->spi->spi3->rxne != NULL)
        {
            irq()->spi->spi3->rxne();
        }
        else
        {
            spi3_rxne_callback();
        }
    }

    /****************************************************************
     * Transmit Buffer Empty
     ****************************************************************/
    if (sr & SPI_SR_TXE)
    {
        if (irq()->spi->spi3->txe != NULL)
        {
            irq()->spi->spi3->txe();
        }
        else
        {
            spi3_txe_callback();
        }
    }

    /****************************************************************
     * Overrun Error
     ****************************************************************/
    if (sr & SPI_SR_OVR)
    {
        (void)SPI3->DR;
        (void)SPI3->SR;

        if (irq()->spi->spi3->ovr != NULL)
        {
            irq()->spi->spi3->ovr();
        }
        else
        {
            spi3_ovr_callback();
        }
    }

    /****************************************************************
     * Mode Fault
     ****************************************************************/
    if (sr & SPI_SR_MODF)
    {
        (void)SPI3->SR;
        CLEAR_BIT(SPI3->CR1, SPI_CR1_SPE);

        if (irq()->spi->spi3->modf != NULL)
        {
            irq()->spi->spi3->modf();
        }
        else
        {
            spi3_modf_callback();
        }
    }

    /****************************************************************
     * CRC Error
     ****************************************************************/
    if (sr & SPI_SR_CRCERR)
    {
        CLEAR_BIT(SPI3->SR, SPI_SR_CRCERR);
        (void)SPI3->SR;

        if (irq()->spi->spi3->crcerr != NULL)
        {
            irq()->spi->spi3->crcerr();
        }
        else
        {
            spi3_crcerr_callback();
        }
    }

    /****************************************************************
     * Frame Format Error
     ****************************************************************/
    if (sr & SPI_SR_FRE)
    {
        (void)SPI3->SR;

        if (irq()->spi->spi3->fre != NULL)
        {
            irq()->spi->spi3->fre();
        }
        else
        {
            spi3_fre_callback();
        }
    }
}

void SPI4_IRQHandler(void)
{
    uint32_t sr = SPI4->SR;

    /****************************************************************
     * Receive Buffer Not Empty
     ****************************************************************/
    if (sr & SPI_SR_RXNE)
    {
        if (irq()->spi->spi4->rxne != NULL)
        {
            irq()->spi->spi4->rxne();
        }
        else
        {
            spi4_rxne_callback();
        }
    }

    /****************************************************************
     * Transmit Buffer Empty
     ****************************************************************/
    if (sr & SPI_SR_TXE)
    {
        if (irq()->spi->spi4->txe != NULL)
        {
            irq()->spi->spi4->txe();
        }
        else
        {
            spi4_txe_callback();
        }
    }

    /****************************************************************
     * Overrun Error
     ****************************************************************/
    if (sr & SPI_SR_OVR)
    {
        (void)SPI4->DR;
        (void)SPI4->SR;

        if (irq()->spi->spi4->ovr != NULL)
        {
            irq()->spi->spi4->ovr();
        }
        else
        {
            spi4_ovr_callback();
        }
    }

    /****************************************************************
     * Mode Fault
     ****************************************************************/
    if (sr & SPI_SR_MODF)
    {
        (void)SPI4->SR;
        CLEAR_BIT(SPI4->CR1, SPI_CR1_SPE);

        if (irq()->spi->spi4->modf != NULL)
        {
            irq()->spi->spi4->modf();
        }
        else
        {
            spi4_modf_callback();
        }
    }

    /****************************************************************
     * CRC Error
     ****************************************************************/
    if (sr & SPI_SR_CRCERR)
    {
        CLEAR_BIT(SPI4->SR, SPI_SR_CRCERR);
        (void)SPI4->SR;

        if (irq()->spi->spi4->crcerr != NULL)
        {
            irq()->spi->spi4->crcerr();
        }
        else
        {
            spi4_crcerr_callback();
        }
    }

    /****************************************************************
     * Frame Format Error
     ****************************************************************/
    if (sr & SPI_SR_FRE)
    {
        (void)SPI4->SR;

        if (irq()->spi->spi4->fre != NULL)
        {
            irq()->spi->spi4->fre();
        }
        else
        {
            spi4_fre_callback();
        }
    }
}

/*** EOF ***/
