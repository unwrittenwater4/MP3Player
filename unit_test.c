#include "unit_test.h"

void LED_Test(void) {
	uint8_t i;
	for (i=0; i<5; i++) {
		LED_FLASH_Change_State();
		delay1s(1);
	}
}

void LCD_Test(void) {
	uint8_t text[] = "LCD Ready!";
	LCD_Write_String(text);
}

void UART_Test(void) {
	uint8_t i=0;
	uint8_t text[] = "UART Ready!";

	while(text[i]!=0x00)
		putchar(text[i++]);
	
	printf("\n\r");
}

// void Memory_Test(void) {
// 	uint8_t *txt_ptr;
// 	txt_ptr = code_memory_init();
// 	print_memory(50, txt_ptr);

// 	printf("\n\r");
// }

// void Xdata_Memory_Test(void) {
// 	uint8_t *txt_ptr;
// 	txt_ptr = xdata_memory_init();
// 	print_memory(50, txt_ptr);

// 	printf("\n\r");
// }