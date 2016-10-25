//------------------------------------------------------------------//
// SD source code
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharsan; Sengupta, Ayush;
//------------------------------------------------------------------//

#include "Main.h"
#include "SD_Card.h"
#include "SPI.h"

uint8_t SD_Card_Ver;

//SD Card Command
//Inputs:
//Output:
uint8_t SD_Send_Command(uint8_t CMD_value, uint32_t argument) {
	uint8_t return_value, send_value, recieved_response = 0, error_flag;
	
	if(CMD_value < 64) {
		return_value = SD_NO_ERRORS;
		
		//Send Command
		send_value = 0x40 | CMD_value;
		error_flag = SPI_Transfer (send_value, &recieved_response);

		//Send Argument starting MSB to LSB
		send_value = (uint8_t)(argument >> 24);
		error_flag = SPI_Transfer (send_value, &recieved_response);
		send_value = (uint8_t)(argument >> 16);
		error_flag = SPI_Transfer (send_value, &recieved_response);
		send_value = (uint8_t)(argument >> 8);
		error_flag = SPI_Transfer (send_value, &recieved_response);
		send_value = (uint8_t)(argument);
		error_flag = SPI_Transfer (send_value, &recieved_response);

		if (CMD_value == CMD0){
			send_value = 0x95;
		}
		else if (CMD_value == CMD8){
			send_value = 0x87;
		}
		else {
			send_value = 0x01;
		}

		error_flag = SPI_Transfer(send_value, &recieved_response);

	} else {
		return_value = SD_ILLEGAL_COMMAND;
	}

	return return_value;
}

uint8_t SD_Recieve_Response(uint8_t number_of_bytes, uint8_t* array_name){
	uint8_t time_out = 0, send_value, SPI_retval, index, return_value, error_flag;
	//Wait for R1 response
	//Repeatedly send 0xFF until recieved value != 0xFF

	do {
		send_value = 0xFF;
		error_flag = SPI_Transfer(send_value, &SPI_retval);
		time_out++;
	} while((SPI_retval == 0xFF) && (time_out != 0));

	if (time_out == 0 )
		return_value = SD_TIMEOUT_ERROR;
	else
		*array_name = SPI_retval;

	if((SPI_retval == 0x01) || (SPI_retval == 0x00))		//0x01 -> Idle state; 0x00-> active state
	{
		if (number_of_bytes > 1){
			for(index = 1; index < number_of_bytes; index++) {
				error_flag = SPI_Transfer (0xFF, &SPI_retval);
				*(array_name + index) = SPI_retval; 
			}
		}
		return_value = SD_NO_ERRORS;
	}
	else
		return_value = SD_RESPONSE_ERROR;

	//Clearing Buffer
	error_flag = SPI_Transfer(0XFF, &SPI_retval);

	return return_value;
}


//SD Card Initialization
//Inputs: None
//Outputs: None
uint8_t SD_Init(void){
	uint8_t recieved_response[5];
	uint8_t error_flag, error_status, iter = 0, time_out;

	//Power On
	SD_Select = 1;
	for(iter = 0; iter < 10; iter++){
		error_flag = SPI_Transfer(0xFF , &recieved_response);
	}

	//CMD0
	SD_Select = 0;
	error_flag = SD_Send_Command(CMD0,0);
	error_flag = SD_Recieve_Response(1, &recieved_response);
	SD_Select  =1;

	if(error_flag == SD_NO_ERRORS) {
		if (recieved_response[0] == 0x01)
			error_status = SD_NO_ERRORS;
		else
			error_status = SD_RESPONSE_ERROR;
	}

	//CMD8
	if (error_status == SD_NO_ERRORS) {
		SD_Select = 0;
		error_flag = SD_Send_Command(CMD8,0x000001AA);
		error_flag = SD_Recieve_Response(5, &recieved_response);	//R1+R7 response
		SD_Select = 1;

		if (error_flag == SD_NO_ERRORS) {
			if(recieved_response[0] == SD_ILLEGAL_COMMAND) {
				//Old SD Card
				SD_Card_Ver = SD_VERSION_1;
			}
			else
				SD_Card_Ver = SD_VERSION_2;

			if (recieved_response[0] == 0x01) {
				error_status = SD_NO_ERRORS;
			}
			else
				error_status = SD_RESPONSE_ERROR;
		}
	}


	//CMD58
	// if (error_status == SD_NO_ERRORS){
	// 	SD_Select = 0;
	// 	error_flag = SD_Send_Command(CMD58, 0X000001AA);
	// 	error_flag = SD_Recieve_Response(5, &recieved_response);		//R1+R3 response
	// 	SD_Select = 1;

	// 	if (error_flag == SD_NO_ERRORS){
	// 		if (recieved_response[0] == 0X01){
	// 			if (recieved_response[3] == )
	// 		}
	// 	}
	// }

	//ACMD41:
	//Sent by first sending CMD55 and recieving R1 response
	//Then sending CMD41 and recieving R1 response

	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		do{
			error_flag = SD_Send_Command(CMD55, 0);
			if (error_flag == SD_NO_ERRORS){	
			
			 	error_flag = SD_Recieve_Response(1, &recieved_response);
			
				if (recieved_response[0] == 0x01 || recieved_response[0] == 0x00)
					error_flag = SD_Send_Command(CMD41, 0X200001AA);
				if (error_flag == SD_NO_ERRORS)
					error_flag = SD_Recieve_Response(1, &recieved_response);
				
				time_out++;

				if (time_out == 0)
					error_flag = SD_TIMEOUT_ERROR;
			}
		} while((recieved_response[0] == 0x01) && (error_flag == SD_NO_ERRORS));
	}

	//CMD58: Checking High Capacity
	if (SD_Card_Ver == SD_VERSION_2){
		if (error_status == SD_NO_ERRORS){
			SD_Select = 0;
			error_flag = SD_Send_Command(CMD58, 0X000001AA);
			error_flag = SD_Recieve_Response(5, &recieved_response);		//R1+R3 response
			
			if (recieved_response[0]&0x80 == 0X80){
				
			}

		}	
	}
	return error_status;
}
