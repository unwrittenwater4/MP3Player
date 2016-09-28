//---------------------------------//
// Source file for LCD functioning
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author: Singh, Siddharth; Vaidhun, Sudharshan;
//		  Sengupta, Ayush
//---------------------------------//


#include "main.h"
#include "port.H"
#include "delay.h"
#include "LCD.h"

void LCD_Init(void) {
	delay50ms(1);
	LCD_Write(COMMAND, (0x30|TWOLINE|DISPLAYON));
	delay50ms(1);
	LCD_Write(COMMAND, (0x30|TWOLINE|DISPLAYON));
	delay50ms(1);
	LCD_Write(COMMAND, (0x30|TWOLINE|DISPLAYON));
	delay50ms(1);
	LCD_Write(COMMAND, (0x30|TWOLINE|DISPLAYON));
	delay50ms(1);
	LCD_Write(COMMAND, (0x08|DISPLAYON|CURSOROFF|BLINKOFF));
	delay50ms(1);
	LCD_Write(COMMAND, (DISPLAYCLEAR));
	delay50ms(1);
	LCD_Write(COMMAND, (0x04|INCREMENT|SHIFTOFF));
	delay50ms(1);
	LCD_Write(COMMAND, (SET_ADDRESS|LINE1));
}

void LCD_Write(bit registerSelect, uint8_t writeValue) {
	lcdRS = registerSelect;
	delay50ms(1);
	lcdPort = writeValue;
	delay50ms(1);
	lcdEnable = 1;
	// delay50ms(1);
	lcdEnable = 0;
	delay50ms(1);
	// lcdPort = 0xFF;
}

void LCD_Write_String(uint8_t *string) {
	uint8_t i = 0;
	while(*(string+i) != 0x00) {
		LCD_Write(DATA,*(string+(i++)));
	}
}