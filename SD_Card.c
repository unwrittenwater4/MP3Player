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
#include "hardware_delay_1ms.h"
#include <stdio.h>

uint8_t SD_Card_Ver;

//SD Card Send Command
//Inputs: Command and Argument
//Output: Error
uint8_t SD_Send_Command(uint8_t CMD_value, uint32_t argument) {
	uint8_t return_value, send_value, received_response = 0, error_flag;
	
	if(CMD_value < 64) {
		return_value = SD_NO_ERRORS;
		
		//Send Command
		send_value = 0x40 | CMD_value;
		error_flag = SPI_Transfer (send_value, &received_response);

		//Send Argument starting MSB to LSB
		send_value = (uint8_t)(argument >> 24);
		error_flag = SPI_Transfer (send_value, &received_response);
		send_value = (uint8_t)(argument >> 16);
		error_flag = SPI_Transfer (send_value, &received_response);
		send_value = (uint8_t)(argument >> 8);
		error_flag = SPI_Transfer (send_value, &received_response);
		send_value = (uint8_t)(argument);
		error_flag = SPI_Transfer (send_value, &received_response);

		if (CMD_value == CMD0){
			send_value = 0x95;
		}
		else if (CMD_value == CMD8){
			send_value = 0x87;
		}
		else {
			send_value = 0x01;
		}

		error_flag = SPI_Transfer(send_value, &received_response);

	} else {
		return_value = SD_ILLEGAL_COMMAND;
	}

	return return_value;
}


//SD Card Receive Command
//Inputs: Num of Bytes, Response array
//Output: Error
uint8_t SD_Receive_Response(uint8_t number_of_bytes, uint8_t* array_name){
	uint8_t time_out = 1, send_value, SPI_retval, index, return_value, error_flag;
	//Wait for R1 response
	//Repeatedly send 0xFF until received value != 0xFF

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
//Outputs: Error Status
uint8_t SD_Init(void){
	uint8_t received_response[5];
	uint8_t error_flag, error_status, iter = 0, time_out;

	//Power On
	printf("Initializing SD Card ...\n");
	SD_Select = 1;
	for(iter = 0; iter < 10; iter++){
		error_flag = SPI_Transfer(0xFF , &received_response);
	}

	//CMD0
	SD_Select = 0;
	error_flag = SD_Send_Command(CMD0,0);
	printf("CMD0 is sent ... ");
	error_flag = SD_Receive_Response(1, &received_response);
	SD_Select  =1;

	if(error_flag == SD_NO_ERRORS) {
		if (received_response[0] == 0x01) {
			error_status = SD_NO_ERRORS;
			printf("Response is 0x01\n");
		}
		else
			error_status = SD_RESPONSE_ERROR;
	}

	//CMD8
	if (error_status == SD_NO_ERRORS) {
		SD_Select = 0;
		error_flag = SD_Send_Command(CMD8,0x000001AA);
		printf("CMD8 is sent ... ");
		error_flag = SD_Receive_Response(5, &received_response);	//R1+R7 response
		SD_Select = 1;

		if (error_flag == SD_NO_ERRORS) {
			if(received_response[0] == SD_ILLEGAL_COMMAND) {
				//Old SD Card
				printf("Response is 0x05\n");
				printf("SD Card Ver 1.0\n");
				SD_Card_Ver = SD_VERSION_1;
			}
			else {
				printf("SD Card Ver 2.0\n");
				SD_Card_Ver = SD_VERSION_2;
			}

			if (received_response[0] == 0x01) {
				error_status = SD_NO_ERRORS;
				printf("Response is 0x01\n");
			}
			else
				error_status = SD_RESPONSE_ERROR;
		}
	}


	//CMD58
	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		error_flag = SD_Send_Command(CMD58, 0X000001AA);
		printf("CMD58 is sent ... ");
		error_flag = SD_Receive_Response(5, &received_response);		//R1+R3 response
		SD_Select = 1;

		if (error_flag == SD_NO_ERRORS){
			if (received_response[0] == 0x01){
				if ((received_response[3] & (0x80))>1)
					printf("Voltage is 2.7 to 2.8 V\n");
				else if ((received_response[2] & 0x01)>1)
					printf("2.8 to 2.9 V\n");
				else if ((received_response[2] & 0x02)>1)
					printf("2.9 to 3.0 V\n");
				else if ((received_response[2] & 0x04)>1)
					printf("3.0 to 3.1 V\n");
				else if ((received_response[2] & 0x08)>1)
					printf("3.1 to 3.2 V\n");
				else if ((received_response[2] & 0x10)>1)
					printf("3.2 to 3.3 V\n");
				else if ((received_response[2] & 0x20)>1)
					printf("3.3 to 3.4 V\n");
				else if ((received_response[2] & 0x40)>1)
					printf("3.4 to 3.5 V\n");
				else if ((received_response[2] & 0x80)>1)
					printf("3.5 to 3.6 V\n");
			}
		}
		else
			error_status = SD_RESPONSE_ERROR;
	}

	//ACMD41:
	//Sent by first sending CMD55 and recieving R1 response
	//Then sending CMD41 and recieving R1 response

	if (error_status == SD_NO_ERRORS){
		SD_Select = 0;
		printf("Sending ACMD41 ... ");
		do{
			error_flag = SD_Send_Command(CMD55, 0);
			if (error_flag == SD_NO_ERRORS){	
			
			 	error_flag = SD_Receive_Response(1, &received_response);
			
				if (received_response[0] == 0x01 || received_response[0] == 0x00) {
					if (SD_Card_Ver == SD_VERSION_1) {
						error_flag = SD_Send_Command(CMD41, 0x00);
						printf("CMD41 is sent with Argument 0\n");
					}
					else if (SD_Card_Ver == SD_VERSION_2) {
						error_flag = SD_Send_Command(CMD41, 0x40000000);
						printf("CMD41 is sent with HCS bit set\n");
					}
				}
				if (error_flag == SD_NO_ERRORS)
					error_flag = SD_Receive_Response(1, &received_response);
				
				time_out++;

				if (time_out == 0)
					error_flag = SD_TIMEOUT_ERROR;
			}
		} while((received_response[0] != 0x00) && (error_flag == SD_NO_ERRORS));
		SD_Select = 1;
	}

	//CMD58: Checking High Capacity
	if (error_status == SD_NO_ERRORS) {
		if (SD_Card_Ver == SD_VERSION_2){
			SD_Select = 0;
			error_flag = SD_Send_Command(CMD58, 0X000001AA);
			printf("CMD58 is sent ... ");
			error_flag = SD_Receive_Response(5, &received_response);		//R1+R3 response
			SD_Select = 1;
			
			if ((received_response[1] & 0xC0)) {
				printf("High Capacity card found.\n");
				SD_Card_Ver = SD_VERSION_2_HC;
			} else if ((received_response[1] & 0x80)) {
				printf("Standard Capacity card found.\n");
				printf("Standard Card not supported at the moment.\n");
			}
		}
	}
	return error_status;
}


