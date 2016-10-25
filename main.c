//---------------------------------//
// Main Project File
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//

#include <stdio.h>
#include "main.h"
#include "port.h"
#include "uart.h"
#include "delay.h"
#include "blink.h"
#include "lcd.h"
#include "print_bytes.h"
#include "memory_test.h"
#include "unit_test.h"
#include "SPI.h"
#include "SD_Card.h"

void main(void)
{
	uint8_t received_value, SD_Error;
	uint8_t array[512];
	uint32_t block_number;

	CKCON0 = CKCON_V;

	LED_FLASH_Init();
	LED_Test();

	LCD_Init();
	LCD_Test();

	UART_Init(9600);
	UART_Test();

	Memory_Test();
	Xdata_Memory_Test();
	
	SPI_Master_Init(400000);
	SD_Error = SD_Init();
	SPI_Master_Init(20000000UL);
	
	while(1)
	{
		printf("Enter a block number to read : ");
		block_number = long_serial_input();
		SD_Select = 0;
		SD_Error = SD_Send_Command(CMD17, block_number);
		if(SD_Error == SD_NO_ERRORS) {
			SD_Error = SD_Read_Block(512, &array);
		}

		print_memory(512, &array);

		// received_value = UART_Recieve();
		// UART_Transmit(received_value);
		// LCD_Write(DATA,received_value);
	}
}