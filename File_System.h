//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Header File for File System
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//
#ifndef _File_System_H 
#define _File_System_H


#include "main.h"
#include "port.h"
#include "Read_Sector.h"


uint8_t read8(uint16_t offset, uint8_t *array_name);
uint16_t read16(uint16_t offset, uint8_t *array_name);
uint32_t read32(uint16_t offset, uint8_t *array_name);







#endif
