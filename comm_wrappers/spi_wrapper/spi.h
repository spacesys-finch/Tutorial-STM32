#ifndef spi.h
#define spi.h

//Includes
#include "stm32g4xx_hal_spi.h"

class spi
  {
    SPI_HandleTypeDef spi_handle;
    
    //Not sure if MCU will always be a spi master
    //Might be good to have the scalability
    bool master;

    SPI_TypeDef *Instance;
    uint32_t Mode;                /*!< Specifies the SPI operating mode.
                                     This parameter can be a value of @ref SPI_Mode */

    uint32_t Direction;           /*!< Specifies the SPI bidirectional mode state.
                                     This parameter can be a value of @ref SPI_Direction */

    uint32_t DataSize;            /*!< Specifies the SPI data size.
                                     This parameter can be a value of @ref SPI_Data_Size */

    uint32_t CLKPolarity;         /*!< Specifies the serial clock steady state.
                                     This parameter can be a value of @ref SPI_Clock_Polarity */

    uint32_t CLKPhase;            /*!< Specifies the clock active edge for the bit capture.
                                     This parameter can be a value of @ref SPI_Clock_Phase */

    uint32_t NSS;                 /*!< Specifies whether the NSS signal is managed by
                                     hardware (NSS pin) or by software using the SSI bit.
                                     This parameter can be a value of @ref SPI_Slave_Select_management */

    uint32_t BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                     used to configure the transmit and receive SCK clock.
                                     This parameter can be a value of @ref SPI_BaudRate_Prescaler
                                     @note The communication clock is derived from the master
                                     clock. The slave clock does not need to be set. */

    uint32_t FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                     This parameter can be a value of @ref SPI_MSB_LSB_transmission */

    uint32_t TIMode;              /*!< Specifies if the TI mode is enabled or not.
                                     This parameter can be a value of @ref SPI_TI_mode */

    uint32_t CRCCalculation;      /*!< Specifies if the CRC calculation is enabled or not.
                                     This parameter can be a value of @ref SPI_CRC_Calculation */

    uint32_t CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation.
                                     This parameter must be an odd number between Min_Data = 1 and Max_Data = 65535 */

    uint32_t CRCLength;           /*!< Specifies the CRC Length used for the CRC calculation.
                                     CRC Length is only used with Data8 and Data16, not other data size
                                     This parameter can be a value of @ref SPI_CRC_length */

    uint32_t NSSPMode;            /*!< Specifies whether the NSSP signal is enabled or not .
                                     This parameter can be a value of @ref SPI_NSSP_Mode
                                     This mode is activated by the NSSP bit in the SPIx_CR2 register and
                                     it takes effect only if the SPI interface is configured as Motorola SPI
                                     master (FRF=0) with capture on the first edge (SPIx_CR1 CPHA = 0,
                                     CPOL setting is ignored).. */

	spi()





  }


// Key notes/ To do:: Will probably need some sort of array storing which gpio pins are available.
// Will also need some sort of array storing which spi pins are available

#endif


