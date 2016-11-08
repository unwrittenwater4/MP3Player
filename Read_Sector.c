//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Read Sector Source Code File
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//
#include "Read_Sector.h"
#include "SD_Card.h"
#include "print_bytes.h"
#include <stdio.h>

uint8_t	Read_Sector(uint32_t Sector_Number, uint16_t Sector_Size, uint8_t * array_for_data)
{
	uint8_t SD_Select, SD_Error;

	// printf("Value at %d+511 is %d\n", array_for_data, *(array_for_data+511));

	SD_Select  = 0;
	SD_Error = SD_Send_Command(CMD17, Sector_Number);

	if(SD_Error == SD_NO_ERRORS) {
		// printf("No Error!\n");
		SD_Error = SD_Read_Block(Sector_Size, array_for_data);
	}
	printf("Value at %d is %d\n", array_for_data, *array_for_data);
	
	SD_Select  = 1;
	if(SD_Error == SD_NO_ERRORS) {
		print_memory(Sector_Size, array_for_data);
	} else {
		printf("%d\n", SD_Error);
	}

	return SD_Error;
}
