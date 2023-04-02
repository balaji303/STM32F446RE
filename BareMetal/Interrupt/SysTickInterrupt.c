#include "stm32f4xx.h"                  // Device header

void LedInit(void);
int main(void){
	LedInit();
	__disable_irq();
	SysTick->LOAD=12000000;
	SysTick->VAL=0;
	SysTick->CTRL=7;
	__enable_irq();
	while(1){	}
}
void SysTick_Handler(void){
	GPIOA->ODR ^=0x20;              //Toggle PA5 LED
}
void LedInit(void){
  RCC->AHB1ENR|=0x1;               //GPIOA Enable
	GPIOA->MODER|=0x400;             //PA5 output 
}

