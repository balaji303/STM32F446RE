/*
Tigger GPIO's PWM based on timer
XTal=16MHz
prescalar value= 10 which means 16M/10= 1.6MHz of XTal
timer starts to count from CNT=0
when the counter reached ARR the counter matches and starts to count once again
The LED is turned ON for CCR1/ARR= 8889/26667 = times

Changing CCR1 value change the LED brightness
*/
#include "stm32f4xx.h"                  // Device header
 
 
int main(void){
uint32_t PwmValue=8889;         // range= 0 to 26667

RCC->AHB1ENR|=0x1;               //Enable Bus for GPIOA
GPIOA->MODER|=0x800;             //Enable Alternate mode @ PA5
GPIOA->AFR[0]|=0x100000;         //Enable TIM2 as alternate mode
	
RCC->APB1ENR|=0x1;               //Enable TIM2 bus
TIM2->PSC = 10-1;                //Prescalar divide by 10
TIM2->ARR = 26667-1;
TIM2->CNT = 0;
TIM2->CCMR1 |=0x60;              //PWM mode 1 (active state)
TIM2->CCER  =1;                  //Enable PWM ch1
TIM2->CCR1  = PwmValue-1;	         //Pulse width 0.3 of the period
TIM2->CR1   =1;                  //Start TIM2
	
	while(1){}
}
