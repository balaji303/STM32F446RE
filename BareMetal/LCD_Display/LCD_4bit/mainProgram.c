/*
LCD display  is used in 4bit mode

PC4-PC7 -> Data line
PB5 -> RS(0x20)
PB7 -> EN(0x80)
GND -> RW

*/
#include "stm32f4xx.h"                  // Device header
void delay(int seconds);
void GpioInit(void);
void LcdCommand(unsigned char command);
void LcdData(char data);
void NibbleWrite(char data,unsigned char control);
void LcdInit(void);

int  main(void){
	LcdInit();
	
	while(1){
		LcdData('B');
		LcdData('A');
		LcdData('L');
		LcdData('A');
		LcdData('J');
		LcdData('I');
		delay(1000);
		LcdCommand(0x01);
		delay(1000);
	}
	
}

void GpioInit(void){
	RCC->AHB1ENR|=0x6; //Enable Clock for GPIOB and GPIOC
	GPIOB->MODER|=0x4400; //Enable PB5 and PB7 as output in MODE register
	GPIOB->BSRR|= 0xA00000; //reset PB5 and PB7 in set/reset register
	
	GPIOC->MODER|=0x5500; //Enable PC4 to PC7 as output in MODE register
	GPIOC->BSRR|=0xF00000; //Reset PC4 to PC7 in set/reset register
}

void NibbleWrite(char data,unsigned char control){
	GPIOC->BSRR|=0xF00000; //Reset PC4 to PC7 in set/reset register
	GPIOC->BSRR|=data & 0xF0; //Only set required ports
	if(control & 0x20){
		GPIOB->BSRR|= 0x20; //Set RS
	}
	else{
		GPIOB->BSRR|= 0x200000; //reset RS
	}	
	GPIOB->BSRR|=0x80; //pulse Enable
	delay(10);
	GPIOB->BSRR|=0x800000;//reset
}

void delay(int seconds){
	int i;
	for(;seconds>0;seconds--){
		for(i=0;i<3195;i++);
	}
}

void LcdCommand(unsigned char command){
	
NibbleWrite(command & 0xF0,0); //Upper 4 bit
NibbleWrite(command<<4,0);		//Lower 4 bit
/*
	If the command is one or two we delay about 2milliseconds
	else any other command we delay about 40milliseeconds
*/
	if( command <4){
		delay(2);
	}
	else{
		delay(40);
	}
}

void LcdData(char data){
	NibbleWrite(data&0xF0,0x20); //Write Upper 4 bit
	NibbleWrite(data<<4,0x20);	//Write Lower 4 bit
	delay(10);
}

void LcdInit(void){
	GpioInit();

	//Init Sequence
	delay(30);
	NibbleWrite(0x30,0);
	delay(5);
	NibbleWrite(0x30,0);
	delay(1);
	NibbleWrite(0x30,0);
	delay(1);
	
	NibbleWrite(0x20,0); //set 4-bit data mode
	delay(1);
	
	LcdCommand(0x28); //4-bit mode, 2-line, 5x7 font
	delay(1);
	LcdCommand(0x06); //move cursor right
	LcdCommand(0x01); //clear screen
	LcdCommand(0x0F); //turn on screen and blink cursor
}
