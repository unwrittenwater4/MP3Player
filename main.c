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

void main(void)
{	uint8_t send_value, recieve_value, return_value;
	uint16_t baudrate;
	UART_Init(baudrate);
	send_value = 'U';

	while(1)
	{
		return_value = UART_Transmit(send_value);
		recieve_value = UART_Recieve();
	}
}