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
	{ 0, 0, 0 }
};

/* Private user code ---------------------------------------------------------*/

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
        		 print_msg( "%s command Failed!", argvar[0] );
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
