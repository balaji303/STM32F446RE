/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief Configure a GPIO pin as Pull up resister
 * @version 1
 * @date 20-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |=0x1;                   //Enable GPIOA
	//By default all state are input
	GPIOA->MODER |=0x100000;              //LED output
	GPIOA->PUPDR |=0x100000;              //PullUp resister at D2
	GPIOA->ODR   |=0x400;                 //High
	while(1){}							  //Loop forever
}