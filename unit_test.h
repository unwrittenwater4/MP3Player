#ifndef _UNIT_TEST_H
define _UNIT_TEST_H

#include "main.h"
#include <reg52.h>

// LED is to be connected to this pin
sbit LED_pin_R = P2^4;
sbit LED_pin_A = P2^5;
sbit LED_pin_G = P2^6;
sbit LED_pin_Y = P2^7;

// Stores the LED state
bit LED_state_R;
bit LED_state_A;
bit	LED_state_G;
bit LED_state_Y;

// Function prototypes
void LED_FLASH_Init(void);
void LED_FLASH_Change_State(void);


#endif