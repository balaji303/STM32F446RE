
/*
Toggle LED every 1 sec from TIM2_CH1
reading the value from PA5 to PA6 (Timer caputure)
We are measuring the toggle rate of PA5 and connecting the toggle rate to PA6

TIM2 ->APB1
TIM2_CH1->PA5

TIM3->APB1
TIM3_CH1->PA6
*/ 
#include "stm32f4xx.h"                  // Device header
int timestamp=0;
int main(void){
	
	RCC->AHB1ENR |=0x1;                 //Enable GPIOA
	GPIOA->MODER |=0x800;             //Alternate function @ PA5
	GPIOA->AFR[0] |=0x100000;        //Enable TIM2 as alternate function
	
	RCC->APB1ENR |=0x1;                //Enable bus for TIMER2
	TIM2->PSC = 1600-1;                 //Prescalar 16MHz/1600=10k
	TIM2->ARR = 10000-1;               //Auto Reset Register 10k/10k=1 sec ~ 1 MHz
	TIM2->CCMR1 = 0x30;	       //ENABLE Toggle on
	TIM2->CCR1  = 0;                      //Set match value
	TIM2->CCER = 1;                       //Enable ch1 comepare mode
	TIM2->CNT = 0;		       //Clear Counter
	TIM2->CR1 = 1; 		       //ENABLE TIM2
	
	//Timer3
	RCC->AHB1ENR |=0x1;                   //Enable GPIOA
	GPIOA->MODER |=0x2000;                //Enable Alternare function @ PA6
	GPIOA->AFR[0]|= 0x2000000;            //Enable Alternate function as TIM3
	
	RCC->APB1ENR |=0x2;                    //Enable bus for TIMER3
	TIM3->PSC = 16000-1;                   //Prescalar
	TIM3->CCMR1 = 0x41;                    //Set CH1 to Capture at every edge
	TIM3->CCER = 1;                        //Enable ch1 compare mode
	TIM3->CR1 =1;                          //Enable TIM3
	
	while(1){
		while(!(TIM3->SR & 2 )){}
			timestamp = TIM3->CCR1;
	}
}
