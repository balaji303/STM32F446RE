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

## Internal Flash
- The Size of Internal Flash is 512KB in STM32F446RE
