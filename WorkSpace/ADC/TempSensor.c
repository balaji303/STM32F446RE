#include "stm32f4xx.h"                 // Device header
#include <stdio.h>
int Usart2Write(int ch);
void Usart2Init(void);
int data;
double voltage;
double celsius;
int main(void){
	RCC->AHB1ENR|=1;                   //Enable GPIOA
	
	RCC->APB1ENR|=1;                   //Enable TIM2
	TIM2->PSC =1200-1;                   //TIM2 prescalar
	TIM2->ARR =10000-1;                  //Auto Reset Reg
	TIM2->CNT=0;                         //Clear Counter
	TIM2->CCMR1 =0x6800;                 //Output Compare mode
	                                     //Output Compare 2 preload enable
	TIM2->CCER=0x10;                     //Compare 2 enable
	TIM2->CCR2=50-1;                     //Compare in CC2 channel                      
	TIM2->CR1 =1;                      //Counter enable
	
	//ADC Setup
	RCC->APB2ENR|=0x100;                 //Enable ADC1
	ADC->CCR|=0x800000;
	ADC->CCR&=~0x400000;                 //VBAT needs to be disabled for temp sensor
	
	ADC1->SMPR1 = 0X4000000;             //Sampling Time minimum 10us  
	ADC1->SQR3 =18;                      //First conversion in regular sequence
	ADC1->CR2 |=0x10000000;              //Tigger on Raising mode
	ADC1->CR2 |=0x03000000;              //TIM2 CC2 event
	ADC1->CR2 |=0x1;                     //Enable ADC
	Usart2Init();
	printf("STM32F446RE Temperature Sensor\r\n");
	while(1){
		while(!(ADC1->SR))
 		data=ADC1->DR;
		voltage= (double)data/4095*3.3;    //Largest 12 bit no.=4085
	  celsius= (voltage-0.76)/0.0025+25;
		printf("%df,%.2f\370C\r\n",data,celsius);
	}
}
void Usart2Init(void){
	RCC->APB1ENR|=0x20000;               //Enable USART2
	RCC->AHB1ENR|=0x1;                   //Enable GPIOA
	GPIOA->MODER|=0x20;                  //Enable alternate fun @PA2
	GPIOA->AFR[0]=0x700;                 //Enable USART2 as alternate fun
  
  USART2->BRR|=0x683;                  //Buad rate 9600	
	USART2->CR1 =0x8;                    //Enable Tx
	USART2->CR1|=0x2000;                 //Enable USART2
}
struct __FILE{int handle;};
FILE __stdout = {1};

int fputc(int c, FILE *f){
	return Usart2Write(c);
}

int Usart2Write(int ch){
	while(!(USART2->SR & 0x80)){}
	 USART2->DR=ch;
	 return ch;
}

