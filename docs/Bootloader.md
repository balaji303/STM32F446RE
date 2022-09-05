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

| BOOT1           | BOOT2 | Boot Mode   | Aliasing | Notes | 
|----------------|---------------|---------------|----------------|-----------|
| x           | 1 | Main Flash Memory   | Main Flash is selected as boot area | Notes |
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