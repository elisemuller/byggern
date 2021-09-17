#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"


void xmem_init(void) {
	MCUCR |= (1 << SRE); //Enables xmem
	SFIOR &= ~(7 << XMM0); // 111 TO XMM0-2
	SFIOR |= (1 << XMM2);  // Masks PC4-PC7 Atmega pins
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

void xmem_write(uint8_t data, uint16_t address, uint16_t base) {	
	volatile char *ext_mem = (char *) base;
	ext_mem[address] = data;
}

uint8_t xmem_read(uint16_t address, uint16_t base) {	
	volatile char *ext_mem = (char *) base;
	uint8_t ret_val = ext_mem[address];	
	return ret_val;
}
