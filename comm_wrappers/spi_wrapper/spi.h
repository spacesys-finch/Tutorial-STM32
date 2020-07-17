#ifndef spi.h
#define spi.h

//Includes
#include "stm32g4xx_hal_spi.h"

/* SPI wrapper Class. For the moment, will assume mcu
is the SPI master */
class spi
  {
    SPI_HandleTypeDef spi_handle; 
    bool poll_mode; //true = polling, false = interrupt 

    // Constructor
    spi(SPI_TypeDef *spi_instance, bool poll_mode);

    /* Functions to modify spi initialization pin settings.
    The constructor sets default pin settings. Make sure to run 
    check_init_constraints() once you've made all required changes.*/
    void set_direction(uint32_t Direction);
    void set_datasize(uint32_t DataSize); 
    void set_clkpolarity(uint32_t CLKPolarity);
    void set_clkphase(uint32_t CLKPhase);
    void set_nss(uint32_t NSS);
    void set_baud_rate_prescaler(uint32_t BaudRatePrescaler);
    void set_first_bit(uint32_t FirstBit);
    void set_TI_mode(uint32_t TIMode);
    void set_crc_calculation(uint32_t CRCCalculation);
    void set_crc_polynomial(uint32_t CRCPolynomial);
    void set_crc_length(uint32_t CRCLength);
    void set_nssp_mode(uint32_t NSSPMode);

    void check_init_constraints();

    //Write to slave
    void spi_write(uint8_t *write_data, uint16_t write_data_size, uint32_t timeout, GPIO_TypeDef *cs_port, uint32_t cs_pin, bool cs_active_high );

    //Read from slave
    void spi_read();

  }


//To do: set up the support for read/write. This needs to support interrupt vs spi mode
//To do: create file for stm32h7 hal msp spi functions.
//To do: figure out how to set compiler flags to choose between compiling h7 vs g4 files

#endif


