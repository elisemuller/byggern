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
#include "OLED_driver.h"
#include "ADC_driver.h"
#include "Movement_driver.h"
#include "menu.h"
#include "mcp2515.h"
#include "SPI_driver.h"
#include "CAN_driver.h"


int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	adc_init();
	//mov_init();
	//OLED_init();
	//menu_init();

	//SPI_init();
	//SPI_send("H");
	//CAN_init();
	//menu_print();
	mcp2515_init();
	//can_message* test_message;
	//test_message->id = 0x01AF;
	//test_message->length = 1;
	//test_message->data[0] = 0xAB;
	//
	//can_message test_received;
	
	
	while(1){
		mcp2515_init();

		_delay_ms(3000);
		//SPI_deselect();
		//_delay_ms(1000);
		//mcp2515_write(0x2,0x2);
		//menu_main();
		//CAN_send_message(*test_message);
		//CAN_receive_message(&test_received);
	}

}