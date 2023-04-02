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
		USART2_Write('\r');
				USART2_Write('A');
		delay(1000);
				USART2_Write('J');
		delay(1000);
		USART2_Write('I');
		delay(1000);
		USART2_Write('.');
		delay(1000);
		USART2_Write('V');
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

/*******************************************************/
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
/***************************************************/

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

int main(void){
	spiInit();
	spiWriteData('B');
	spiWriteData('A');
	spiWriteData('L');
	spiWriteData('A');
	spiWriteData('J');
	spiWriteData('I');
	return 0;
}

void  spiInit(void){
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

void spiWriteData(unsigned char data){
	while(!(SPI1->SR &0x2)){} //Transmission empty or not
	
		GPIOA->BSRR|=0x100000; //Reset PA4
		
		SPI1->DR=data;  //Need to write in a spectific location instead of just data, as this is an overview
	
		while (SPI1->SR & 80){}; //Wait till tx buffer is not empty
			
		GPIOA->BSRR|=0x10; //Set PA4
}

/*****************************************/