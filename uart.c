//---------------------------------//
// UART source code
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include "uart.h"

//----------------------------------//

/*--- UART Initialization function ---*/

void UART_Init(uint16_t baudrate)
{
	PCON &= 0x3F;	// Clear SMOD0 bit

	if(SMOD1 == 1)
		PCON |= 0x80;	// Set SMOD1 bit

	//Initialiazing SCON register
		SM0 = 0; SM1 = 1; //Mode 1
		REN = 1;
		SM2 = 0;
		TI = 1;			// SBUF Empty
		RI = 0;			// SBUF Empty

	//Disabling Interrupt
		ES =0;


	BDRCON = 0;
	BRL = 256-(((1+(1*SMOD1))*(1+(5*SPD))*OSC_FREQ)/(OSC_PER_INST*32*baudrate));
	BDRCON = (0x1C|(SPD<<1));	// Baud Rate Control Register

//UART Initialized
}


/*--- UART_Transmit ---*/

uint8_t UART_Transmit (uint8_t send_value)
{
	uint16_t timeout;
	uint8_t return_value;

	//wait for T1 to be set
	timeout =1;
	while ((TI == 0) && (timeout !=0))	timeout++;
	
	if (timeout == 0)
	{
		return_value = -1;
	}
	else
	{
		TI = 0;
		SBUF = send_value;
		return_value = send_value;
	}

	// Must add timeout error return option
	return return_value;

}

/*--- UART_Recieve ---*/

uint8_t UART_Recieve(void)
{
	uint8_t recieved_value;

	// wait for RI to be set
	while(RI == 0);

	recieved_value = SBUF;
	RI = 0;

	return recieved_value;
}
