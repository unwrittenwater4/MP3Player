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
#include "uart.h"
#include "port.h"
#include "unit_test.h"
#include "delay.h"

void main(void)
{

	uint8_t send_value, recieve_value, return_value;
	uint16_t baudrate = 9600;

	if(OSC_PER_INST == 6)
		CKCON0 = 0x01;
	else if(OSC_PER_INST == 12)
		CKCON0 = 0x00;

	LED_FLASH_Init();
	UART_Init(baudrate);
	send_value = 'U';
		
	LED_FLASH_Change_State();
	delay1s(1);
	LED_FLASH_Change_State();
	delay1s(1);
	LED_FLASH_Change_State();
	delay1s(1);
	LED_FLASH_Change_State();
	delay1s(1);
	

	while(1)
	{
		return_value = UART_Transmit(send_value);
		// return_value = UART_Transmit(UART_Recieve());
	}
}