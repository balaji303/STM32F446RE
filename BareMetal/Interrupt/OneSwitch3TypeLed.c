/*PA5->LED
PC13->Button

When No button pressed blinks slowly
When button is pressed once blinks at medium speed
When button is pressed while blinking in medium speed it blinks fast
*/
#include "stm32f4xx.h"                  // Device header

int main(void){
	
	__disable_irq();
	RCC->AHB1ENR|=0x5;                    //Enable GPIOA and GPIOC
	GPIOA->MODER|=0x400;                  //PA5 output
	GPIOA->PUPDR|=0x800;                  //PullUp PA5
	
	RCC->APB2ENR|=0x4000;                 //Enable SYSCFG
	SYSCFG->EXTICR[3]|=0x20;             //Interrupt at PC13
	
	EXTI->IMR|=0x2000;                     //Unmask interrupt at PC13
	EXTI->FTSR|=0x2000;                    //Raising Interrupt
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	__enable_irq();
	while(1){
		GPIOA->ODR|=0x20;
		for(int i=0;i<3000;i++){
			for(int j=1000;j>0;j--){}
		}
		GPIOA->ODR&=~0x20;
		for(int i=0;i<3000;i++){
			for(int j=1000;j>0;j--){}
		}
	}//End of while(1)
}//End of main
void EXTI15_10_IRQHandler(){
	EXTI->PR|=0x2000;
	for(int k=0;k<10;k++){
	GPIOA->ODR|=0x20;
		for(int i=0;i<2000;i++){
			for(int j=500;j>0;j--){}
		}
	GPIOA->ODR&=~0x20;
		for(int i=0;i<2000;i++){
			for(int j=500;j>0;j--){}
		}
	}
  if(GPIOC->IDR & 0x2000){ }  //Do nothing
  else{
	    	for(int k=0;k<10;k++){
	        GPIOA->ODR|=0x20;
		         for(int i=0;i<1000;i++){
			         for(int j=200;j>0;j--){}
		            }
	        GPIOA->ODR&=~0x20;
		        for(int i=0;i<1000;i++){
			        for(int j=200;j>0;j--){}
		            }
	           }
	}			
		
	}	

