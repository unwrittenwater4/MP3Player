//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Header File for I2C
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//

#ifndef _I2C_H
#define _I2C_H

#define I2C_NO_ERROR          0
#define BUS_BUSY             -1
#define TIMEOUT_ERROR		 -2
#define ACK                   0
#define NACK                  1

#define STOP                  0
#define PROCEED              1     //C keyword in lowercase; I think this should be avoided?

#include "main.h"
#include "port.h"

uint8_t I2C_Write (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_send);
uint8_t I2C_Read (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_receive);

void I2C_Clock_Start (void);
void I2C_Clock_Delay (uint8_t control);

void I2C_Init(uint32_t i2c_speed);

#endif