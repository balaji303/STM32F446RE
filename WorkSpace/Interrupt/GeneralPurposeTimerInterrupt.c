/*
16MHz clock
*/
//With TIM2
/*
#include "stm32f4xx.h"                  // Device header

int main(void){
	__disable_irq();                      
	RCC->AHB1ENR|=0x1;                    //Enable GPIOA
	GPIOA->MODER|=0x400;                  //Enable PA5 as output
	
	RCC->APB1ENR|=0x1;                    //Enable TIM2
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CR1 =1;                         //Enable CR1
	TIM2->DIER|=0x1;                      //Update Interrupt enable
	
	NVIC_EnableIRQ(TIM2_IRQn);
	__enable_irq();
	while(1){}
}

void TIM2_IRQHandler(void){
	TIM2->SR =0;                          //Clear Interrupt Flag
	GPIOA->ODR ^=0x20;
}
*/
//with TIM3
/*
16MHz clock
*/
#include "stm32f4xx.h"                  // Device header

int main(void){
	__disable_irq();                      
	RCC->AHB1ENR|=0x1;                    //Enable GPIOA
	GPIOA->MODER|=0x400;                  //Enable PA5 as output
	
	RCC->APB1ENR|=0x2;                    //Enable TIM3
	TIM3->PSC = 1600-1;
	TIM3->ARR = 10000-1;
	TIM3->CR1 =1;                         //Enable CR1
	TIM3->DIER|=0x1;                      //Update Interrupt enable
	
	NVIC_EnableIRQ(TIM3_IRQn);
	__enable_irq();
	while(1){}
}

void TIM3_IRQHandler(void){
	TIM3->SR =0;                          //Clear Interrupt Flag
	GPIOA->ODR ^=0x20;
}

