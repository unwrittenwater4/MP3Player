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
#include "hardware_delay_1ms.h"

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
	lcdPort = writeValue;
	lcdEnable = 1;
	lcdEnable = 0;
	DELAY_1ms_T1(1);
}

void LCD_Write_String(uint8_t *string) {
	uint8_t i = 0;
	while(*(string+i) != 0x00) {
		LCD_Write(DATA,*(string+(i++)));
	}
}