//SD Card Read Block
//Inputs: Number of Bytes, Pointer to array in which the block will be stored 
//Outputs: Error Status
uint8_t SD_Read_Block(uint16_t number_of_bytes, uint8_t * array){
	uint8_t send_value, error_flag, error_status, time_out = 1, rec_value;
	uint16_t index;

	error_status = SD_NO_ERRORS;

	//Sending 0xFF and waiting for R1 Response
	do {
		send_value = 0xFF;
		error_flag = SPI_Transfer(send_value, &rec_value);
		time_out++;
	} while((rec_value != 0x00) && (time_out != 0));

	if (time_out == 0)
		error_status = SD_TIMEOUT_ERROR;

	if (error_status == SD_NO_ERRORS) {
		time_out = 1;
		do {
			error_flag = SPI_Transfer(0xFF, &rec_value);
			time_out++;
		} while((rec_value != 0xFE) && ((rec_value & 0xF0)!=0x00) && (time_out != 0));

		if (time_out == 0)
			error_status = SD_TIMEOUT_ERROR;

		if (rec_value == 0xFE){
			for(index = 0; index < number_of_bytes; index++){
				error_flag = SPI_Transfer(0xFF, &rec_value);
				array[index] = rec_value;
			}

			error_flag = SPI_Transfer(0XFF, &rec_value);
			error_flag = SPI_Transfer(0XFF, &rec_value);
			error_flag = SPI_Transfer(0XFF, &rec_value);
		} 
		else {
			error_status = rec_value;
		}
	}
	return error_status;
}