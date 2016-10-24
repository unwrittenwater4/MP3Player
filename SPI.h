//---------------------------------//
// Header file for SPI
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//



#ifndef _SPI_H
#define _SPI_H


#include "main.h"

#define no_errors 				0
#define SPI_ILLEGAL_CLK_RATE 	1
#define TIMEOUT_ERROR 			2
#define SPI_ERROR 				3

uint8_t SPI_Master_Init(uint32_t);
uint8_t SPI_Transfer(uint8_t, uint8_t*);

#endif