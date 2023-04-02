#include "stm32f4xx.h"                  // Device header

int main(void){
	RCC->AHB1ENR |=0x1;                   //Enable GPIOA
	//By default all state are input
	GPIOA->MODER |=0x100000;              //LED output
	GPIOA->PUPDR |=0x200000;              //PullDown resister at D2
	GPIOA->ODR   |=0x400;                 //High
	while(1){}
}

