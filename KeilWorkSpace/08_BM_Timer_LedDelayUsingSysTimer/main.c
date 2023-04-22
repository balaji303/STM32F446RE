/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief Blink the LED using the SysTick timer
 * @version 1
 * @date 22-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
/*
LED->PA5
PA5->GPIOA
GPIOA->AHB1 bus
*/

#include "stm32f4xx.h"                  // Device header
//#include "delay.h"                    //Own header file for delay function

int main(void)
{
	RCC->AHB1ENR |=0x1;                   //GPIOA enable
	GPIOA->MODER |=0X400;                 //Enable PA5 output mode
	
	//SysTick timer
	SysTick->LOAD = 6400000-1;            /*Changing  load value changes delay. Mmo. of cycles in single ms, if XTAL=64MHz then 64M cycles in one sec which is 64M/1000 in one millisec. Load takes values for 1ms*/
	SysTick->VAL = 0; /*Clear the current value register*/
	SysTick->CTRL = 5; /*Enable it*/
	
	while(1)
	{
		if(SysTick->CTRL & 0x10000)
		{
			GPIOA->ODR ^=0x20;
		}
	}
}

