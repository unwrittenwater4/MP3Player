//---------------------------------//
// Header file to initailize lcd.c
//---------------------------------//
//---------------------------------//
//Project: MP3 Player
//Author:   Singh, Siddharth;
//          Vaidhun, Sudharsan;
//          Sengupta, Ayush
//---------------------------------//

#ifndef _LCD_H
#define _LCD_H

#include "main.h"

#define COMMAND 0
#define DATA 1

#define SET_ADDRESS 0x80
#define LINE1       0x00
#define LINE2       0x40
#define ONELINE     0x00
#define TWOLINE     0x08
#define DISPLAYOFF  0x00
#define DISPLAYON   0x04
#define DISPLAYCLEAR 0x01
#define CURSOROFF   0x00
#define CURSORON    0x02
#define BLINKOFF    0x00
#define BLINKON     0x01
#define DECREMENT   0x00
#define INCREMENT   0x02
#define SHIFTOFF    0x00
#define SHIFTON     0x01

// Functions to be used in lcd
void LCD_Init(void);
void LCD_Write(bit registerSelect, uint8_t writeValue);

#endif