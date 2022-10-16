/**
  ******************************************************************************
  * @file           : BootloaderFunctions.c
  * @brief          : Handler Functions for Bootloader are defined
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 @balaji303.
  * All rights reserved.
  *
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BootloaderFunctions.h"
#include "stm32f4xx_hal.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
typedef bool ( *funCmdTable )( uint32_t argc, char *argv[] );
typedef struct
{
   const char *pCmdName;
   funCmdTable pfunCmd;
   const char *pDesString;
} cmdTable_t;

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
#define MAX_CMDLINE_ARGS 5

/* Private variables ---------------------------------------------------------*/
static char                   *argvar[MAX_CMDLINE_ARGS + 1];

/* Private function prototypes -----------------------------------------------*/
const cmdTable_t bootCmdTable[] =
{
	{ "---Commands---",        help_cmd,         "---Description---"   },
	{ "1h",           help_cmd,                "Prints the boot command list"	  },
	{ "2id",          get_mcu_id,              "Prints the ID from the chip"      },
	{ "3ver",         get_boot_ver,            "Prints the version of Bootloader" },
	{ "5flash",       get_flash_status,        "Prints the Flash Protection status" },
	{ "13jump",       jump_to_address,         "Jumps Program counter to certain address" },
	{ "14erase",      erase_sector,            "Erases a sector in flash" },
	{ 0, 0, 0 }
};

bool verify_address(uint32_t goto_address);
/* Private user code ---------------------------------------------------------*/

/**
  * @brief  verifies the address
  * @retval bool
  */
bool verify_address(uint32_t goto_address)
{
	if( (goto_address >= SRAM1_BASE)
			&& (goto_address <= SRAM1_END) )
	{
		/* Address from 0x2000_0000 to 0x2001_BFFF whose size is 112KB*/
		return ADDR_VALID;
	}
	else if( (goto_address >= SRAM2_BASE)
				&& (goto_address <= SRAM2_END) )
	{
		/* Address from 0x2001_C000 to 0x2001_FFFF whose size is 16KB*/
		return ADDR_VALID;
	}
	else if( (goto_address >= FLASH_BASE)
				&& (goto_address <= FLASH_END) )
	{
		/* Address from 0x08000000UL to 0x0807FFFFUL whose size is 512KB*/
		return ADDR_VALID;
	}
	else if( (goto_address >= BKPSRAM_BASE)
				&& (goto_address <= BKP_SRAM_END) )
	{
		/* Address from 0x4248_0000 to 0x4248_4090 whose size is 4KB*/
		return ADDR_VALID;
	}
	else
	{
		return ADDR_INVALID;
	}
}

/**
  * @brief  Process the Bootloader commands and calls the respective function
  * @retval None
  */
void process_bootloader_command(void)
{
   char     *CmdString;
   uint32_t commandLen = 0;
   uint32_t argc = 0;
   bool NextArg = ( bool )true;
   bool isTaskCompleted = TASK_PENDING;
   uint16_t i;
   cmdTable_t const * CmdEntry;

   CmdString = &bootRxBuf[0];

   while ( *CmdString != 0 )
   {
      if ( *CmdString == ' ' )
      {
         *CmdString = 0;
         NextArg = ( bool )true;
      } /* end if() */
      else if ( NextArg )
      {
         if ( argc < MAX_CMDLINE_ARGS )
         {
            argvar[argc] = CmdString;
            argc++;
            NextArg = ( bool )false;
         } /* end if() */
         else
         {
            break;
         } /* end else() */
      } /* end if() */
 	 else
 	 {
 		 /* Do Nothing */
 	 }
      CmdString++;
   } /* end while() */

   if ( argc > 0 )
   {
      CmdEntry = bootCmdTable;

      while ( CmdEntry->pfunCmd != 0 )
      {
         if ( !strcasecmp( argvar[0], CmdEntry->pCmdName ) )
         {
            /* This is the line of code that is actually calling the handler function
               for the command that was received */
        	 isTaskCompleted = CmdEntry->pfunCmd( argc, argvar );
        	 if (isTaskCompleted != TASK_COMPLETED)
        	 {
        		 print_msg( "%s comment Failed!\r\n", argvar[0] );
        	 }
        	 else
        	 {
        		 /* Do Nothing */
        	 }
            break;
         } /* end if() */
    	 else
    	 {
    		 /* Do Nothing */
    	 }
         CmdEntry++;
      } /* end while() */

      if ( CmdEntry->pCmdName == 0 )
      {
            /* We reached the end of the list and did not find a valid command */
    	  	print_msg( "%s is not a valid command!\r\n", argvar[0] );
      } /* end if() */
 	 else
 	 {
 		 /* Do Nothing */
 	 }
   } /* end if() */
	 else
	 {
		 /* Do Nothing */
	 }
} /* end process_bootloader_command() */

