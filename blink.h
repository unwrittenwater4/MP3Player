#ifndef _BLINK_H
#define _BLINK_H

#include "main.h"

// Public Variable definitions
sbit LED_pin_R = P2^4;
sbit LED_pin_A = P2^5;
sbit LED_pin_G = P2^6;
sbit LED_pin_Y = P2^7;

// Public Function prototypes
void LED_FLASH_Init(void);
void LED_FLASH_Change_State(void);

#endif