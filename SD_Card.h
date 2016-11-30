//------------------------------------------------------------------//
// Header file for initailize SD_Card
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharsan; Sengupta, Ayush;
//------------------------------------------------------------------//


#ifndef _SD_CARD_H
#define _SD_CARD_H

#include "main.h"
#include "PORT.H"

#define CMD0					0
#define CMD8					8
#define CMD16					16
#define CMD17					17
#define CMD41					41
#define CMD42					42
#define CMD55					55
#define CMD58					58

#define SD_ILLEGAL_COMMAND 		0x05

#define SD_VERSION_1			1
#define SD_VERSION_2			2
#define SD_VERSION_2_HC			6

#define SD_NO_ERRORS		 	0x00
#define SD_TIMEOUT_ERROR		0xFE
#define SD_RESPONSE_ERROR		0xFD
#define SD_VOLTAGE_ERROR		0xFC
#define SD_OTHER_ERROR			0xF0

//Function Prototypes
uint8_t SD_Init(void);
uint8_t SD_Send_Command(uint8_t, uint32_t);
uint8_t SD_Receive_Response(uint8_t, uint8_t*);
uint8_t SD_Read_Block(uint16_t, uint8_t*);

#endif