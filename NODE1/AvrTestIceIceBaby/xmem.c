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
