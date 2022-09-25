# Bootloader Docs

## What is Bootloader?
- A bootloader, also spelled as boot loader or called boot manager and bootstrap loader, is a computer program that is responsible for booting a computer.

- When a computer is turned off, its software‍—‌including operating systems, application code, and data‍—‌remains stored on non-volatile memory. When the computer is powered on, it typically does not have an operating system or its loader in random-access memory (RAM). The computer first executes a relatively small program stored in read-only memory (ROM, and later EEPROM, NOR flash) along with some needed data, to initialize RAM (especially on x86 systems), to access the nonvolatile device (usually block device, eg NAND flash) or devices from which the operating system programs and data can be loaded into RAM.

- For Example 
  1. When we upload the code to the Arduino UNO from the IDE
  1. The board gets resets
  1. The Bootloader in the board runs and waits from the command from the debugger/programmer
  1. Then it receieves the code in the format of binary
  1. Stores the code in the respective flash it is programmer
  1. Once this is done it resets again
  1. This time the bootloader once completed jumps to the application code
  1. In case of boards like STM32F446RE which has a debugger in it
      1. When reset happens doesn't goes to bootloader
      1. Depending on the Status of certain pins (boot 0 or boot 1) they enter the specific regions of the flash
      1. This is controlled by the debuggger

## Boot Configuration

| BOOT1           | BOOT0 | Boot Mode   | Aliasing | Notes | 
|----------------|---------------|---------------|----------------|-----------|
| x           | 0 | Main Flash Memory   | Main Flash is selected as boot area | This means the content of 0x0800 is aliased with 0x0000 |
| 0           | 1 | System Memory   | System Memory is selected as boot area | This means the content of 0x1FFF is aliased with 0x0000 |
| 1           | 1 | Embedded SRAM   | Embedded SRAM is selected as boot area | This means the content of 0x2000 is aliased with 0x0000 |

## Internal Flash
- The Size of Internal Flash is 512KB in STM32F446RE
- Begins at 0x0800_0000 and Ends at 0x0807_FFFF
- There are 7 sector of different size and starting address, the code by default stored from sector 0
- Non-volatile Memory

## Internal Static RAM
- There are 2 SRAM
- SRAM 1  Begins at 0x2000_0000 and Ends at 0x2001_BFFF whose size is 112KB
- SRAM 2  Begins at 0x2000_0000 and Ends at 0x2000_0000 whose size is 16KB
- Used to store Global and static variables
- Used to store Stack and Heap
- Volatile Memory

## System Memory ROM
- Size is 30KB
- Begins at 0x1FFF_0000 and Ends at 0x1FFF_77FF
- Read Only
- By default this memory will not be used but we can configure to execute or boot the MCU from this memory 

## Facts
- Memory Aliasing
  - [ ] A Technique called "Memory Aliasing" is used to map the contents of Data in the User Flash (0x0800_0000) to the very 
  begining of the flash (0x0000_0000), we can also check using the memory window both the content of 0x0800_0000 and 0x0000_0000
  are completely same.
  - Using this method, on reset the MSP(Main Stack Pointer) goes to reset handler and continuse to jump to 0x0800_0000 on next run

## Boot Control
- Connect the USB to USART cable to the board in the following order
  | USB-USART Cable           | Board | 
  |----------------|---------------|
  | White (RXD)           | PC10 (USART3_TX) |
  | Green (TXD)           | PC11 (USART3_RX) |
  | Red           | NO CONNECT |
  | Black           | GND|
- Connect the BOOT0 pin to GND and Power Up the Board.
- Use the tool https://www.st.com/en/development-tools/flasher-stm32.html

## Setup Overview
- **USART2**->(Virtual Port for Bootloader command)->**BOOTLOADER**->(Debug Prints over USB-USART cable->**USART3**
- We will be using the first 2 sector (0 and 1 of size 16KB) of Internal Flash for our Bootloader and 
rom Sector 2 we will use for our application
![Flash Module Organisation](https://github.com/balaji303/STM32F446RE/blob/main/docs/Table4_RM.jpg)

## Bootloader Commands

| Host Sends | Command Code | Bootloader Replies   | Size of Reply | Notes | 
|----------------|---------------|---------------|----------------|-----------|
| BL_GET_VER           | 0x51 | Bootloader version number  | 1 Byte | This command is used to read the bootloader version from the MCU |
| BL_GET_HELP           | 0x52 | All supported Command codes   | 10 bytes | This command is used to know what are the commands supported by the bootloader |
| BL_GET_CID           | 0x53 | Chip identification number | 2 Bytes | This command is used to read the MCU chip identification number |
| BL_GET_RDP_STATUS    | 0x54 | Returns the FLASH Read Protection level | 1 Bytes | This command is used to read the Flash read protection level |
| BL_GO_TO_ADDR    | 0x55 | Success or Error Code | 1 Bytes | This command is used to jump bootloader to specified address |
| BL_FLASH_ERASE    | 0x56 | Success or Error Code | 1 Bytes | This command is used to mass erase or sector erase of the user flash |
| BL_MEM_WRITE    | 0x57 | Success or Error Code | 1 Bytes | This command is used to write data in to different memories of the MCU |
| BL_EN_R_W_PROTECT  | 0x58 | Success or Error Code | 1 Bytes | This command is used to enable read/write protect on different sectors of the user flash |
| BL_MEM_READ | 0x59 | Memory contents of length asked by the host | May vary | This command is used to read data from different memories of the microcontroller.TODO | 
| BL_READ_SECTOR_STATUS | 0x5A | All sector status | 2bytes | This command is used to read all the sector protection status |
| BL_OTP_READ | 0x5B | OTP contents | May Vary | This command is used to read the OTP contents. TODO |
| BL_DIS_R_W_PROTECT | 0x5C | Success or Error Code | 1byte | This command is used to disable read/write protection on different sectors of the user flash . This command takes the protection status to default state |

## Custom Bootloader Code Flow

1. On Reset of the MCU it goes to the reset handler
1. We do the Inits of necessary peripharals like
  1. GPIOs
  1. UART
  1. CRC
  1. Clocl
1. We need to check the status of USER Button, if pressed
  1. YES,Then read the data from the UART (Continue in Bootloader mode)
  1. No, Then jump to the application  ( Handover the control to application mode)


## VTOR

- The VTOR stands for Vector Table reallocation Register
- This is used to reallocate the vector table for the application code
- By default this VTOR is 0, which indicates there is only one vector table
- But now, there will be 2
  - One for Bootloader at 0x000000 which means VTOR = 0
  - Another for application at 0x8008000 whihc means VTOR needs to be 0x8008000
