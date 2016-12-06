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
#include "i2c.h"

void main(void)
{
	// uint8_t received_value;
	uint8_t SD_Error, FS_Error, index;
	uint16_t tot_entries, entry_input;
	uint32_t entry_cluster, temp_sector, current_sector, current_cluster, temp32;

	uint8_t xdata array_for_data[512];
	
	FS_values_t * drive_p;
	drive_p = Export_Drive_values();

	CKCON0 = CKCON_V;
	AUXR = 0x0C;

	LED_FLASH_Init();
	LED_Test();

	// LCD_Init();
	// LCD_Test();

	UART_Init(9600);
	UART_Test();

	// Memory_Test();
	// Xdata_Memory_Test();
	
	SPI_Master_Init(400000);
	SD_Error = SD_Init();
	SPI_Master_Init(20000000UL);

	I2C_Init(24000);
	I2C_Test();

	FS_Error = mount_drive();
	current_sector = drive_p -> FirstRootDirSec;
	printf("Reading Root Directory\n");

	while(1)
	{
		tot_entries = Print_Directory(current_sector, &array_for_data);
		printf("Enter a entry number to read : ");
		entry_input = (uint16_t) long_serial_input();

		if ((entry_input <= tot_entries) && (entry_input > 0)) {
			temp32 = Read_Dir_Entry(current_sector, entry_input, &array_for_data);
			if (temp32 & 0x80000000) {
				FS_Error = DIR_READ_ERROR;
			} else {
				entry_cluster = (temp32 & 0x0FFFFFFF);
				temp_sector = First_Sector(entry_cluster);
				if (temp32 & 0x10000000) {
					// Directory
					// tot_entries = Print_Directory(temp_sector, &array_for_data);
					current_sector = temp_sector;
				} else {
					// File
					index = 1;
					current_cluster = entry_cluster;
					do {
						if (index == drive_p -> SecPerClus) {
							current_cluster = Find_Next_Clus(current_cluster, &array_for_data);
							temp_sector = First_Sector(entry_cluster);
						}
						// printf("Current Sector value : %lu\n", temp_sector);
						SD_Error = Read_Sector(temp_sector, 512, &array_for_data);
						print_memory(512, array_for_data);
						printf("Press <1> to continue or <0> to exit!\n");
						// scanf("%u",&entry_input);
						entry_input = (uint16_t) long_serial_input();
						temp_sector ++;
						index ++;
					} while(entry_input!=0);
				}
			}
		} else {
			printf("Invalid Entry!\n");
		}

		// received_value = UART_Receive();
		// UART_Transmit(received_value);
		// LCD_Write(DATA,received_value);
	}
}