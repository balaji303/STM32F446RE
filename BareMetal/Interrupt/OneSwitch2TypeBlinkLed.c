/*
PA5->LED
PC10->Button
*/
#include "stm32f4xx.h"                  // Device header

int main(void){
	
	__disable_irq();
	RCC->AHB1ENR|=0x5;                    //Enable GPIOA and GPIOC
	GPIOA->MODER|=0x400;                  //PA5 output
	
	RCC->APB2ENR|=0x4000;                 //Enable SYSCFG
	SYSCFG->EXTICR[2]|=0x200;             //Interrupt at PC10
	
	EXTI->IMR|=0x400;                     //Unmask interrupt at PC10
	EXTI->RTSR|=0x400;                    //Raising Interrupt
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq();
	while(1){
		GPIOA->ODR|=0x20;
		for(int i=0;i<1000;i++){
			for(int j=500;j>0;j--){}
		}
		GPIOA->ODR&=~0x20;
		for(int i=0;i<1000;i++){
			for(int j=500;j>0;j--){}
		}
	}//End of while(1)
}//End of main
void EXTI15_10_IRQHandler(){
	for(int k=0;k<2;k++){
	GPIOA->ODR|=0x20;
		for(int i=0;i<3000;i++){
			for(int j=1000;j>0;j--){}
		}
		GPIOA->ODR&=~0x20;
		for(int i=0;i<3000;i++){
			for(int j=1000;j>0;j--){}
		}
	}
	EXTI->PR|=0x400;	
}

