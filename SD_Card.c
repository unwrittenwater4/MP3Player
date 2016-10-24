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


//SD Card Initialization
//Inputs:
//Outputs:
void SD_Init(void){
	uint8_t rec_value =0, sd_select;
	sd_select =0;
	send_command(0,0);
	receive_response(1, rec_value);
	sd_select  =1;
	if(error_flag == SD_NO_ERRORS)
	{ if (rec_value[0]=0X01)
		{ error_status = NO_ERRORS;
		else
		error_status=RESPONSE_ERROR;
		}

	}

	if (error_status == no_errors)
	{
		sd_select = 0;
		error_flag = send_command(8,0X000001AA);
		error_flag = receive_response(5,rec_value);
		sd_select =1;
		if (error_flag == no_errors)
		{
			if(rec_value[0] == 0X05)
			{
				//OLd CARD
				//error_status=version_1;

			}
			if (rec_value[0] == 0X01)
			{
				error_status = no_errors;
				else
					printf("Voltage Problem\n");
			}
		}

	}

}





//SD Card Command
//Inputs:
//Output:
uint8_t send_command(uint8_t CMD_value, uint32_t argument){
	uint8_t ret_val, send_val, rec_value = 0, error_flag;
	
	if(CMD_value < 64){
		ret_val = SD_NO_ERRORS;
		
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
	else ret_val = SD_ILLEGAL_COMMAND;

	return ret_val;
}

uint8_t recieve_response(uint8_t number_of_bytes, uint8_t* array_name){
	uint8_t time_out = 0, send_val, SPI_retval, index, ret_val;
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
			for(index = 0; index < number_of_bytes; index++ ){
				error_flag = SPI_Transfer ( 0xFF, &SPI_retval);
				*(array_name + index) = SPI_retval; 
			}
		}
		ret_val = SD_NO_ERRORS;
	}

	error_flag = SPI_Transfer(0XFF, &SPI_retval);
	return ret_val;
}


