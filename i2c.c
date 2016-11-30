//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Source Code for I2C
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//

#include "i2c.h"
#include "port.h"
#include "AT89C51RC2.h"

uint8_t I2C_Write (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_send) {
	uint8_t send_value, index, bit_index, error_flag = I2C_NO_ERROR;
	bit send_bit;

	SDA = 1;
	SCL = 1;
	if ((SDA != 1)||(SCL != 1)) {
		error_flag = BUS_BUSY;
	}

	if (error_flag == I2C_NO_ERROR) {
		SDA = 0;
	}
	I2C_Clock_Start();
	send_value = device_addr << 1;

	index = 0;
	while (index < num_bytes) {
		send_value = *(bytes_to_send + index);
		bit_index = 0;
		do {
			I2C_Clock_Delay(CONTINUE);
			SCL = 0;
			send_bit = (send_value >>(7-bit_index));
			SDA = send_bit;
			I2C_Clock_Delay(CONTINUE);
			SCL = 1;
			while (SCL==0);
			if (SDA!=send_bit) {
				error_flag = BUS_BUSY;
			}
			bit_index++;
		} while ((bit_index<8)&&(error_flag==I2C_NO_ERROR));
		I2C_Clock_Delay(CONTINUE);
		SCL = 0;
		SDA = 1;
		I2C_Clock_Delay(CONTINUE);
		SCL = 1;
		while (SCL==0);
		if(SDA==0) {
			error_flag = I2C_NO_ERROR;
		} else if(SDA==1) {
			error_flag = NACK;
		}
		index++;
	}

	I2C_Clock_Delay(CONTINUE);
	SCL = 0;
	SDA = 0;
	I2C_Clock_Delay(CONTINUE);
	SCL = 1;
	while (SCL==0);
	I2C_Clock_Delay(STOP);
	SDA = 1;

	return error_flag;
}

uint8_t I2C_Read (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_receive) {
	uint8_t send_value, rec_value, i, index = 0, error_flag = I2C_NO_ERROR, num_bits;
	bit send_bit, sent_bit, rec_bit;

	SDA = 1;
	SCL = 1;
	if ((SDA==1)&&(SCL==1)) {
		I2C_Clock_Start();
		send_value = (device_addr << 1);
		send_value |= 0x01;					// R/W = Write
		while ((index<num_bytes)&&(error_flag==I2C_NO_ERROR)) {
			num_bits = 8;
			do {
				I2C_Clock_Delay(CONTINUE);
				SCL = 0;
				num_bits--;
				send_bit = (send_value >> num_bits);
				SDA = send_bit;
				I2C_Clock_Delay(CONTINUE);
				SCL = 1;
				while (SCL==0);
				sent_bit = SDA;
				if(send_bit!=sent_bit) {
					error_flag = BUS_BUSY;
				}
			} while ((num_bits>0)&&(error_flag==I2C_NO_ERROR));

			I2C_Clock_Delay(CONTINUE);
			SCL = 0;
			SDA = 1;
			I2C_Clock_Delay(CONTINUE);
			SCL = 1;
			while (SCL==0);
			send_bit = SDA;
			if(send_bit != ACK) {
				error_flag = NACK;
			}

			for (i=0; i<8; i++) {
				I2C_Clock_Delay(CONTINUE);
				SCL = 0;
				SDA = 1;
				I2C_Clock_Delay(CONTINUE);
				SCL = 1;
				while (SCL==0);
				rec_bit = SDA;
				rec_value = rec_value << 1;
				rec_value |= rec_bit;
			}
			*(bytes_to_receive+index) = rec_value;
			index++;
			if (index+1 == num_bytes) {
				send_bit = NACK;
			} else {
				send_bit = ACK;
			}
			I2C_Clock_Delay(CONTINUE);
			SCL = 0;
			SDA = send_bit;
			I2C_Clock_Delay(CONTINUE);
			SCL = 1;
			while (SCL==0);
		}

		I2C_Clock_Delay(CONTINUE);
		SCL = 0;
		SDA = 0;
		I2C_Clock_Delay(CONTINUE);
		SCL = 1;
		while (SCL==0);
		I2C_Clock_Delay(STOP);
		SDA = 1;
	} else {
		error_flag = BUS_BUSY;
	}

	return error_flag;
}

void I2C_Clock_Start (void) {
	TMOD &= 0x0F;
	TMOD1 |= 0x10; // Unable to find the define in headers!
	TR1 = 0;
	ET1 = 0;
	TH1 = I2C_Reload_H;
	TL1 = I2C_Reload_L;
	TF1 = 0;
	TR1 = 1;
}

void I2C_Clock_Delay (uint8_t control) {
	if (TR1 == 1) {
		while (TF1 == 0);
	}

	TR1 = 0;
	if (control == CONTINUE) {
		TH1 = I2C_Reload_H;
		TL1 = I2C_Reload_L;
		TF1 = 0;
		TR1 = 1;
	}
}