/*
 * AvrTestIceIceBaby.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "UART_driver.h"
#include "sram_test.h"
//#include "test.h"
#include "xmem.h"
//#include "OLED_driver.h"
#include "ADC_driver.h"

//void xmem_write(uint8_t data, uint16_t address, uint16_t BASE_ADDRESS) {
	//volatile char *ext_mem = (char *) BASE_ADDRESS;
	//ext_mem[address] = data;
//}
//
//uint8_t xmem_read(uint16_t address, uint16_t BASE_ADDRESS) {
	//volatile char *ext_mem = (char *) BASE_ADDRESS;
	//uint8_t ret_val = ext_mem[address];
	//return ret_val;
//}

int main(void)
{
	uart_init( MYUBRR );
	
	
	xmem_init();
	
	// SRAM_test();
	//xmem_write(0xFF, 0x0001, 0x1000);
	//
	adc_init();
	
	while(1){
		char x = adc_read(1); // A1
		char y = adc_read(0); // A0
		char b = adc_read(2); // A2
		
		printf("X value: %d, Y value: %d, Button value: %d \n", x, y, b);
	}

}