//-----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------//
// Source Code for I2C
// Project: MP3 Player
// Author : Sengupta,Ayush; Vaidhun, Sudharsan; Singh, Siddharth;
//------------------------------------------------------------------------------------------------------------------//


#include "i2c.h"
#include "port.h"
#include "AT89C51RC2.h"
#include <stdio.h>

uint8_t I2C_Reload_L;
uint8_t I2C_Reload_H;

uint8_t I2C_Write (uint8_t device_addr, uint8_t num_bytes, uint8_t *bytes_to_send) {
	uint8_t send_value, index, bit_index, error_flag = I2C_NO_ERROR;
	bit send_bit;	

	//Check for Bus Idle
	SDA = 1;
	SCL = 1;
	if ((SDA != 1)||(SCL != 1)) {
		error_flag = BUS_BUSY;
	}

	if (error_flag == I2C_NO_ERROR) {
		SDA = 0;
		I2C_Clock_Start();
		send_value = device_addr << 1;

		index = 0;
		do {
			bit_index = 0;
			do {
				I2C_Clock_Delay(PROCEED);
				SCL = 0;
				send_bit = ((send_value >>(7-bit_index)) & 0x01);
				SDA = send_bit;
				I2C_Clock_Delay(PROCEED);
				SCL = 1;
				while (SCL==0);	//Waiting for CLK to change
				if (SDA!=send_bit) {
					error_flag = BUS_BUSY;
				}
				bit_index++;
			} while ((bit_index<8)&&(error_flag==I2C_NO_ERROR));

			I2C_Clock_Delay(PROCEED);
			SCL = 0;
			SDA = 1;
			I2C_Clock_Delay(PROCEED);
			SCL = 1;
			while (SCL==0);
			if(SDA==0) {
				error_flag = I2C_NO_ERROR;
			} 
			else if(SDA==1) {
				error_flag = NACK;
			}
			send_value = *(bytes_to_send + index);
			index++;
		} while ((index <= num_bytes) && (error_flag == I2C_NO_ERROR));

		if (error_flag == I2C_NO_ERROR){
			I2C_Clock_Delay(PROCEED);
			SCL = 0;
			SDA = 0;
			I2C_Clock_Delay(PROCEED);
			SCL = 1;
			while (SCL==0);
			I2C_Clock_Delay(STOP);
			SDA = 1;
		}
	} else {
		error_flag = BUS_BUSY;
	}

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
		send_value |= 0x01;					// R/W = Read
		SDA = 0;

		num_bits = 8;
		do {
			I2C_Clock_Delay(PROCEED);
			SCL = 0;
			num_bits--;
			send_bit = ((send_value >> num_bits) & 0x01);
			SDA = send_bit;
			I2C_Clock_Delay(PROCEED);
			SCL = 1;
			while (SCL==0);
			sent_bit = SDA;
			if(send_bit!=sent_bit) {
				error_flag = BUS_BUSY;
			}
		} while ((num_bits>0)&&(error_flag==I2C_NO_ERROR));

		I2C_Clock_Delay(PROCEED);
		SCL = 0;
		SDA = 1;
		I2C_Clock_Delay(PROCEED);
		SCL = 1;
		while (SCL==0);
		rec_bit = SDA;
		if(rec_bit != ACK) {
			error_flag = NACK;
		}

		while ((index<num_bytes)&&(error_flag == I2C_NO_ERROR)) {
			for (i=0; i<8; i++) {
				I2C_Clock_Delay(PROCEED);
				SCL = 0;
				SDA = 1;
				I2C_Clock_Delay(PROCEED);
				SCL = 1;
				while (SCL==0);
				rec_bit = SDA;
				rec_value = rec_value << 1;
				rec_value |= rec_bit;
			}
			*(bytes_to_receive+index) = rec_value;
			index++;

			if (index == num_bytes) {
				send_bit = NACK;
			} else {
				send_bit = ACK;
			}
			I2C_Clock_Delay(PROCEED);
			SCL = 0;
			SDA = send_bit;
			I2C_Clock_Delay(PROCEED);
			SCL = 1;
			while (SCL==0);
		}

		I2C_Clock_Delay(PROCEED);
		SCL = 0;
		SDA = 0;
		I2C_Clock_Delay(PROCEED);
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
	TMOD &= 0x0F;	//Clearing bit 4-7
	TMOD |= 0x10; 	//Setting bit 4 => Timer1 in Mode 1
	TR1 = 0;		//Timer 1 run control: STOP
	ET1 = 0;		//Timer1 Interrupt Disable
	TH1 = I2C_Reload_H;
	TL1 = I2C_Reload_L;
	TF1 = 0;		//Clear Overflow bit
	TR1 = 1;		//Timer1 Start
}

void I2C_Clock_Delay (uint8_t control) {
	if (TR1 == 1) {
		while (TF1 == 0);
	}
	TR1 = 0;

	if (control == PROCEED) {
		TH1 = I2C_Reload_H;
		TL1 = I2C_Reload_L;
		TF1 = 0;
		TR1 = 1;
	}

	if (control == STOP){
		TR1 = 0;
	}
}

void I2C_Init(uint32_t i2c_speed) {
	uint32_t reload_value = (65535 + 1) - (OSC_FREQ/(i2c_speed*2UL*OSC_PER_INST));
	// Set i2c_speed as 24000 for decent round values for reloading

	// reload_value = (65535 + 1) - ((OSC_FREQ/i2c_speed)/(2*OSC_PER_INST));

	I2C_Reload_L = (uint8_t) reload_value % 256;
	I2C_Reload_H = (uint8_t) reload_value / 256;
	// I2C_Reload_H = 0xFF;
	printf("I2C Initialized.\n");
}