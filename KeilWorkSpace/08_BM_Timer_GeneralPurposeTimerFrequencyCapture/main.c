/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief GPT Freq Capture
 * @version 1
 * @date 22-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
/*
AHB1 bus->GPIOA-> PA5->LED toggle and toggle is measured by 
AHB1 bus->GPIOA->PA6 outputs the toggle period and frequency
timer starts to count from CNT=0
when the counter reached ARR the counter matches and starts to count once again
*/

#include "stm32f4xx.h"                  // Device header

uint32_t period=0;
uint32_t frequency=0;

int main(void)
{
	uint32_t currentValue=0;
	uint32_t lastValue=0;
	RCC->AHB1ENR |=0x1;                   //Enable GPIOA
	GPIOA->MODER |=0x800;                 //Enable Alternate function
	GPIOA->AFR[0]|= 0x100000;             //Enable TIM2 as alternate function
	
	RCC->APB1ENR|= 0x3;                   //Enable TIM2 bus and TIM3
	TIM2->PSC    =1600-1;                 //Enable Prescalar
	TIM2->ARR    =10000-1;                //Enable Auto reset registers
	TIM2->CCMR1  =0x30;                   //Toggle on match of CCR1 and CNT
	TIM2->CCR1  =0;
	TIM2->CCER  =1;
	TIM2->CNT   =0;
	TIM2->CR1   =1;
	
	//PA6
	//RCC->AHB1ENR |=0x1;                 //Enable GPIOA
	GPIOA->MODER |=0x2000;                //Enable alternate function at PA6
	GPIOA->AFR[0]|=0x20000000;            //Enable TIM3 as alternate function
	
	RCC->APB1ENR |=0x2;                   //TIM3 bus
	TIM3->PSC    = 16000-1;               //Prescalar divide by 16000
	TIM3->CCMR1  =0x41;                    
	TIM3->CCER   =0x0B;                    
	TIM3->CR1    =1;
	
	while(1)
	{
		while((TIM3->SR & 2)!=0){}
		currentValue = TIM3->CCR1;
		period = currentValue - lastValue;
		lastValue = currentValue;
		frequency = 1000.00f/period;
		lastValue = currentValue;
	}
}

