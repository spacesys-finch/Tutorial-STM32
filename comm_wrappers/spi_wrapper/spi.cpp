#include spi.h

/* 
Constructor. spi_instance needs to one of the values defined by macros: 
SPI1, SPI2 or SPI3 ... etc. The number of available macros depends on MCU.
example instantiation: spi(SPI2, false)
*/
spi::spi(SPI_TypeDef *spi_instance, bool poll_mode) {
  
  this->poll_mode = poll_mode
  
  this->spi_handle.Instance = spi_instance;
  this->spi_handle.Init.Mode = SPI_MODE_MASTER;
  this->spi_handle.Init.Direction = SPI_DIRECTION_2LINES;
  this->spi_handle.Init.DataSize = SPI_DATASIZE_8BIT;
  this->spi_handle.Init.CLKPolarity = SPI_POLARITY_LOW;
  this->spi_handle.Init.CLKPhase = SPI_PHASE_1EDGE;
  this->spi_handle.Init.NSS = SPI_NSS_SOFT;
  this->spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  this->spi_handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
  this->spi_handle.Init.TIMode = SPI_TIMODE_DISABLE;
  this->spi_handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  this->spi_handle.Init.CRCPolynomial = 7;
  this->spi_handle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  this->spi_handle.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&(this->spi_handle)) != HAL_OK)
  {
    Error_Handler();
  }
}

void spi::set_direction(uint32_t Direction) {
  this->spi_handle.Init.Direction = Direction;	
}

void spi::set_datasize(uint32_t DataSize) {
  this->spi_handle.Init.DataSize = DataSize;	
}

void spi::set_clkpolarity(uint32_t CLKPolarity) {
  this->spi_handle.Init.CLKPolarity = CLKPolarity;	
}

void spi::set_clkphase(uint32_t CLKPhase) {
  this->spi_handle.Init.CLKPhase = CLKPhase;	
}

void spi::set_nss(uint32_t NSS) {
  this->spi_handle.Init.NSS = NSS;	
}

void spi::set_baud_rate_prescaler(uint32_t BaudRatePrescaler) {
  this->spi_handle.Init.BaudRatePrescaler = BaudRatePrescaler;	
}

void spi::set_first_bit(uint32_t FirstBit) {
  this->spi_handle.Init.FirstBit = FirstBit;	
}

void spi::set_TI_mode(uint32_t TIMode) {
  this->spi_handle.Init.TIMode = TIMode;	
}

void spi::set_crc_calculation(uint32_t CRCCalculation) {
  this->spi_handle.Init.CRCCalculation = CRCCalculation;	
}

void spi::set_crc_polynomial(uint32_t CRCPolynomial) {
  this->spi_handle.Init.CRCPolynomial = CRCPolynomial;	
}

void spi::set_crc_length(uint32_t CRCLength) {
  this->spi_handle.Init.CRCLength = CRCLength;	
}

void spi::set_nssp_mode(uint32_t NSSPMode) {
  this->spi_handle.Init.NSSPMode = NSSPMode;	
}

void spi::check_init_constraints() {
  if (HAL_SPI_Init(&(this->spi_handle)) != HAL_OK)
  {
    Error_Handler();
  }
}