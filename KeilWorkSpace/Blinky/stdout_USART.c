/*-----------------------------------------------------------------------------
 * Name:    stdout_USART.c
 * Purpose: STDOUT USART Template
 * Rev.:    1.0.0
 *-----------------------------------------------------------------------------*/

/* Copyright (c) 2013 - 2016 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "stm32f4xx.h"                  // Device header
#include "RTE_Components.h"             // Component selection


//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------


// <h>STDOUT USART Interface

//   <o>Baudrate
#define USART_BAUDRATE          115200

//   <o>USART clock
#define USART_CLK             50000000

// </h>

/* Define  Baudrate setting (BRR) for USART */
#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))

/* Define  USART */
#define USARTx  USART2


/**
  Initialize stdout

  \return          0 on success, or -1 on error.
*/
int stdout_init (void) {

#ifdef RTE_Compiler_IO_STDOUT_User
  RCC->AHB1ENR  |=   ( 1ul <<  0);                        /* Enable GPIOA clock */
  RCC->APB1ENR  |=   ( 1ul << 17);                        /* Enable USART#2 clock */

  /* Configure PA3 to USART2_RX, PA2 to USART2_TX */
  GPIOA->AFR[0] &= ~((15ul << 4* 3) | (15ul << 4* 2) );
  GPIOA->AFR[0] |=  (( 7ul << 4* 3) | ( 7ul << 4* 2) );
  GPIOA->MODER  &= ~(( 3ul << 2* 3) | ( 3ul << 2* 2) );
  GPIOA->MODER  |=  (( 2ul << 2* 3) | ( 2ul << 2* 2) );

  USARTx->BRR  = __USART_BRR(USART_CLK, USART_BAUDRATE);  /* 115200 baud @ 12MHz   */
  USARTx->CR3    = 0x0000;                                /* no flow control */
  USARTx->CR2    = 0x0000;                                /* 1 stop bit */
  USARTx->CR1    = ((   1ul <<  2) |                      /* enable RX */
                    (   1ul <<  3) |                      /* enable TX */
                    (   0ul << 12) |                      /* 1 start bit, 8 data bits */
                    (   1ul << 13) );                     /* enable USART */
#endif
  return (0);
}


/**
  Put a character to the stdout

  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
int stdout_putchar (int ch) {

#ifdef RTE_Compiler_IO_STDOUT_User
  while (!(USARTx->SR & 0x0080));
  USARTx->DR = (ch & 0xFF);
#endif
  return (ch);
}
