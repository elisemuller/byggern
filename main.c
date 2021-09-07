/*
 * AvrTestIceIceBaby.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#define OLED_BASE 0x1000;
#define ADC_BASE 0x1400;
#define SRAM_BASE 0x1800;

#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"

void xmem_write(uint8_t data, uint16_t address, uint16_t BASE_ADDRESS) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	ext_mem[address] = data;
}

uint8_t xmem_read(uint16_t address, uint16_t BASE_ADDRESS) {
	volatile char *ext_mem = (char *) BASE_ADDRESS;
	uint8_t ret_val = ext_mem[address];
	return ret_val;
}

int main(void)
{
	uart_init( MYUBRR );
	
	xmem_init();
	
	//xmem_write(0xFF, 0x00FF, 0x1000);
	
	while(1){
		
		 uint8_t joystick_1 = (uint8_t) xmem_read(0x0000, ADC_BASE);
		 uint8_t joystick_23 = (uint8_t) xmem_read(0x0022, ADC_BASE);
		 uint8_t joystick_24 = (uint8_t) xmem_read(0x0023, ADC_BASE);
		 
		 printf("Joystick output, ADC pin 1:")
		 printf(joystick_1)
	}

}