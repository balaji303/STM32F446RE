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
void delay(int seconds);
int main(void){
	 
	RCC->AHB1ENR |= 1;                   // Enable AHB1 BUS which is connected to PA5 via GPIO port A 
	GPIOA->MODER |= 0x400;               // in bits 0000 0000 0000 0000 0000 0100 0000 0000
	
	for(int i=0;i<5;i++){
	 GPIOA->ODR |=0x20;               //digitalWrite (13,high) in bits 0000 0000 0000 0000 0000 0000 0010 0000
	 delay(1);
	 GPIOA->ODR &=~0x20;              //digitalWrite (13,low)
	 delay(1);
	if(i==3)
                        {
			RCC->AHB1RSTR |= 1;              //Reset AHB1 bus register
			}
	}
 return 0;	
}

void delay(int seconds){
 int count,count1;
	for(count=0;count<1000;count++){
		for(count1=0;count1<3000;count1++);
	}
}

