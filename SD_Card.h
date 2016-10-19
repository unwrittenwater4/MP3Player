//---------------------------------//
// Header file for initailize SD_Card
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//


#ifndef _SD_CARD_H
#define _SD_CARD_H


#include "main.h"



//Function Prototypes
uint8_t send_command(uint8_t command, uint32_t argument);
uint8_t recieve_response(uint8_t number_of_bytes, uint8_t* array_name);




#endif