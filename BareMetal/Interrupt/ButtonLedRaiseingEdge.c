/*
Create a interrput function when button is leaving
LED toggles and count value increses
*/
#include "stm32f4xx.h"                  // Device header

uint8_t count=0;
int main(void){
	
	__disable_irq();
	//LED
	RCC->AHB1ENR |=0x1;                   //Enable bus GPIOA
  GPIOA->MODER |=0x400;                 //Output mode for GPIO
  //GPIOA->BSRR  |=0x200000;      	      //Reset mode
	
	//Button
	RCC->AHB1ENR |=0x4;                   //Enable bus GPIOC
	
	RCC->APB2ENR |=0x4000;                    //Enable SysCongif clock
	SYSCFG->EXTICR[3] |=0x20;                 //Since we are accessing EXTICR4 we write EXTICR[3] (count from 0)
	
	EXTI->IMR |=0X2000;                  //Unmask interrupt at 13
	EXTI->RTSR|=0x2000;                  //Enable interrupt at raiseing trigger
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);      //Enable IRQ and the interrupt occurs btw pin 10 to 15 so that argument 
	__enable_irq();
	while(1){}
}

void EXTI15_10_IRQHandler(void){       //Interrupt Handler function
	GPIOA->ODR ^=0x20;                   //Toggle LED
  for(int i=0;i<3000;i++){
	for(int j=1000;j>0;j--){}
		}
	count++;                             //Increment count value	
	EXTI->PR |=0x2000;                   //Clear Interrupt pending flag
}
