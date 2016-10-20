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

#define Illegal_Command		

//Function Prototypes
uint8_t send_command(uint8_t , uint32_t );
uint8_t recieve_response(uint8_t , uint8_t* );




#endif