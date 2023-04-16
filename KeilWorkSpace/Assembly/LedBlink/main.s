 ; Not Working
 ; This is a Assembly File
 ; |.text| means program callable by the C
 ; CODE means this is stored in RAM memory i.e, Programm memory 
 ; THUMB says the program is written in THUMB
 ;
RCC_AHB1ENR      EQU  0x40023830 ;0x40023800+0x30
GPIOA_MODER      EQU  0x40020000  ;0x4002 0000+0x00
GPIOA_BSRR       EQU  0x40020018  ;0x4002 0000+0x18
DELAY            EQU  0x000F
ONESEC           EQU  5333333
HSEC		      EQU  266667

				AREA |.text|,CODE, READONLY, ALIGN=2
				THUMB
				EXPORT Main
					
Main
		BL GPIO_Init
		B  Loop

Loop
		BL Led_On
		B  Loop
		
GPIO_Init
		LDR R1, = RCC_AHB1ENR ;Manipulate this register
		LDR R0,[R1]           ;Stored that into another register
		ORR R0,R0,#0x1        ;Manipulate its value
		STR R0,[R1]           ;Store it back to the register
		
		LDR R1, =GPIOA_MODER
		LDR R0,[R1]
		ORR R0,R0,#0x400
		STR R0,[R1]
		BX  LR
		
Led_On		
		LDR R1, =GPIOA_BSRR
		LDR R0,[R1]
		ORR R0,R0,#0x20
		STR R0,[R1]
		BX  LR
		ALIGN
		END
			
			