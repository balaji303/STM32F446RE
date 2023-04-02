
//https://cortex-m.com/lcd/
//PC0 to PC7 -> D0 to D7
//PB5 -> RS
//PB6 -> R/W
//PB7 -> EN

#include "stm32f4xx.h"                  // Device header

//#define RS 0x20  //0b0010 0000
//#define RW 0x40  //0b0100 0000
//#define EN 0x80  //0b1000 0000

void LcdInit(void);
void delay(int seconds);
void LcdData(char data);
void LcdCommand(unsigned char command);
void GpioInit(void);
int main(void){
	LcdInit();
	while(1){
		
		LcdData('H');
		LcdData('A');
		LcdData('P');
		LcdData('P');
		LcdData('Y');
		LcdData(' ');
		LcdData('D');
		LcdData('E');
		LcdData('E');
		LcdData('P');
		LcdData('A');
		LcdData('V');
		LcdData('A');
		LcdData('L');
		LcdData('I');
		LcdCommand(0xC0);//2ed Line
		LcdData(' ');
		LcdData(' ');
		LcdData('-');
		LcdData('B');
		LcdData('y');
		LcdData(' ');
		LcdData('B');
		LcdData('a');
		LcdData('l');
		LcdData('a');
		LcdData('j');
		LcdData('i');
		LcdData('.');
		LcdData('V');
		delay(10000);
		LcdCommand(1);//Clear screen
		delay(10);
	}
}
void LcdInit(void){
	GpioInit();
	//Init sequence
	delay(30);
	LcdCommand(0x30);
	delay(10);
	LcdCommand(0x30);
	delay(5);
	LcdCommand(0x30);
	
	LcdCommand(0x38); //set in 8bit data mode, 2Line, 5x7 font size
	LcdCommand(0x06); //move cursor right
	LcdCommand(0x01); //Clear Screen
	LcdCommand(0x0F); //turn on Display, blink cursor
}
void GpioInit(void){
	RCC->AHB1ENR|=0x06;  //0b0000 0110 Enable clock for GPIOB and GPIOC
	GPIOB->MODER|=0x5400;//Enable Output mode in PB5,PB6,PB7
	GPIOB->BSRR |=0xC00000;//Making RW and EN as low
	
	//PC0 to PC7 set as output
	GPIOC->MODER|=0x5555; //Enable Output mode PC0 to PC7	
}

void LcdCommand(unsigned char command){
	GPIOB->BSRR|=0x600000;//set RS and RW as Zero
  GPIOC->ODR=command;
  GPIOB->BSRR|=0x80;//Set the EN
  delay(1);
  GPIOB->BSRR|=0x800000;//Reset the EN	
}
void LcdData(char data){
  GPIOB->BSRR|=0x20;//set RS
	GPIOB->BSRR|=0x400000;//Reset RW
	GPIOC->ODR =data;
	GPIOB->BSRR|=0x80;//Set the EN
  delay(1);
  GPIOB->BSRR|=0x800000;//Reset the EN	
}
void delay(int seconds){
	int i;
	for(;seconds>0;seconds--){
		for(i=0;i<3195;i++);
	}
	
}