/**
  * @brief  Prints the Bootloader version
  * @retval Bool
  */
bool get_boot_ver(void)
{
	print_msg( "[DBG_MSG]: BOOTLOADER_VERSION: %d\r\n",BOOTLOADER_VERSION );
	return TASK_COMPLETED;
}/* end of get_boot_ver */

/**
  * @brief  Prints the MCU's Chip ID
  * @retval Bool
  */
bool get_mcu_id(void)
{
	uint16_t chipId;
	chipId = ( uint16_t )((DBGMCU->IDCODE) & 0xffff) ;
	print_msg( "[DBG_MSG]: Chip ID: 0x%x\r\n",chipId );
	return TASK_COMPLETED;
}/* end of get_mcu_id */

/**
  * @brief  Prints the MCU's Chip ID
  * @retval Bool
  */
bool get_flash_status(void)
{
	FLASH_OBProgramInitTypeDef flashStatus;
	HAL_FLASHEx_OBGetConfig(&flashStatus);
	print_msg( "[DBG_MSG]: Flash Protection Status: 0x%X\r\n",flashStatus.RDPLevel );
	return TASK_COMPLETED;
}/* end of get_flash_status */

/**
  * @brief  jump_to_address
  * @retval Bool
  */
bool jump_to_address( uint32_t argc, char *argv[] )
{

	bool returnValue = TASK_PENDING;
	bool isAddrValid = ADDR_INVALID;
	if ( argc == 3 )
	{
		/* Argument count should be 2 */
 //		uint32_t gotoAddress = (uint32_t)atoi(argv[1]);
   		uint32_t gotoAddress = ( uint32_t )strtol( argv[1], NULL, 16 );
   		isAddrValid = verify_address(gotoAddress);
   		if(isAddrValid == ADDR_VALID)
   		{
			print_msg( "[DBG_MSG]: gotoAddress: 0x%X\r\n",gotoAddress );
			gotoAddress |= 1;
			void (*jump_func)(void) = (void *)gotoAddress;
			print_msg( "[DBG_MSG]: Performing Jump\r\n" );
			// todo jump results in Hard Fault
			jump_func();
			returnValue = TASK_COMPLETED;
		}
		else
		{
			print_msg( "[DBG_MSG]: goto-address is invalid\r\n" );
		}
	}
	else
	{
		print_msg( "[WRG_MSG]: Invalid Argu count. ex: 4jump <Jump to address>\r\n" );
		returnValue = TASK_PENDING;
	}
	return returnValue;
}/* end of jump_to_address */

/**
  * @brief  erase_sector
  * @retval Bool
  */
bool erase_sector( uint32_t argc, char *argv[] )
{

	bool returnValue = TASK_PENDING;
	bool isSectorValid = ADDR_INVALID;
	if ( argc == 2 )
	{
		/* Argument count should be 1 */
		uint32_t eraseSector = ( uint32_t )strtol( argv[1], NULL, 16 );
		uint32_t numSectorToErase = (uint32_t)atoi(argv[2]);
		isAddrValid = verify_address(gotoAddress);
		if(isAddrValid == ADDR_VALID)
		{
			print_msg( "[DBG_MSG]: gotoAddress: 0x%X\r\n",gotoAddress );
			gotoAddress |= 1;
			void (*jump_func)(void) = (void *)gotoAddress;
			print_msg( "[DBG_MSG]: Performing Jump\r\n" );
			// todo jump results in Hard Fault
			jump_func();
			returnValue = TASK_COMPLETED;
		}
		else
		{
			print_msg( "[DBG_MSG]: goto-address is invalid\r\n" );
		}
	}
	else
	{
		print_msg( "[WRG_MSG]: Invalid Argu count. ex: 4jump <Jump to address>\r\n" );
		returnValue = TASK_PENDING;
	}
	return returnValue;
}/* end of erase_sector */

/**
  * @brief  Prints the Command List
  * @retval Bool
  */
bool help_cmd(void)
{
	cmdTable_t  const *CmdLineEntry;
	print_msg( "Boot Command List:\r\n" );
   CmdLineEntry = bootCmdTable;
   while ( CmdLineEntry->pCmdName )
   {
      /* has partial command text been entered and no match? */
//      if ((1 == argc) ||
//          (2 == argc) && (NULL != strstr(CmdLineEntry->pCmdName, argv[1])))
//      {
    	  print_msg( "%20s: %s\r\n", CmdLineEntry->pCmdName, CmdLineEntry->pDesString );
         HAL_Delay(10);
//      }
      CmdLineEntry++;
   } /* end while() */
   return TASK_COMPLETED;
} /* end DBG_CommandLine_Help () */


