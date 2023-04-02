/*
D2->PC10->button
D3->PB6->LED
D13->PA5->Always Blinking
When I press the button the LED should turn ON
*/
#include "stm32f4xx.h"                  // Device header
int count=0;
int main(void){
	__disable_irq();
  RCC->AHB1ENR|= 0X7;                  //GPIOB and GPIOC
  GPIOB->MODER |=0x1000;               //GPIOB output
  GPIOA->MODER |=0x400;                //GPIOA op
	GPIOB->PUPDR |=0x20000;
  RCC->APB2ENR|=0x4000;                //Enable SYSCFG
  SYSCFG->EXTICR[2] |=0x200;           //Enable interrupt from PC10
	
	EXTI->IMR|=0x400;                    //Unmask interrupt from PC10
	EXTI->FTSR|=0x400;                   //Enable Falling Edge
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq();
	
  while(1){
		GPIOA->BSRR |=0x20;	
	for(int i=0;i<3000;i++){
		for(int j=1000;j>0;j--){}
	}
	
	GPIOA->BSRR |=0x200000;
	for(int i=0;i<3000;i++){
		for(int j=1000;j>0;j--){}
	}
	}
}
void EXTI15_10_IRQHandler(void){
	count++;
	GPIOB->ODR |=0x400;
	for(int i=0;i<3000;i++){
		for(int j=1000;j>0;j--){}
	}
	
	GPIOB->ODR &=~0x400;
	for(int i=0;i<3000;i++){
		for(int j=1000;j>0;j--){}
	}	
	EXTI->PR|=0x400;
}

