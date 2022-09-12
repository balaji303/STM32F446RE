
#include "stm32f4xx.h"                  // Device header
void delay(int sec);
void Usart_Init(void);
void Led_Init(void);
char Usart_Read(void);
void Led_play(int value);
int main(void){
	char ch;
	Led_Init();
	Usart_Init();
while(1)
{
  ch=Usart_Read();
	Led_play(ch);
}
	return 0;
}
void Usart_Init(void){
	RCC->APB1ENR |= 0x20000; //Enable AHB1
	RCC->AHB1ENR |= 0x1;     //Enable GPIOA->PA3
	GPIOA->MODER |= 0x80;    //Alernate Function at PA3
	GPIOA->AFR[0] |=0x7000;   //Enable USART2
	
	USART2->BRR |= 0x682;    //9600 Baud Rate
	USART2->CR1 |= 0x4;      //Rx Mode
	USART2->CR1 |= 0x2000;   //USART2 Enable
}

char Usart_Read(void){
while(!(USART2->SR & 0x20)){}    //Check the status register for Rx Buffer
	return USART2->DR;       //Return Data registers
}
void delay(int sec){
	for(;sec>0;sec--){
		for(int count1=0;count1<3000;count1++);
     }
}
void Led_Init(void){
	//Led ->PA5->AHB1
	RCC->AHB1ENR |= 0x1;   //GPIOA enable
	GPIOA->MODER |= 0x400; //Output enable 
}

void Led_play(int ch){
	ch %=16;
	for(;ch>0;ch--){
	GPIOA->BSRR  |= 0x20 ;      //Turn ON
	delay(1000);
	GPIOA->BSRR  |= 0x200000;   //Turn OFF
	delay(1000);
	}
}
