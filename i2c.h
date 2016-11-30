//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Header File for I2C
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//

#ifndef _I2C_H
#define _I2C_H

#define I2C_NO_ERROR (0)
#define BUS_BUSY (-1)
#define ACK (0)
#define NACK (1)

#define STOP (0)
#define CONTINUE (1)

uint8_t I2C_Write (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_send);
uint8_t I2C_Read (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_receive);

void I2C_Clock_Start (void);
void I2C_Clock_Delay (uint8_t control);

#endif