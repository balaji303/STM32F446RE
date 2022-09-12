//Video-10 UART Driver using system datasheet
//Protocol selected USART2
//USART2->APB1 bus
//RCC_APB1ENR is the APB1 enable register
//  Enable 1 at 17 bit for USART2
//USART2_TX-> PA2 Pin
//RCC_AHB1ENR is the AHB1 enable register
//  Enable 1 at 0 bit for PA2
//GPIOx_MODER is the Mode register
//  Enable 1 at 5 bit for alternate function
//Here we are using Alternate function of PA2 So, look for alternate
// Function diagram and find AF pin number
// Enable AF pin using Respective register
// GPIOx_AFRL


#include "stm32f4xx.h"                  // Device header
void USART2_Init(void);
void USART2_Write(char data);
void delay(int sec);
int main(void){
	USART2_Init();
	for(int count=0;count<2;count++){
	 USART2_Write('B');
		delay(1000);
		USART2_Write('A');
		delay(1000);
				USART2_Write('L');
		delay(1000);
		
				USART2_Write('A');
		delay(1000);
				USART2_Write('J');
		delay(1000);
		USART2_Write('I');
		delay(1000);
		USART2_Write('.');
		delay(1000);
		USART2_Write('V');
		USART2_Write('\r');
		USART2_Write('\n');
	}
	return 0;
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;              // Enable Bus for USART2
	RCC->AHB1ENR |= 0x1;                  //Enable Bus for GPIOA
	GPIOA->MODER |= 0x20;                 //Alernate Function for PA2
	GPIOA->AFR[0] |= 0x700;               //Selecting Alernate PIN USART2
	
	USART2->BRR |=0X683;                  //16MHz/9600 = 0x683
	USART2->CR1 |=0x8;                    //Enable Tx in Control Rregister
	USART2->CR1 |=0x2000;                 //Enable USART at last so everything is right
}

void USART2_Write(char data){
	while(!(USART2->SR & 0x80)){}  //if 0 enters loop, if 1 exit
	                               //This loop is for Tx buffer
	USART2->DR |= ( data );   //Sending data to the Data register
}

void delay(int sec){
	for(;sec>0;sec--){
		for(int count1=0;count1<3000;count1++);
     }
}

