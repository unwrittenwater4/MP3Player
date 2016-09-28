#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

#include "main.h"
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "blink.h"
#include "lcd.h"
#include "print_bytes.h"
#include "memory_test.h"

void LED_Test(void);
void LCD_Test(void);
void UART_Test(void);
void Memory_Test(void);
void Xdata_Memory_Test(void);

#endif