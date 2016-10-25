//------------------------------------------------------------------//
// SPI source code
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharsan; Sengupta, Ayush;
//------------------------------------------------------------------//


#include "SPI.h"
 
//SPI Initialization function
//Inputs: Clock Rate
//Outputs: Error Status (No Error or Illegal Clock Rate)
uint8_t SPI_Master_Init(uint32_t clock_rate) {
	uint8_t clock_divider, return_value = SPI_NO_ERROR;
	
	clock_divider = (uint8_t)((OSC_FREQ * 6)/(OSC_PER_INST * clock_rate));

	if (clock_divider <=2)
		SPCON = 0x70 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=4)
		SPCON = 0x71 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=8)
		SPCON = 0x72 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=16)
		SPCON = 0x73 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=32)
		SPCON = 0xF0 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=64)
		SPCON = 0xF1 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else if (clock_divider <=128)
		SPCON = 0xF2 | (CPOL_VALUE<<3) | (CPHA_VALUE <<2);
	else
		return_value = SPI_ILLEGAL_CLK_RATE;

	return return_value;
}

//SPI Transfer
//Inputs: Send Value and Pointer to Received Value
//Output: Error_Flag
uint8_t SPI_Transfer(uint8_t send_value, uint8_t* received_value) {
	uint8_t status_value, return_value;
	uint16_t timeout;

	timeout = 1;
	SPDAT = send_value;

	//waiting for transfer to complete and SPIF bit (Bit 7 of SPSTA)
	//to be set by hardware
	do {
		status_value = SPSTA;
		timeout++;
	} while ((status_value & 0xF0) == 0 && timeout !=0);

	if (timeout == 0){
		*received_value = 0xFF;
		return_value = SPI_TIMEOUT_ERROR;
	}
	else if ((status_value & 0x70) == 0) {
		*received_value = SPDAT;
		return_value = SPI_NO_ERROR;
	}
	else {
		*received_value = 0xFF;
		return_value = SPI_ERROR;
	}

	return return_value;

}
