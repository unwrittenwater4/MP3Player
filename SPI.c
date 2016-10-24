//---------------------------------//
// SPI source code
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharsan;
//		  Sengupta, Ayush
//---------------------------------//


#include "SPI.h"
 
//SPI Initialization function
//Inputs: Clock Rate
//Outputs: Error Status (No Error or Illegal Clock Rate)
uint8_t SPI_Master_Init(uint32_t clock_rate){
	uint8_t clock_divider, ret_val = SPI_NO_ERROR;

	clock_divider = (uint8_t)((OSC_FREQ*6)/(OSC_PER_INST + clock_rate));

	if 	(clock_divider <=2)	SPCON = 0x70 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=4)	SPCON = 0x71 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=8)	SPCON = 0x72 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=16)	SPCON = 0x73 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=32)	SPCON = 0xF0 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=64)	SPCON = 0xF1 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=128)	SPCON = 0xF2 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else ret_val = SPI_ILLEGAL_CLK_RATE;

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
	} while ((status_value & 0xF0) == 0 && timeout !=0);

	if (timeout == 0){
		*recieved_value = 0xFF;
		ret_val = SPI_TIMEOUT_ERROR;
	}
	else if ((status_value & 0x70) == 0){			//Not so Sure about the Masking and == 0?
		*recieved_value = SPDAT;
		ret_val = SPI_NO_ERROR;
	}
	else {
		*recieved_value = 0xFF;
		ret_val = SPI_ERROR;
	}

	return ret_val;

}


