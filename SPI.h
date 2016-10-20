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

#define no_errors 0
#define illegal_clock_rate 1

uint8_t SPI_Master_Init(uint32_t);

#endif