/*
 * AvrTestIceIceBaby.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#define F_CPU 4915200
#include <avr/interrupt.h>

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
	CAN_init(MODE_LOOPBACK);
	
	printf("######## Starting new session ########\r\n");
	
	can_message test_message;
	test_message.id = 0x76;
	test_message.length = 1;
	test_message.data[0] = 'U';
	
	can_message test_message_2;
	test_message_2.id = 0x7B;
	test_message_2.length = 1;
	test_message_2.data[0] = 'M';
	
	can_message test_1_received;
	can_message test_2_received;
	
	
	while (1)
	{
		CAN_send_message(&test_message);
		CAN_receive_message(&test_1_received);
		CAN_send_message(&test_message_2);
		CAN_receive_message(&test_2_received);
	}

}