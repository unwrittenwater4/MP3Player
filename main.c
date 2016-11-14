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
#include "File_System.h"
#include "Directory_Functions_struct.h"

void main(void)
{
	// uint8_t received_value;
	uint8_t SD_Error, FS_Error;
	uint16_t tot_entries, entry_input;
	uint32_t temp32;

	uint8_t xdata array_for_data[512];
	
	FS_values_t * drive_p;
	drive_p = Export_Drive_values();

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
	
	FS_Error = mount_drive();
	printf("Reading Root Directory\n");
	
	tot_entries = Print_Directory(drive_p -> FirstRootDirSec, &array_for_data);
	while(1)
	{
		printf("Enter a entry number to read : ");
		entry_input = (uint16_t) long_serial_input();

		if (entry_input < tot_entries) {
			temp32 = Read_Dir_Entry(drive_p -> FirstRootDirSec, entry_input, &array_for_data);
			printf("Cluster Number is %lu\n", temp32);
		}
		
		// SD_Error = Read_Sector(block_number, 512, &array_for_data);


		// received_value = UART_Receive();
		// UART_Transmit(received_value);
		// LCD_Write(DATA,received_value);
	}
}