//---------------------------------//
// Main Project File
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include <stdio.h>
#include "main.h"
#include "port.h"
#include "uart.h"
#include "delay.h"
#include "blink.h"
#include "lcd.h"
#include "print_bytes.h"
#include "memory_test.h"

void main(void)
{
	uint8_t received_value, i;
	uint8_t text01[] = "LCD Ready!";
	uint8_t text02[] = "UART Ready!";
	uint8_t *txt_ptr = &text01;
	
	if(OSC_PER_INST == 6)
		CKCON0 = 0x01;
	else if(OSC_PER_INST == 12)
		CKCON0 = 0x00;

	LED_FLASH_Init();
	LCD_Init();
	UART_Init(9600);
	for (i=0; i<4; i++) {
		LED_FLASH_Change_State();
		delay1s(1);
	}
	LCD_Write_String(txt_ptr);
	LCD_Write(COMMAND, (SET_ADDRESS|LINE2));
	i=0;
	while(text02[i]!=0x00)
		putchar(text02[i++]);
	
	printf("\n\r\n\r");

	txt_ptr = code_memory_init();
	print_memory(50, txt_ptr);

	printf("\n\r");

	txt_ptr = xdata_memory_init();
	print_memory(50, txt_ptr);
	
	while(1)
	{
		received_value = UART_Recieve();
		UART_Transmit(received_value);
		LCD_Write(DATA,received_value);
	}
}