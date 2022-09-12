/*
PA3->Usart RX
PA5->LED

Input using Termianl Tools like TeraTerm
*/
#include "stm32f4xx.h"                  // Device header
void Usart2Init(void);
void systickDelay(int seconds);
void LedPlay(int value);
void LedInit(void);
int main(void){
	__disable_irq();
	LedInit();
	Usart2Init();
	USART2->CR1|=0x80;
	NVIC_EnableIRQ(USART2_IRQn);
	__enable_irq();
	while(1){}
}

void Usart2Init(void){
	RCC->AHB1ENR|=0x1;         //GPIOA Enable
	RCC->APB1ENR|=0x20000;     //USART2 Enable
	
	GPIOA->MODER|=0x80;        //Alternate function @ PA3
	GPIOA->AFR[0]|=0x7000;     //alternate fun PA3 to Uart Rx
	
	USART2->BRR|=0x683;        //BaudRate 9600
	USART2->CR1|=0x4;          //Rx Enable
	USART2->CR1|=0x2000;       //Enable Clock for USART
}

void LedInit(void){
	RCC->AHB1ENR|=0x1;         //GPIOA Enable
	GPIOA->MODER|=0x400;       //Led op
}

void LedPlay(int value){
	value =value%16;
	//value %= 16;
	for(;value>0;value--){
		GPIOA->BSRR|=0x20;
		systickDelay(1000);
		GPIOA->BSRR|=0x200000;
		systickDelay(1000);
	}	
}
void USART2_IRQHandler(void){
	uint8_t c;
	while(USART2->SR & 0x20){
		c=USART2->DR;		
		LedPlay(c);
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

