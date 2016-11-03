//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Header File for File System
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//
#ifndef _File_System_H 
#define _File_System_H

#define FS_NO_ERROR (0)
#define UNREADABLE_DRIVE (-1)
#define UNSUPPORTED_FAT16 (-2)

#include "main.h"
#include "port.h"
#include "Read_Sector.h"


uint8_t read8(uint16_t offset, uint8_t *array_name);
uint16_t read16(uint16_t offset, uint8_t *array_name);
uint32_t read32(uint16_t offset, uint8_t *array_name);

uint8_t mount_drive(void);

#endif
