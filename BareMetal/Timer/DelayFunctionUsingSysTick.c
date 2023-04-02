/*
Create a LED blink using Systick timer as delay function
*/
#include "stm32f4xx.h"                  // Device header
void systickDelay(int seconds);
int main(void){
	RCC->AHB1ENR |=0x1;                   //GPIOA enable
	GPIOA->MODER |=0X400;                 //Enable PA5 output mode
	
	while(1){
		systickDelay(1000);
		GPIOA->ODR ^= 0x20;
	}
}

void systickDelay(int seconds){
	SysTick->LOAD = 12000;  //Reload with number of clocks per second
	SysTick->VAL = 0;       //Clear current value register
	SysTick->CTRL = 5;      //Enable Systick
	
	//Wait until the count flag is set
	for(int i=0;i<seconds; i++){
		while(!(SysTick->CTRL & 0x10000)){}
	}
	SysTick->CTRL = 0;      //Resets systick delay
}
