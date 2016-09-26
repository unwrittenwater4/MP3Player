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
}

void LCD_Write(bit registerSelect, uint8_t writeValue) {
	lcdRS = registerSelect;
	lcdEnable = 1;
	lcdPort = writeValue;
	delay50ms(1);
	lcdEnable = 0;
	lcdPort = 0xFF;
}
