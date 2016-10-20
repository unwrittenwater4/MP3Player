//---------------------------------//
// SD source code
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include "Main.h"
#include "SD_Card.h"
#include "SPI.h"


//SD Card Command
//Inputs:
//Output:
uint8_t send_command(uint8_t CMD_value, uint32_t argument){
	uint8_t ret_val, send_val, rec_value = 0, error_flag;
	
	if(CMD_value < 64){
		ret_val = no_errors;
		
		//Send Command
		send_val = 0x40 | CMD_value;
		error_flag = SPI_Transfer (send_val, &rec_value);

		//Send Argument starting MSB to LSB
		send_val = (uint8_t)(argument >> 24);
		error_flag = SPI_Transfer (send_val, &rec_value);
		send_val = (uint8_t)(argument >> 16);
		error_flag = SPI_Transfer (send_val, &rec_value);
		send_val = (uint8_t)(argument >> 8);
		error_flag = SPI_Transfer (send_val, &rec_value);
		send_val = (uint8_t)(argument);
		error_flag = SPI_Transfer (send_val, &rec_value);

		if (CMD_value == CMD0){
			send_val = 0x95;
		}

		else if (CMD_value == CMD8){
			send_val = 0x87;
		}

		else {
			send_val = 0x01;
		}

		error_flag = SPI_Transfer(send_val, &rec_value);
	}
	else ret_val = illegal_command;
>>>>>>> dbf86a0cf256796edbfe56a032b07995a0808b50

	return ret_val;
}

uint8_t recieve_response(uint8_t number_of_bytes, uint8_t* array_name){
	
}

