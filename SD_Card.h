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
#include "PORT.H"


#define CMD0					0
#define CMD8					8

#define CMD41					41
#define CMD42					42
#define CMD55					55
#define CMD58					58


#define SD_VERSION_1			1
#define SD_VERSION_2			2
#define SD_VERSION_2_HC			6

#define SD_NO_ERRORS		 	0
#define SD_ILLEGAL_COMMAND 		0x05
#define SD_TIMEOUT_ERROR		-12		
#define SD_RESPONSE_ERROR		-13



//Function Prototypes
void SD_Init(void);
uint8_t send_command(uint8_t , uint32_t );
uint8_t recieve_response(uint8_t , uint8_t* );




#endif