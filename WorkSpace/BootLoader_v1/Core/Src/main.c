/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;


UART_HandleTypeDef huart3;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CRC_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

void print_msg( char *format,... );
void jump_to_app(void);
void read_usr_cmd(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//UART_HandleTypeDef *UART
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	bool userButton;
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
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Transmit(VRL_COM_UART,(uint8_t *)"Hello from Bootloader!\r\n",15,HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* Get the User Button Status */
	  userButton = HAL_GPIO_ReadPin( USER_BUTTON_PORT, USER_BUTTON_PIN );
	  if ( userButton == BUTTON_PRESSED )
	  {
		  print_msg( "[DBG_MSG]: Button Pressed\r\n" );
		  jump_to_app();
	  }
	  else
	  {
		  print_msg( "[DBG_MSG]: Button Not Pressed\r\n" );
		  read_usr_cmd();
	  }
/*
 * uint32_t currentTick = HAL_GetTick();
	  print_msg( "[DBG_INFO]: curentTick = %d\r\n",currentTick );
	  while( HAL_GetTick() <= ( currentTick + 1000 ) )
	  {
		// Do Nothing
	  }
*/
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
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
  * @brief  This function is used to print string in Console over UART.
  * @retval None
  */
void print_msg( char *format,... )
{
#if ( BOOT_DEBUG_MSG == 1 )
	char data[100];
	va_list args;
	va_start(args, format);
	vsprintf(data, format, args);
	HAL_UART_Transmit( VRL_COM_UART, (uint8_t *)data, strlen(data), HAL_MAX_DELAY );
	va_end(args);
#endif
}

/**
  * @brief  This function is used to jump the code to app(0X0800_8000 or Sector 2)
  * 		or FLASH_SECTOR2_BASE_ADDRESS
  * @retval None
  */
void jump_to_app(void)
{
	/*	There are two things we need to take care before switching to App section
	 * 	1. Stack Pointer
	 * 		The very first address in app(0X0800_8000) holds the value of Main Stack Pointer
	 * 		(MSP)
	 *	2. Reset Handler
	 *		The next address in app(0x0800_8000+4) holds the value of the Reset Handler
	 * 	*/

	/* A function to hold the address of the reset handler */
	void (*app_reset_handler_addr)(void);
	print_msg("[DBG_MSG]: Started jump to application\r\n");

	/* 1.Get the MSP by reading the very first address in app */
	uint32_t mspValue = *(volatile uint32_t *)FLASH_SECTOR2_BASE_ADDRESS;
	print_msg("[DBG_INFO]: mspValue = %#x\r\n",mspValue);

	/* Sets the New MSP_value */
	__set_MSP(mspValue);

	/* 2.Get the resetHandlerAddr address from next address and set the new value */
	uint32_t resetHandlerAddr = *( volatile uint32_t *) (FLASH_SECTOR2_BASE_ADDRESS + 4);
	app_reset_handler_addr = (void *)resetHandlerAddr;

	print_msg("[DBG_INFO]: app_reset_handler_addr = %#x\r\n",app_reset_handler_addr);

	/* 3. Jump to the reset handler of the address */
	app_reset_handler_addr();

}

/**
  * @brief  This function is used read the commands from the user to process bootloader
  * @retval None
  */
void read_usr_cmd(void)
{
	uint8_t rxDataLen = 0;

	while(1)
	{
		memset(bootRxBuf, 0,  sizeof(bootRxBuf));
		/* First byte is the length of the command, check data frame for each command */
		HAL_UART_Receive(VRL_COM_UART, bootRxBuf, 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(VRL_COM_UART, bootRxBuf, 1, HAL_MAX_DELAY);
		if (isdigit(bootRxBuf[0]))
		{
			HAL_UART_Receive(VRL_COM_UART, &bootRxBuf[1], 1, 500);
			HAL_UART_Transmit(VRL_COM_UART, &bootRxBuf[1], 1, HAL_MAX_DELAY);
			if (isdigit(bootRxBuf[1]))
			{
				/* Gets Length as 2 Digit */
				rxDataLen = (uint8_t)( (( bootRxBuf[0] - 48 )*10) + (bootRxBuf[1] - 48) ) ; // Converting Hex to decimal
				HAL_UART_Receive(VRL_COM_UART, &bootRxBuf[2], rxDataLen, HAL_MAX_DELAY);
				HAL_UART_Transmit(VRL_COM_UART, &bootRxBuf[2], rxDataLen, HAL_MAX_DELAY);
			}
			else
			{
				/* Gets Length as 1 Digit */
				rxDataLen = (uint8_t)( bootRxBuf[0] - 48 );
				HAL_UART_Receive(VRL_COM_UART, &bootRxBuf[1], rxDataLen, HAL_MAX_DELAY);
				HAL_UART_Transmit(VRL_COM_UART, &bootRxBuf[1], rxDataLen, HAL_MAX_DELAY);
			}

			HAL_UART_Transmit(VRL_COM_UART,(uint8_t *)"\r\n",3,HAL_MAX_DELAY);
			process_bootloader_command();
		}
		else if(bootRxBuf[0] == 13)
		{
			print_msg("\r\n");
		}
		else
		{
			print_msg("\r\n[DBG_INFO]: Invalid Input. Enter \"1h\" for help\r\n");
		}
	}

}

/**
  * @brief  Used to verify the CRC generated by the host
  * @len 	Length to find CRC for
  * @retval None
  */
bool verify_crc(uint8_t *pData, uint32_t len, uint32_t crcFromHost)
{
	uint32_t accCrcValue = 0xff;
	uint32_t buffChar;

	/* Calculate the CRC for each byte */
	for(uint32_t i=0; i<len; i++)
	{
		buffChar = pData[i];
		accCrcValue = HAL_CRC_Accumulate(&hcrc, &buffChar, 1);
	}

	/* Verify the CRC accumulated with CRC from the host */
	if( accCrcValue == crcFromHost )
	{
		return TASK_COMPLETED;
	}
	else
	{
		return TASK_PENDING;
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

