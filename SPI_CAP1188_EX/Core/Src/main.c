/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
enum {
	TRANSFER_WAIT, TRANSFER_COMPLETE, TRANSFER_ERROR
};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef hlpuart1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
/* Buffers used for transmission */
uint8_t setCap1188AddrBuffer[] = { SET_CAP1188_SPI_ADDR };
uint8_t setCap1188WriteCmd[] = { SET_CAP1188_SPI_WRITE };

/* transfer state */
__IO uint32_t wTransferState = TRANSFER_WAIT;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
int32_t GPIO_CONFIG(uint32_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed,
		GPIO_TypeDef *GPIOx);
void cap_1188_spi_write(GPIO_TypeDef *cs_port, uint32_t cs_pin, uint8_t addr,
		uint8_t val);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_LPUART1_UART_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */

	/* Configure LED2 */
	BSP_LED_Init(LED2);

	/* Configure User push-button button */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	//Need to initialize GPIO slave select pin high to the touch sensor device
	//note that the chip select for cap1188 is active low!!!
	__HAL_RCC_GPIOC_CLK_ENABLE();
	static GPIO_TypeDef *cap1188_cs_port = GPIOC;
	uint32_t cap1188_cs_pin = GPIO_PIN_2;
	GPIO_CONFIG(cap1188_cs_pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,
			GPIO_SPEED_FREQ_VERY_HIGH, cap1188_cs_port);
	HAL_GPIO_WritePin(cap1188_cs_port, cap1188_cs_pin, GPIO_PIN_SET);

	/* Wait for User push-button press before starting the Communication */
	while (BSP_PB_GetState(BUTTON_USER) != GPIO_PIN_SET) {
		BSP_LED_Toggle(LED2);
		HAL_Delay(100);
	}
	BSP_LED_Off(LED2);

	// set up multi touching for SPI////////////////////////////////////////////////////////////////
	cap_1188_spi_write(cap1188_cs_port, cap1188_cs_pin, CAP1188_MULTITOUCH_ADDR,
			ENABLE_MULTITOUCH);

	// set up led linking for SPI///////////////////////////////////////////////////////////////////////
	cap_1188_spi_write(cap1188_cs_port, cap1188_cs_pin, CAP1188_LED_LINK_ADDR,
			CAP1188_LED_LINK);

	// If transactions ended successfully will have the LED ON
	BSP_LED_On(LED2);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Configure the main internal regulator output voltage 
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
	/** Initializes the CPU, AHB and APB busses clocks 
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
	RCC_OscInitStruct.PLL.PLLN = 85;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks 
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the peripherals clocks 
	 */
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
	PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief LPUART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_LPUART1_UART_Init(void) {

	/* USER CODE BEGIN LPUART1_Init 0 */

	/* USER CODE END LPUART1_Init 0 */

	/* USER CODE BEGIN LPUART1_Init 1 */

	/* USER CODE END LPUART1_Init 1 */
	hlpuart1.Instance = LPUART1;
	hlpuart1.Init.BaudRate = 115200;
	hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
	hlpuart1.Init.StopBits = UART_STOPBITS_1;
	hlpuart1.Init.Parity = UART_PARITY_NONE;
	hlpuart1.Init.Mode = UART_MODE_TX_RX;
	hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&hlpuart1) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN LPUART1_Init 2 */

	/* USER CODE END LPUART1_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
/**
 * @brief  TxRx Transfer completed callback.
 * @param  hspi: SPI handle
 * @note   This example shows a simple way to report end of Interrupt TxRx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	/* Turn LED2 on: Transfer in transmission/reception process is complete */
	BSP_LED_On(LED2);
	wTransferState = TRANSFER_COMPLETE;
}

/**
 * @brief  SPI error callbacks.
 * @param  hspi: SPI handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
	wTransferState = TRANSFER_ERROR;
}

/**
 * @brief  Select GPIO Pin to configure.
 * @param  Led Specifies the Led to be configured.
 *         This parameter can be one of following parameters:
 *           @arg  LED2
 * @retval BSP status
 */
int32_t GPIO_CONFIG(uint32_t Pin, uint32_t Mode, uint32_t Pull, uint32_t Speed,
		GPIO_TypeDef *GPIOx) {
	GPIO_InitTypeDef gpio_init_structure;

	/* Configure the GPIO_LED pin */
	gpio_init_structure.Pin = Pin;
	gpio_init_structure.Mode = Mode;
	gpio_init_structure.Pull = Pull;
	gpio_init_structure.Speed = Speed;

	HAL_GPIO_Init(GPIOx, &gpio_init_structure);
	HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_RESET);

	return BSP_ERROR_NONE;
}

void cap_1188_spi_write(GPIO_TypeDef *cs_port, uint32_t cs_pin, uint8_t addr,
		uint8_t val) {

	uint8_t addr_buffer[] = { addr };
	uint8_t tx_buffer[] = { val };

	uint8_t rx_buffer[BUFFERSIZE];

	//set up the Chip Select (active low for this device)
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);

	//set the address ///////////////////////////////
	if (HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) setCap1188AddrBuffer,
			(uint8_t*) rx_buffer, BUFFERSIZE) != HAL_OK) {
		Error_Handler();
	}
	while (wTransferState == TRANSFER_WAIT) {
	}
	wTransferState = TRANSFER_WAIT;

	if (HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) addr_buffer,
			(uint8_t*) rx_buffer, BUFFERSIZE) != HAL_OK) {
		Error_Handler();
	}
	while (wTransferState == TRANSFER_WAIT) {
	}
	wTransferState = TRANSFER_WAIT;
	/////////////////////////////////////////////////

	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);

	//set the write command and write the actual value ///
	if (HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) setCap1188WriteCmd,
			(uint8_t*) rx_buffer, BUFFERSIZE) != HAL_OK) {
		Error_Handler();
	}
	while (wTransferState == TRANSFER_WAIT) {
	}
	wTransferState = TRANSFER_WAIT;

	if (HAL_SPI_TransmitReceive_IT(&hspi1, (uint8_t*) tx_buffer,
			(uint8_t*) rx_buffer, BUFFERSIZE) != HAL_OK) {
		Error_Handler();
	}
	while (wTransferState == TRANSFER_WAIT) {
	}
	wTransferState = TRANSFER_WAIT;
	/////////////////////////////////////////////////

	//reset the chip select back to high
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
		/* Toggle LED2 for error */
		BSP_LED_Toggle(LED2);
		HAL_Delay(1000);
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
