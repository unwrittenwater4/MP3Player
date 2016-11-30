//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
// Header File for Read Sector
// Project: MP3 Player
// Author : Sengupta,Ayush; Singh, Siddharth; Vaidhun, Sudharsan;
//------------------------------------------------------------------------------------------------------------------
#ifndef _Read_Sector_H
#define _Read_Sector_H

#include "main.h"
#include "port.h"

uint8_t	Read_Sector(uint32_t Sector_Number, uint16_t Sector_Size, uint8_t *array_for_data);

#endif
