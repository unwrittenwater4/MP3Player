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

/*--- UART Initialization function ---*/

void UART_Init(uint16_t baudrate)
{
	SMOD0 = 0;
	PCON = ((SMOD1<<7)|(SMOD0<<6));

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
	BRL = baudrate;
	BDRCON = (0x1C|(SPD<<1));

//UART Initialized
}


/*--- UART_Transmit ---*/

uint8_t UART_Transmit (uint8_t send_value)
{ uint16_t timeout; uint8_t return_value;
	//wait for T1 to be set
	timeout =1;
	while ((TI == 0) && (timeout !=0))	timeout++;

	SBUF = send_value;
	return_value = send_value;

	return return_value;

}


/*--- UART_Recieve---*/
