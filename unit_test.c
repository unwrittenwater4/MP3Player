#include "unit_test.h"

// Stores the LED state
bit LED_state_R;
bit LED_state_A;
bit LED_state_G;
bit LED_state_Y;

void LED_FLASH_Init(void)
{
   LED_state_R = 0;
}

void LED_FLASH_Change_State(void)
   {
   // Change the LED from OFF to ON (or vice versa)
   if (LED_state_R == 1)
      {
      LED_state_R = 0;
      LED_pin_R = 0;
      }
   else
      {
      LED_state_R = 1;
      LED_pin_R = 1;
      }
   }

