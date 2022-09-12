
/*
*  LED is connected to D13/PA5
*    Port A Pin 5
*    PA5 is connected to AHB1 bus
*    **Reference manual**
*    Enable AHB1 by RCC register
*    RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
*    RCC->AHB1ENRs
*    RCC AHB1 peripheral reset register (RCC_AHB1RSTR)
*    RCC_AHB1RSTR
*    GPIO Registers
*    GPIOx_MODER - Mode registers (2bits of data) 
*    GPIOx_IDR - Input data registers
*    GPIOx_ODR - Output Data register
*    0th place 1 is for Port A
*/
#include "stm32f4xx.h"                  // Device header
#define infinte 1
void delayMs(int seconds);
int main(void){
	 
	RCC->AHB1ENR |= 1;                   // Enable AHB1 BUS which is connected to PA5 via GPIO port A 
	GPIOA->MODER |= 0x400;               // in bits 0000 0000 0000 0000 0000 0100 0000 0000
	
	while(infinte){
	 GPIOA->ODR |=0x20;               //digitalWrite (13,high) in bits 0000 0000 0000 0000 0000 0000 0010 0000
	 delayMs(1000);
	 GPIOA->ODR &=~0x20;              //digitalWrite (13,low)
	 delayMs(1000);
	}	
}

void delayMs(int seconds){
	for(;seconds>0;seconds--){
		for(int count1=0;count1<3000;count1++);
	}
}

