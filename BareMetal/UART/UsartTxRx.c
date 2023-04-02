/*
Using USART2 both Tx and Rx
Usart2->APB1 bus
usart2_rx = PA3
usart2_tx = PA2
GPIOA->AHB1 bus
*/
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void Usart_Init(void);
int Usart_Write(int value);
int Usart_Read(void);

int main(void){
	int age;
	char name[100];
	Usart_Init();
printf("Hello World! I am STM32F446RE\r\n");
fprintf(stdout,"The test for stdout is successfully completed\r\n");
fprintf(stderr,"The test for stdin is successfully completed\r\n");
		printf("Enter your age:");
		scanf("%d",&age);
		printf("\r\n");
	  printf("Your age is %d\r\n",age);
		printf("Please give me your name:\r\n");
		gets(name);
	  printf("\r\n");
	  puts(name);
		printf("is that right? \r\n");
	return 0;
}

void Usart_Init(void){
	  RCC->AHB1ENR |=0x1;                //Enable GPIOA bus
		RCC->APB1ENR |=0x20000;      //Enable USART2 bus
	  GPIOA->MODER |=0xA0;               //Enable PA2,PA3 alternate function on pin
		GPIOA->AFR[0]|=0x7700;       //Enable alternate function
	
	  USART2->BRR  |=0x683;             //9600
		USART2->CR1	 |=0XC;     //ENABLE TX and RX
		USART2->CR1	 |=0x2000;  //ENABLE USART2
}

int Usart_Write(int value){    		    //Tx
    while(!(USART2->SR & 0x80)){}	    //Wait till data is not transfered to the shift register
		USART2->DR = (value & 0xFF);
		return value;
}

int Usart_Read(void){			    //Rx
	  while(!(USART2->SR & 0x20)){}	    //Wait till data is not receieved
		return USART2->DR;
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f){
	int c;
	c = Usart_Read();
	if(c == '\r'){
		Usart_Write(c);
		c = '\n';
	}
	Usart_Write(c);
	
	return c;
}

int fputc(int c, FILE *f){
    return Usart_Write(c);	
}

