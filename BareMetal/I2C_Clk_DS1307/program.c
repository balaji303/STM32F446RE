/*
Master Device -> STM32F446RE
Slave Device -> DS1307
Since It is a RTC, it got SEC
min, hour, day, month Year,

we are going to read the sec
and use that to toggle the LED

PIN's used
SCL-PB8
SDA-PB9
*/

#include "stm32f4xx.h"                  // Device header

#define SLAVEADDR 0x68

int i2cdata(char saeaddr, char mtraddr, char *data);
void i2cInit(void);
void delay(int msec);
void Ledinit(void);

int main(void){
	char secdata;
	Ledinit();
	i2cInit();
	while(1){
	i2cdata(SLAVEADDR,0,&secdata);
		if(secdata & 1){
			GPIOA->ODR|=0x20;
		}
		else{
			GPIOA->ODR&=~0x20;
		}
		delay(10);
	}
	
}

void i2cInit(void){
	//GPIO config
	RCC->AHB1ENR|=0x2; //Enable BUS for GPIOB as PB8 and PB9 are GPIOB
	RCC->APB1ENR|=0x200000; //Enable I2C1 as PB8 and PB9 are connected
	
	GPIOB->MODER|=0xA0000; //Enable Alternate Mode at PB8 and PB9
	
	GPIOB->AFR[1]|=0x44;   //Enable I2C as alternate function for PB8 and PB9
	
	GPIOB->OTYPER|=0x300;  //Making Both as Open-Drain (HIGH-> 0v; LOW-> Floating value, so pull up resistor is added in I2C, which makes the logic 1 from the pull up resister when the PIN is low and zero when high)
	
	GPIOB->PUPDR|=0x50000; //Pull-up PB8 and PB9
	
	//I2C config
	I2C1->CR1|=0x8000; //I2C1 is connected to PB and PB9, so I2C1 is software reset
	
	I2C1->CR2|=0x10;  //I2C1 is Frequency is set at 10MHz, [XTAL 10MHz]
	
	I2C1->CCR = 80;  //standard mode 100kHz clock
	
	I2C1->TRISE = 17; //Max Trigger Rise edge duration
	
	I2C1->CR1|=0x1; //Enable Peripharals
}



int i2cdata(char saeaddr, char mtraddr, char *data){
	
	volatile int temp;
	
	while(I2C1->SR2 & 2){    //If bus is busy, enters the loop	
		
		I2C1->CR1 |= 0x100;    //Start condition for I2C
	}
	while(!(I2C1->SR1 & 1)){}		//Start Master mode. wait till start condition is set
	//while(I2C1->SR1 ==0){};		//Start Master mode balaji
		
	I2C1->DR = saeaddr <<1;		//slave address+write is written in Data register, As slave address is 7bit mode left shift 
	while(!(I2C1->SR1 & 2)){}; 	//0-No end of address transmission, 1-End of address tranmission
	
	temp=I2C1->SR2;  					//Copy Status register value to temp variable
		
	while(!(I2C1->SR1 & 80)){};		//wait till data register is empty| 0-not empty | 1-Empty
	/*
1. I2C1->SR1 is 0, so while(!(I2C1->SR1 & 80)) = 1, enters loop
2. after few times I2C1->SR1 is 1, so while(!(I2C1->SR1 & 80)) = 0, exits loop
  */		
	I2C1->DR = mtraddr;			//Master address is sent to data register
		
	while(!(I2C1->SR1 & 80)){};		//wait till data register is empty| 0-not empty | 1-Empty
		
	I2C1->CR1|=0x100;		//Repeated Start Generation
		
	while(!(I2C1->SR1 & 1)){}		//wait till start flag is set
		
	I2C1->DR=saeaddr<<1 |1; //Address flag is sent in read and write mode
		
	while(!(I2C1->SR1 & 2)){}; 	//0-No end of address transmission, 1-End of address tranmission
		I2C1->CR1|=0X400;         //Enable Acknowledgement
		temp=I2C1->SR2;  					//Copy Status register value to temp variable
		
		I2C1->CR1|=0x200;					//Stop condition
		
	while(!(I2C1->SR1 & 40)){}; 	//Wait till RxNe is set 0-Data register empty| 1-Data register not empty
		
		*data++=I2C1->DR;
		
		return 0;
}


void Ledinit(void){ //LED is connected to PA5
	RCC->AHB1ENR|=0x1; //	Enalbe BUS for PA5
	GPIOA->MODER|=0x400; //Enable BUS for 
	GPIOA->ODR|=0x20; //Set LED
	GPIOA->ODR&=~0x20;//Reset LED
}


void delay(int msec){				//sudo delay function for 10MHz
		for(;msec>0;msec--){
			for(int i=0;i<3195;i++);
		}
}
