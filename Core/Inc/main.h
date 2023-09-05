/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void App_Main();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Drv_NSS_Pin GPIO_PIN_13
#define Drv_NSS_GPIO_Port GPIOC
#define M0_IB_Pin GPIO_PIN_0
#define M0_IB_GPIO_Port GPIOC
#define M0_IC_Pin GPIO_PIN_1
#define M0_IC_GPIO_Port GPIOC
#define ENC_NSS_Pin GPIO_PIN_1
#define ENC_NSS_GPIO_Port GPIOA
#define VBUS_Pin GPIO_PIN_6
#define VBUS_GPIO_Port GPIOA
#define Temp_Pin GPIO_PIN_5
#define Temp_GPIO_Port GPIOC
#define EN_GATE_Pin GPIO_PIN_12
#define EN_GATE_GPIO_Port GPIOB
#define M0_AL_Pin GPIO_PIN_13
#define M0_AL_GPIO_Port GPIOB
#define M0_BL_Pin GPIO_PIN_14
#define M0_BL_GPIO_Port GPIOB
#define M0_CL_Pin GPIO_PIN_15
#define M0_CL_GPIO_Port GPIOB
#define M0_AH_Pin GPIO_PIN_8
#define M0_AH_GPIO_Port GPIOA
#define M0_BH_Pin GPIO_PIN_9
#define M0_BH_GPIO_Port GPIOA
#define M0_CH_Pin GPIO_PIN_10
#define M0_CH_GPIO_Port GPIOA
#define Drv_SCK_Pin GPIO_PIN_10
#define Drv_SCK_GPIO_Port GPIOC
#define Drv_MISO_Pin GPIO_PIN_11
#define Drv_MISO_GPIO_Port GPIOC
#define Drv_MOSI_Pin GPIO_PIN_12
#define Drv_MOSI_GPIO_Port GPIOC
#define nFAULT_Pin GPIO_PIN_2
#define nFAULT_GPIO_Port GPIOD
#define ENC_SCK_Pin GPIO_PIN_3
#define ENC_SCK_GPIO_Port GPIOB
#define ENC_MISO_Pin GPIO_PIN_4
#define ENC_MISO_GPIO_Port GPIOB
#define ENC_MOSI_Pin GPIO_PIN_5
#define ENC_MOSI_GPIO_Port GPIOB
#define ENC_A_Pin GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOB
#define ENC_B_Pin GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define sqrt3 1.7320508075F
#define TPWM  5000

//LED宏定义
#define LED1_ON()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)
#define LED1_OFF()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET)
#define LED2_ON()   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)
#define LED2_OFF()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)

//SPI_NSS宏定义
#define DRV_SPI_ON()  HAL_GPIO_WritePin(Drv_NSS_GPIO_Port,Drv_NSS_Pin,GPIO_PIN_RESET)
#define DRV_SPI_OFF() HAL_GPIO_WritePin(Drv_NSS_GPIO_Port,Drv_NSS_Pin,GPIO_PIN_SET)
#define ENC_ON()      HAL_GPIO_WritePin(ENC_NSS_GPIO_Port,ENC_NSS_Pin,GPIO_PIN_RESET)
#define ENC_OFF()     HAL_GPIO_WritePin(ENC_NSS_GPIO_Port,ENC_NSS_Pin,GPIO_PIN_SET)

//Drv8301启动宏定义
#define DRV_ON()  HAL_GPIO_WritePin(EN_GATE_GPIO_Port,EN_GATE_Pin,GPIO_PIN_SET)
#define DRV_OFF() HAL_GPIO_WritePin(EN_GATE_GPIO_Port,EN_GATE_Pin,GPIO_PIN_RESET)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
