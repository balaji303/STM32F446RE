/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "BootloaderFunctions.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
UART_HandleTypeDef huart2;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define USER_BUTTON_PIN 	GPIO_PIN_13
#define USER_BUTTON_PORT	GPIOC
#define BUTTON_PRESSED		RESET
#define KBYTES_SIZE			1024
/* Function Returns */
#define TASK_COMPLETED		0
#define TASK_PENDING		1
#define ADDR_VALID			TASK_COMPLETED
#define ADDR_INVALID		TASK_PENDING

/* Flash Address and Size */
/* SRAM1(112 KB) */
#define SRAM1_SIZE			(112*KBYTES_SIZE)
#define SRAM1_END			(SRAM1_BASE+SRAM1_SIZE)
/* SRAM2(16 KB) */
#define SRAM2_SIZE			(16*KBYTES_SIZE)
#define SRAM2_END			(SRAM2_BASE+SRAM2_SIZE)
/* TOTAL FLASH (512 KB) */
#define TAL_FLASH_SIZE		(512*KBYTES_SIZE)
/* BACK-UP RAM (4 KB) */
#define BKP_SRAM_SIZE		(4*KBYTES_SIZE)
#define BKP_SRAM_END		(BKPSRAM_BASE+BKP_SRAM_SIZE)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
bool verify_crc(uint8_t *pData, uint32_t len, uint32_t crcFromHost);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define VRL_COM_UART 				&huart2
#define BOOT_DEBUG_MSG				1
#define FLASH_SECTOR2_BASE_ADDRESS 	0x08008000
#define BOOT_RX_SIZE				200

uint8_t bootRxBuf[BOOT_RX_SIZE]; //Buffer to receieve data from the user
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
