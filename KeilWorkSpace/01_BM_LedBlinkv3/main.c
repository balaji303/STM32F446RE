/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief LED blink program using set and reset register
 * @version 1
 * @date 19-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
//BSRR set and reset register
//5 set and 21 reset register

#include "stm32f4xx.h"                  // Device header
void delay(int seconds); 
 
int main(void)
{
	RCC->AHB1ENR |= 1; 
	GPIOA->MODER |= 0x400;	 
	for(int i=0;i<5;i++)
	{
		GPIOA->BSRR |= 0x20;               //Set register  
		delay(1000);
		GPIOA->BSRR |= 0x200000;           //Re-set register
		delay(1000);
	}
	return 0;
}
 
/**
 * @brief Delay function
 * 
 * @param seconds 
 */
void delay(int seconds)
{
	for(;seconds>0;seconds--)
	{
		for(int count1=0;count1<3000;count1++);
	}
}
 

