/*
 * stm32g4xx_nucleo_conf.h
 *
 *  Created on: May 9, 2020
 *      Author: ksb22
 */

#ifndef INC_STM32G4XX_NUCLEO_CONF_H_
#define INC_STM32G4XX_NUCLEO_CONF_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32G4XX_NUCLEO
  * @{
  */

/** @defgroup STM32G4XX_NUCLEO_CONFIG Config
  * @{
  */

/** @defgroup STM32G4XX_NUCLEO_CONFIG_Exported_Constants Exported Constants
  * @{
  */
/* Uncomment one of the board define below */
/* #define USE_NUCLEO_32 */
#define USE_NUCLEO_64

/* COM usage define */
#define USE_BSP_COM_FEATURE                 0U

/* COM log define */
#define USE_COM_LOG                         0U

/* IRQ priorities */
#define BSP_BUTTON_USER_IT_PRIORITY         15U
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* INC_STM32G4XX_NUCLEO_CONF_H_ */
