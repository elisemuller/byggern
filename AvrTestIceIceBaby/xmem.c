#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"

#define BASE_ADDRESS 0x1000


void xmem_init(void) {
	// Enables external memory
	MCUCR |= (1 << SRE); 
	
	// Masks PC4-PC7 pins
	SFIOR &= ~(7 << XMM0);
	SFIOR |= (1 << XMM2); 
}

void mcu_porta_io_config(uint8_t mcu_in) {
	if (mcu_in) {
		DDRA = 0x00; //input
	}
	else {
		DDRA = 0xFF; //output
	}
}


// xmem read og write er hentet fra labforelesning

void xmem_write(uint8_t data, uint16_t offset) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	ext_mem[offset] = data;
}

uint8_t xmem_read(uint16_t offset) {	
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	uint8_t ret_val = ext_mem[offset];	
	return ret_val;
}
