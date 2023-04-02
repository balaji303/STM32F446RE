/*
Led Blink using General Purpose Timer Output Capture in TIM2
ARR playes a major role in delay
if ARR=1000 
10 000/1000 = 10 which means LED toggles 10 times a second 
(10 times for 1MHz)
*/
#include "stm32f4xx.h"                  // Device header

int main(void){
	RCC->AHB1ENR |=0x1;                  //Enable GPIOA
	GPIOA->MODER |=0x800;                //Enable alternative function
	GPIOA->AFR[0]|=0x100000;             //Enable TIM2 as GPIO function
	
	RCC->APB1ENR |=0X1;                  //Enable Bus for TIM2
	TIM2->PSC  =1600-1;                  //Prescalar with value 16M/1600=10k
	TIM2->ARR  =10000-1;                 //Auto reset register 10k/10k=1~1sec delay
	TIM2->CCMR1 =0x30;                   //Set output to toggle on MATCH
	TIM2->CCR1 = 0;                      //Set match mode
	TIM2->CCER |=1;                      //Enable CH1 compare mode
	TIM2->CNT  = 0;                      //Clear counter
	TIM2->CR1  = 1;                      //Enable TIM2
	
	while(1){}
}
