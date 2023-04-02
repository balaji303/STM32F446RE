/*
XTal = 16MHz
Toggle LED using General Purpose Timer Register
Here we use TIMER2 which is 32bit timer attached to APB1 bus
*/
#include "stm32f4xx.h"                  // Device header
int main(void){
	
	RCC->AHB1ENR |=0x1;                   //Enable GPIOA
	GPIOA->MODER |=0x400;									//Enable OUTPUT mode
	
	RCC->APB1ENR |=0x1;                   //Enable TIMER2
	TIM2->PSC = 1600-1;                   //16 000 000 divide by 1600 = 10000
	TIM2->ARR = 10000-1;                  //10 000 divide by 10000 = 1sec delay
	TIM2->CNT = 0;                        //Clear Timer Counter becoz not used
	TIM2->CR1 = 1;                        //Enable Timer control
	
	while(1){
	  while(!(TIM2->SR & 1)){}
			GPIOA->ODR ^= 0x20;                //Toggle GPIOA
			TIM2->SR=0;
	}
}
