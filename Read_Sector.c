//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Read Sector Source Code File
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//
#include "Read_Sector.h"
#include "SD_Card.h"
#include "SPI.h"
#include "hardware_delay_1ms.h"
#include <stdio.h>









uint8_t	Read_Sector(uint32_t Sector_Number, uint16_t Sector_Size, uint8_t *array_for_data);
{
	SD_Select  = 0;
		SD_Error = SD_Send_Command(CMD17, block_number);
		if(SD_Error == SD_NO_ERRORS) 
			SD_Error = SD_Read_Block(Sector_Size, &array_for_data);
	SD_Select  = 1;
	print_memory(Sector_Size, &array);
}
