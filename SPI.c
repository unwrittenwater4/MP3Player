//---------------------------------//
// SPI source code
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//


#include "SPI.h"
 
//SPI Initialization function
//Inputs: Clock Rate
//Outputs: Error Status (No Error or Illegal Clock Rate)
uint8_t SPI_Master_Init(uint32_t clock_rate){
	uint8_t clock_divider, ret_val = no_errors;
	uint8_t CPOL_value = 0, CPHA_value = 0;

	clock_divider = (uint8_t)((OSC_FREQ*6)/(OSC_PER_INST + clock_rate));

	if 	(clock_rate <=2)	SPCON = 0x70 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=4)	SPCON = 0x71 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=8)	SPCON = 0x72 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=16)	SPCON = 0x73 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=32)	SPCON = 0xF0 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=64)	SPCON = 0xF1 | (CPOL_value<<3) | (CPOL_value <<2);
	else if (clock_rate <=128)	SPCON = 0xF2 | (CPOL_value<<3) | (CPOL_value <<2);
	else ret_val = illegal_clock_rate;

	return ret_val;
}

//SPI Transfer
//Inputs: Send Value and Pointer to Recieved Value
//Output: Error_Flag
uint8_t SPI_Transfer(uint8_t send_value, uint8_t* recieved_value){
	uint8_t status_value, ret_val;
	uint16_t timeout;

	timeout = 1;
	SPDAT = send_value;

	//waiting for transfer to complete and SPIF bit (Bit 7 of SPSTA)
	//to be set by hardware
	do{
		status_value = SPSTA;
		timeout++;
	}while ((status_value & 0xF0) == 0 && timeout !=0)

	if (timeout == 0){
		*recieved_value = 0xFF;
		ret_val = TIMEOUT_ERROR;
	}
	else if ((status_value & 0x70) == 0){			//Not so Sure about the Masking and == 0?
		*recieved_value = SPDAT;
		ret_val = no_errors;
	}
	else {
		*recieved_value = 0xFF;
		ret_val = SPI_Error;
	}

	return = ret_val;

}


