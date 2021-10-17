/*
 * NODE1.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#define F_CPU 4915200
#include <avr/interrupt.h>

#include <avr/io.h>
#include <stdio.h>
#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"
#include "ADC_driver.h"
#include "Movement_driver.h"
#include "OLED_driver.h"
#include "menu.h"
//#include "mcp2515.h"
//#include "SPI_driver.h"
//#include "CAN_driver.h"


int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	adc_init();
	mov_init();
	//CAN_init(MODE_LOOPBACK);
	OLED_init();

	menu_init();
	menu_print();
	
	printf("######## Starting new session ########\r\n");
	//SRAM_test();
	//test_movement();
	
	//can_message test_joystick_message;
	//test_joystick_message.id = CAN_JOYSTICK_ID;
	//test_joystick_message.length = 4;
	//input_j joystick_input;
	
	while (1)
	{
		//OLED_print("Hello");
		menu_main();
		//OLED_print("Hello");

		//menu_main();
		//joystick_input = mov_get_joy_input();
		

		//test_joystick_message.data[0] = joystick_input.pos_x;
		//test_joystick_message.data[1] = joystick_input.pos_y;
		//test_joystick_message.data[2] = joystick_input.button_pressed;
		//test_joystick_message.data[3] = joystick_input.direction;
		//
		//CAN_send_message(&test_joystick_message);
		////CAN_receive_message(&test_1_received);
	}

}
