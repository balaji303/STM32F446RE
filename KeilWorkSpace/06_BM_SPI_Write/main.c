/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief Write data using SPI1
 * @version 1
 * @date 21-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
/*
This is an Overview, This program has no working module

SPI write fundation program

PA7-SPI1_MOSI
PA6-SPI1_MISO
PA5-SPI1_SCK
PA4-SPI1_NSS

*/
#include "stm32f4xx.h"                  // Device header

void spiWriteData(unsigned char data);
void  spiInit(void);

int main(void)
{
	spiInit();
	spiWriteData('B');
	spiWriteData('A');
	spiWriteData('L');
	spiWriteData('A');
	spiWriteData('J');
	spiWriteData('I');
	return 0;
}

/**
 * @brief Init SPI1
 * 
 */
void  spiInit(void)
{
	RCC->AHB1ENR|=1; //Enable clock for port A
	RCC->APB2ENR|=0x1000; //Enable clock for SPI1
	GPIOA->MODER|=0xAA00; //Enable Alternate Function
	GPIOA->AFR[0]|=0x50500000; //Enable SPI1 in alternate function for PA5 and PA7
	
	GPIOA->MODER|=0x100; //Enable PA4 as output data register
	
	/*
	*MasterEnable,
	Set Buad rate as Fclk/64
	Internal Slave select
	Software slave select
	8-bit Data frame is set by default (0-8bit)
	*/
  SPI1->CR1|=0x31C;
	
	SPI1->CR2=0;
	SPI1->CR1|=0x40; //Enable SPI 
}

/**
 * @brief Write data using SPI1
 * 
 * @param data 
 */
void spiWriteData(unsigned char data)
{
	while(!(SPI1->SR &0x2)){} //Transmission empty or not
	
	GPIOA->BSRR|=0x100000; //Reset PA4
	
	SPI1->DR=data;  //Need to write in a spectific location instead of just data, as this is an overview

	while (SPI1->SR & 80){}; //Wait till tx buffer is not empty
		
	GPIOA->BSRR|=0x10; //Set PA4
}

