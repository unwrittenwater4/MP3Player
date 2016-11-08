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
#include "long_serial_in.h"
#include "unit_test.h"
#include "SPI.h"
#include "SD_Card.h"
#include "Read_Sector.h"

void main(void)
{
	// uint8_t received_value;
	uint8_t SD_Error;
	uint16_t sector_size = 512;
	uint8_t xdata array_for_data[512];
	uint32_t block_number;

	CKCON0 = CKCON_V;
	AUXR = 0x0C;

	LED_FLASH_Init();
	LED_Test();

	LCD_Init();
	LCD_Test();

	UART_Init(9600);
	UART_Test();

	// Memory_Test();
	// Xdata_Memory_Test();
	
	SPI_Master_Init(400000);
	SD_Error = SD_Init();
	SPI_Master_Init(20000000UL);
	
	printf("Value at %d is %d\n", &array_for_data + 511, array_for_data[511]);
	print_memory(sector_size, &array_for_data);

	while(1)
	{
		printf("Enter a block number to read : ");
		block_number = long_serial_input();

		// SD_Select  = 0;
		// SD_Error = SD_Send_Command(CMD17, block_number);

		// if(SD_Error == SD_NO_ERRORS) {
		// 	printf("No Error!\n");
		// 	SD_Error = SD_Read_Block(sector_size, &array_for_data);
		// }
		printf("Value at %d is %d\n", &array_for_data, array_for_data[0]);
		
		// SD_Select  = 1;
		// print_memory(sector_size, &array_for_data);
		
		SD_Error = Read_Sector(block_number, sector_size, &array_for_data);
		// print_memory(512, &array_for_data);

		// received_value = UART_Receive();
		// UART_Transmit(received_value);
		// LCD_Write(DATA,received_value);
	}
}