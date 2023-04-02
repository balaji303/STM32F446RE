//Button based LED
//Button is connected to PC13
//PC13 -> AHB1 bus
// LED is connected to PA5 
// PA5 -> AHB1 bus
//RCC_AHB1ENR is the bus enable register
// GPIOC is 2ed bit so 0x4 -button
// GPIOA is 0th bit so 0x1 -LED
// GPIOx_MODER is the mode register
// GPIOC->MODER is input so 00 at 26,27th bit
// GPIOA->MODER is output so 01 at 10,11th bit
// GPIOC->IDR is 13 so if 0x2000 comes then it goes high
// in this STM32F446RE PC13 is always high
// so we are going to turn off LED when high and vice versa
// LED glowing using set reset BSRR register
#include "stm32f4xx.h"                  // Device header
void delay(int sec);
int main(void){
      	RCC->AHB1ENR |= 0x4;   //Enable GPIOC
	      RCC->AHB1ENR |= 0x1;   // Enable GPIOA
				//GPIOC->MODER |= 0x0;   // Enabling input register
	     	GPIOA->MODER |= 0x400; //Enabling output register
	while(1){
	 if(GPIOC->IDR & 0x2000 ){   //Button not pressed
		 GPIOA->BSRR |=0x200000;   // LED LOW
		 delay(1000);
	 }
	 else{                       // Button pressed
		 GPIOA->BSRR |=0x20;       //LED HIGH
		 delay(1000);
	 }
 }
}

void delay(int sec){
	for(;sec>0;sec--){
		for(int count1=0;count1<3000;count1++);
     }
}

