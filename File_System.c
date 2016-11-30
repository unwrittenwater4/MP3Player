//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Source Code for File System
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//

#include "File_System.h"
#include <stdio.h>
#include "Directory_Functions_struct.h"
// #include "Directory_Functions.h"

uint32_t idata MBR_RelSec = 0;

// Function to Read 8-bit Value from XRAM Memory
uint8_t read8(uint16_t offset, uint8_t *array_name) {
	uint8_t return_val;
	
	return_val = *(array_name+offset);
	// printf("%bu\n", return_val);
	
	return return_val;
}

// Function to Read 16-bit Value from XRAM Memory and Converts the little enfdian format
uint16_t read16(uint16_t offset, uint8_t *array_name) {
	uint16_t return_val=0;
	uint8_t temp, index;
	
	for (index = 2; index > 0; index--)
	{
		temp = *(array_name+offset+index-1);
		return_val = return_val << 8;
		return_val = return_val | temp;
	}

	// printf("%u\n", return_val);

	return return_val;
}

// Function to Read 32-bit Value from XRAM Memory and Converts the little enfdian format
uint32_t read32(uint16_t offset, uint8_t *array_name) {
	uint32_t return_val = 0;
	uint8_t temp, index;
	for (index = 4; index > 0; index--)
	{
		temp = *(array_name+offset+index-1);
		return_val = return_val << 8;
		return_val = return_val | temp;

	}
	// printf("%lu\n", return_val);
	return return_val;

}

uint8_t mount_drive(void) {
	uint8_t error_flag = FS_NO_ERROR, temp8;
	uint8_t xdata xdata_array[512];

	uint8_t idata numFATs;
	uint16_t idata rsvdSecCnt, rootEntCnt;
	uint32_t idata totSec, FATSz, hiddenSec, rootClus, dataSec, clusCnt;

	FS_values_t * drive_p;
	drive_p = Export_Drive_values();

	error_flag = Read_Sector(0, 512, &xdata_array);

	temp8  = read8 (  0, &xdata_array);
	
	if((temp8 != 0xEB) && (temp8 != 0xE9)) {
		printf("Reading Master Boot Record\n");
		MBR_RelSec = read32(0x01C6, &xdata_array);
		error_flag = Read_Sector(MBR_RelSec, 512, &xdata_array);
		temp8 = read8(0, &xdata_array);

		if((temp8 != 0xEB) && (temp8 != 0xE9)) {
			error_flag = UNREADABLE_DRIVE;
		}
	}

	if(error_flag==FS_NO_ERROR) {
		drive_p -> BytesPerSec = read16(0x0B, xdata_array);
		drive_p -> SecPerClus = read8(0x0D, xdata_array);
		rsvdSecCnt = read16(0x0E, xdata_array);
		numFATs = read8(0x10, xdata_array);
		rootEntCnt = read16(0x11, xdata_array);
		totSec = read16(0x13, xdata_array);
		FATSz = read16(0x16, xdata_array);
		hiddenSec = read32(0x1C, xdata_array);

		if(totSec == 0) {
			totSec = read32(0x20, xdata_array);
		}
		if(FATSz == 0) {
			FATSz = read32(0x24, xdata_array);
			rootClus = read32(0x2C, xdata_array);
		}

		// Calculation for Root Directory Sectors
		drive_p -> RootDirSecs = (rootEntCnt*32+ drive_p -> BytesPerSec -1)/(drive_p -> BytesPerSec);

		// Calculation for Data Sectors
		dataSec = totSec - (rsvdSecCnt + drive_p -> RootDirSecs + FATSz*numFATs);

		// Calculation for Count of Clusters
		clusCnt = dataSec / drive_p -> SecPerClus;

		if (clusCnt < 65525) {
			drive_p -> FATtype = FAT16;
			printf("Found FAT16\n");
			error_flag = UNSUPPORTED_FAT16;
		} else {
			drive_p -> FATtype = FAT32;
			printf("Found FAT32\n");
		}

		if (error_flag==FS_NO_ERROR) {
			drive_p -> StartofFAT = (uint32_t)rsvdSecCnt + hiddenSec;
			drive_p -> FirstDataSec = rsvdSecCnt + drive_p -> RootDirSecs + hiddenSec + FATSz*numFATs;
			drive_p -> FirstRootDirSec = First_Sector(rootClus);
		}
	}

	return error_flag;
}

uint32_t First_Sector(uint32_t Cluster_Num) {
	uint32_t sector_number;
	FS_values_t * drive_p;

	drive_p = Export_Drive_values();

	if (Cluster_Num == 0) {
		sector_number = drive_p -> FirstRootDirSec;
	} else {
		sector_number = ((Cluster_Num - 2) * drive_p -> SecPerClus) + drive_p -> FirstDataSec;
	}

	return sector_number;
}

uint32_t Find_Next_Clus(uint32_t Cluster_Num, uint8_t * array_name) {
	uint8_t error_flag;
	uint16_t FATOffset;
	uint32_t sector_number, return_clus;
	FS_values_t * drive_p;

	drive_p = Export_Drive_values();

	sector_number = drive_p -> StartofFAT + (Cluster_Num >> (drive_p -> BytesPerSecShift - drive_p -> FATshift));
	error_flag = Read_Sector(sector_number, drive_p -> BytesPerSec, array_name);
	FATOffset = (uint16_t)((Cluster_Num << drive_p -> FATtype) % (drive_p -> BytesPerSec -1));

	if (drive_p -> FATtype == FAT32) {
		return_clus = (read32(FATOffset, array_name) && 0x0FFFFFFF);
	} else if (drive_p -> FATtype == FAT16) {
		return_clus = (uint32_t)(read16(FATOffset, array_name));
	}

	return return_clus;
}