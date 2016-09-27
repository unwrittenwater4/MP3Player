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

void main(void)
{
	uint8_t received_value;
	LED_FLASH_Init();
	LCD_Init();
	UART_Init(9600);
	while(1)
	{
		LED_FLASH_Change_State();
		received_value = UART_Recieve();
		UART_Transmit(received_value);
		LCD_Write(DATA,received_value);
		delay1s(1);
		LED_FLASH_Change_State();
		delay1s(1);
	}
}