/*------------------------------------------------------------------*-

   Hello.C (v1.00)

  ------------------------------------------------------------------

   A "Hello Embedded World" test program for 8051.


   COPYRIGHT
   ---------

   This code is associated with the book:

   EMBEDDED C by Michael J. Pont 
   [Pearson Education, 2002: ISBN: 0-201-79523-X].

   This code is copyright (c) 2001 by Michael J. Pont.
 
   See book for copyright details and other information.

-*------------------------------------------------------------------*/

#include <reg52.h>

// LED is to be connected to this pin
sbit LED_pin = P2^7;

// Stores the LED state
bit LED_state_G;

// Function prototypes
void LED_FLASH_Init(void);
void LED_FLASH_Change_State(void);
void DELAY_LOOP_Wait(const unsigned int);

/*..................................................................*/

void main(void)
   {
   LED_FLASH_Init();

   while(1) 
      {
      // Change the LED state (OFF to ON, or vice versa)
      LED_FLASH_Change_State();

      // Delay for *approx* 1000 ms
      DELAY_LOOP_Wait(1000);
      }   
   }

/*------------------------------------------------------------------*-

  LED_FLASH_Init()

  Prepare for LED_Change_State() function - see below.

-*------------------------------------------------------------------*/
void LED_FLASH_Init(void)
   {
   LED_state_G = 0;
   }


/*------------------------------------------------------------------*-

  LED_FLASH_Change_State()

  Changes the state of an LED (or pulses a buzzer, etc) on a 
  specified port pin.

  Must call at twice the required flash rate: thus, for 1 Hz
  flash (on for 0.5 seconds, off for 0.5 seconds),
  this function must be called twice a second.

-*------------------------------------------------------------------*/
void LED_FLASH_Change_State(void)
   {
   // Change the LED from OFF to ON (or vice versa)
   if (LED_state_G == 1)
      {
      LED_state_G = 0;
      LED_pin = 0;
      }
   else
      {
      LED_state_G = 1;
      LED_pin = 1;
      }
   }

/*------------------------------------------------------------------*-

  DELAY_LOOP_Wait()

  Delay duration varies with parameter.  

  Parameter is, *ROUGHLY*, the delay, in milliseconds,
  on 12MHz 8051 (12 osc cycles).

  You need to adjust the timing for your application!

-*------------------------------------------------------------------*/
void DELAY_LOOP_Wait(const unsigned int DELAY)
   {
   unsigned int x, y;

   for (x = 0; x <= DELAY; x++)
      {
      for (y = 0; y <= 120; y++);
      }
   }

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
