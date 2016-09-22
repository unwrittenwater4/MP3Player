//---------------------------------//
// Main Project File
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include "main.h"
#include "uart.h"

void main(void)
{	uint8_t send_value, recieve_value, return_value;
	uint16_t baudrate;
	UART_Init(baudrate);

	while(1)
	{
		return_value = UART_Transmit(send_value);
		recieve_value = UART_Recieve();
	}
}