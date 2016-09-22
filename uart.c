//---------------------------------//
// UART source code
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include "main.h"
#include "uart.h"

//----------------------------------//

//UART Initialization function

void UART_Init(uint16_t baudrate)
{
	//SMOD1
	SMOD0 = 0;

	PCON

	//Initialiazing SCON register
	SM0 = 0; SM1 = 1; //Mode 1
	REN = 1;
	SM2 = 0;
	TI = 0;
	RI = 0;

	//Disabling Interrupt
	ES =0;

	TI =1;

	BDRCON = 0;
	//BRL = value
	BDRCON = (0x1C|(SPD<<1));

//UART Initialized
}
