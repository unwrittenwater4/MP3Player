//---------------------------------//
// Header file to initailize UART.C
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//



#ifndef UART_H
#define UART_H


#include "main.h"

/*----------------------------------
Define all the identifiers here
------------------------------------*/
//Can't undertsand this?
#define SMOD1	1
#define SMOD0	0
#define SPD		1

//Functions to be used in UART
void UART_Init(uint16_t baudrate);
uint8_t UART_Transmit (uint8_t send_value);
uint8_t UART_Recieve (void);


#endif