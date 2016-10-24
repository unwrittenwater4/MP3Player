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
	uint8_t ret_val, send_val, recieved_resp = 0, error_flag;
	
	if(CMD_value < 64){
		ret_val = SD_NO_ERRORS;
		
		//Send Command
		send_val = 0x40 | CMD_value;
		error_flag = SPI_Transfer (send_val, &recieved_resp);

		//Send Argument starting MSB to LSB
		send_val = (uint8_t)(argument >> 24);
		error_flag = SPI_Transfer (send_val, &recieved_resp);
		send_val = (uint8_t)(argument >> 16);
		error_flag = SPI_Transfer (send_val, &recieved_resp);
		send_val = (uint8_t)(argument >> 8);
		error_flag = SPI_Transfer (send_val, &recieved_resp);
		send_val = (uint8_t)(argument);
		error_flag = SPI_Transfer (send_val, &recieved_resp);

		if (CMD_value == CMD0){
			send_val = 0x95;
		}

		else if (CMD_value == CMD8){
			send_val = 0x87;
		}

		else {
			send_val = 0x01;
		}

		error_flag = SPI_Transfer(send_val, &recieved_resp);

	}
	else ret_val = SD_ILLEGAL_COMMAND;

	return ret_val;
}

uint8_t recieve_response(uint8_t number_of_bytes, uint8_t* array_name){
	uint8_t time_out = 0, send_val, SPI_retval, index, ret_val, error_flag;
	//Wait for R1 response
	//Repeatedly send 0xFF until recieved value != 0xFF

	do{
		send_val = 0xFF;
		error_flag = SPI_Transfer(send_val, &SPI_retval);
		time_out++;
	}while((SPI_retval == 0xFF) && (time_out != 0));

	if (time_out == 0 ) ret_val = SD_TIMEOUT_ERROR;
	else *array_name = SPI_retval;

	if((SPI_retval == 0x01) || (SPI_retval == 0x00))		//0x01 -> Idle state; 0x00-> active state
	{
		if (number_of_bytes > 1){
			for(index = 1; index < number_of_bytes; index++ ){
				error_flag = SPI_Transfer ( 0xFF, &SPI_retval);
				*(array_name + index) = SPI_retval; 
			}
		}

		ret_val = error_flag;
	}


	//Clearing Buffer
	error_flag = SPI_Transfer(0XFF, &SPI_retval);

	return ret_val;
}


//SD Card Initialization
//Inputs: None
//Outputs: None
void SD_Init(void){
	uint8_t recieved_resp[5];
	uint8_t error_flag, error_status, iter = 0;

	//Power On
	SD_Select = 1;
	for( iter = 0; iter < 10; iter++){
		error_flag = SPI_Transfer(0xFF , &recieved_resp);
	}

	//CMD0
	SD_Select = 0;
	error_flag = send_command(CMD0,0);
	error_flag = recieve_response(1, &recieved_resp);
	SD_Select  =1;

	if(error_flag == SD_NO_ERRORS){

		if (recieved_resp[0] = 0X01)	error_status = SD_NO_ERRORS;

		else 	error_status = SD_RESPONSE_ERROR;

	}


	//CMD8
	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		error_flag = send_command(CMD8,0X000001AA);
		error_flag = recieve_response(5, &recieved_resp);	//R1+R7 response
		SD_Select = 1;

		if (error_flag == SD_NO_ERRORS){
			if(recieved_resp[0] == 0X05){
				//OLd CARD
				error_status = SD_VERSION_1;
			}

			if (recieved_resp[0] == 0X01) 	error_status = SD_NO_ERRORS;
			//else	printf( " Voltage Problem \n ");

		}
	}


	//CMD58
	/*
	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		error_flag = send_command(CMD58, 0X000001AA);
		error_flag = recieve_response(5, &recieved_resp);		//R1+R3 response
		SD_Select = 1;

		if (error_flag == SD_NO_ERRORS){
			if (recieved_resp[0] == 0X01){
				if (recieved_resp[3] == ?)
			}
		}
	}
	*/

	//ACMD41:
	//Sent by first sending CMD55 and recieving R1 response
	//Then sending CMD41 and recieving R1 response

	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		error_flag = send_command(CMD55, 0X000001AA);
		error_flag = recieve_response(1, &recieved_resp);
		SD_Select = 1;

		if (recieved_resp[0] == 0x01){
			SD_Select = 0;
			error_flag = send_command(CMD41, 0X000001AA);
			error_flag = recieve_response(1, &recieved_resp);
			SD_Select = 1;


		}
	}


}
