//---------------------------------//
// Header file for initailize UART
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//



#ifndef _UART_H
#define _UART_H


#include "main.h"

/*----------------------------------
Define all the identifiers here
------------------------------------*/
// Values used in Baud Rate Reload calculation
#define SMOD1	1
// #define SMOD0	0		// This value is hardcoded in uart.c
#define SPD		1

//Functions to be used in UART
void UART_Init(uint16_t baudrate);
uint8_t UART_Transmit (uint8_t send_value);
uint8_t UART_Recieve (void);


#endif