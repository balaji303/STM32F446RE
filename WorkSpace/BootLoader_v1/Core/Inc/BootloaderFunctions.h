/**
  ******************************************************************************
  * @file           : BootloaderFunctions.h
  * @brief          : Header for BootloaderHandler.c file.
  *                   This file contains the common defines of the BootloaderHandler.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 @balaji303.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_BOOTLOADERFUNCTIONS_H_
#define INC_BOOTLOADERFUNCTIONS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
/* Private includes ----------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
#define BOOTLOADER_VERSION		(1U)

/* Exported functions prototypes ---------------------------------------------*/

bool get_boot_ver(void);
bool help_cmd(void);
bool get_flash_status(void);
bool jump_to_address( uint32_t argc, char *argv[] );
bool erase_sector( uint32_t argc, char *argv[] );
bool get_mcu_id(void);
void process_bootloader_command(void);
/* Private defines -----------------------------------------------------------*/

#endif /* INC_BOOTLOADERFUNCTIONS_H_ */
