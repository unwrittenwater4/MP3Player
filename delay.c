#include "main.h"
#include "delay.h"

void delay50ms(uint16_t time) {
	uint16_t i,j;

	for(i=0; i<time; ++i) {
		for(j = 0; j<(OSC_FREQ * 3/(OSC_PER_INST * 2 * 1000)); ++j){
		}
	}
}

void delay1s(uint8_t time) {
	uint16_t i;
	for(i=0; i<time; i++)
		delay50ms(20);
}