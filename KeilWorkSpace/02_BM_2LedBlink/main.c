/**
 * @file main.c
 * @author @balaji303 (https://github.com/balaji303)
 * @brief Blink 2 different LED
 * @version 1
 * @date 19-04-2023
 * 
 * Copyright (c) 2023 @balaji303
 * 
 */
#include "stm32f4xx.h"                  // Device header

#define GREEN_LED_PIN (1U<<10)
#define RED_LED_PIN (1U<<12)
#define AHB1_BUS_ENABLE (1U)
#define GREEN_HIGH (1U<<5)
#define RED_HIGH (1U<<6)
#define LOW (0U)

void GPIO_init(void);
void Red_LED(void);
void Green_LED(void);
void Both_LED(void);
void delaysec(uint32_t sec);


int main(void)
{
	GPIO_init();
	while(1)
	{
		// Red_LED();
		Both_LED();
	}
	return 0;
}

/**
 * @brief Initialise the clock and mode of the GPIO pins
 * 
 */
void GPIO_init(void)
{
	__disable_irq();
	RCC->AHB1ENR |= AHB1_BUS_ENABLE;        //Enable Clock for AHB1 Bus
	GPIOA->MODER |= RED_LED_PIN;			//D12 as Output
	GPIOA->MODER |= GREEN_LED_PIN;          //D13 as Output
	__enable_irq();
}

/**
 * @brief Function to blink the Red LED
 * 
 */
void Red_LED(void)
{

	GPIOA->ODR  = RED_HIGH;                 //Make D12 HIGH
	delaysec(1000);
	GPIOA->ODR  = LOW;                      //Make D12 LOW
	delaysec(1000);
	
}

/**
 * @brief Function to blink the Green LED
 * 
 */
void Green_LED(void)
{
	
	GPIOA->ODR  = GREEN_HIGH;               //Make D13 HIGH
	delaysec(1000);
	GPIOA->ODR  = LOW;                      //Make D13 LOW
	delaysec(1000);
	
}

/**
 * @brief Function to blink both LED
 * 
 */
void Both_LED(void)
{

	GPIOA->ODR  = RED_HIGH | GREEN_HIGH;    //Make both pin HIGH
	delaysec(1000);
	GPIOA->ODR  = LOW;                      //Make both pin LOW
	delaysec(1000);
	
}

/**
 * @brief Delay function
 * 
 * @param sec 
 */
void delaysec(uint32_t sec)
{
	for(;sec>0;sec--)
	{
		for(int i=0;i<3000;i++);
	}
}
