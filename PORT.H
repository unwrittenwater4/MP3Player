/*------------------------------------------------------------------*-

   Port.H (v1.00)

  ------------------------------------------------------------------

   Port Header - Exp#1 UART & LCD Module
   
   Programmer(s): Roger Younger 
   
   Date: 9/8/16

   Description: Defines the port pins for the basic 8051 circuit
-*------------------------------------------------------------------*/

#ifndef _PORT_H
#define _PORT_H

// LCD Port
sfr lcdPort   = 0x80;	// Port 0

// Port 0
sbit P0_0 = P0^0;	// LCD
sbit P0_1 = P0^1;	// LCD
sbit P0_2 = P0^2;	// LCD
sbit P0_3 = P0^3;	// LCD
sbit P0_4 = P0^4;	// LCD
sbit P0_5 = P0^5;	// LCD
sbit P0_6 = P0^6;	// LCD
sbit P0_7 = P0^7;	// LCD

// Port 1
sbit SD_Select = P1^0;	// SD Card
sbit SDA = P1^1;		//	I2C
sbit SCL = P1^2;		//	I2C
sbit P1_3 = P1^3;
sbit STA_Select = P1^4;		// STA013 MP3 Decoder
sbit SPI_MISO = P1^5;		//	SPI
sbit SPI_SCK = P1^6;		//	SPI
sbit SPI_MOSI = P1^7;		//	SPI

// Port 2
sbit SW1 = P2^0;
sbit SW2 = P2^1;
sbit SW3 = P2^2;
sbit SW4 = P2^3;
sbit REDLED = P2^4;
sbit GREENLED = P2^5;
sbit YELLOWLED = P2^6;
sbit AMBERLED = P2^7;

// Port 3
sbit per_TxD = P3^0;
sbit per_RxD = P3^1;
sbit P3_2 = P3^2;		
sbit STA_DATA_REQ = P3^3;	// STA013 MP3 Decoder
sbit STA_RESET = P3^4;		// STA013 MP3 Decoder
sbit P3_5 = P3^5;
sbit lcdRS = P3^6;
sbit lcdEnable = P3^7;

#endif

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/



