#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"


void xmem_init(void) {
	MCUCR |= (1 << SRE);
	SFIOR &= ~(7 << XMM0); // 111 TO XMM0-2
	SFIOR |= (1 << XMM2);
}

void mcu_porta_io_config(uint8_t mcu_in) {
	if (mcu_in) {
		DDRA = 0x00;
	}
	else {
		DDRA = 0xFF;
	}
}


// xmem read og write er hentet fra labforelesning

void xmem_write(uint8_t data, uint16_t address, uint16_t BASE_ADDRESS) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	ext_mem[address] = data;
}

uint8_t xmem_read(uint16_t address, uint16_t BASE_ADDRESS) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	uint8_t ret_val = ext_mem[address];
	return ret_val;
}