/*
 * test.c
 *
 * Created: 06.09.2021 12:50:21
 *  Author: elisegm
 */ 

#define F_CPU 4915200

#include "test.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "CAN_driver.h"
#include "Movement_driver.h"

void test_address_decoder(void) {
	PORTC &= (0xF0);
	_delay_ms(250);
	
	PORTC |= (1 << 2); // 01
	_delay_ms(250);
	
	PORTC |= (1 << 3); // 11
	_delay_ms(250);
	
	PORTC &= (1 << 3); // 10
	_delay_ms(250);
}


void test_CAN_loopback(void){
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

//
//void test_movement(void){
	//input_j joystick_input;
	//input_s slider_input;
	//while (1)
	//{
		//joystick_input = mov_get_joy_input();
		//slider_input = mov_get_slider_input();
		//printf("X value: %d, Y value: %d \r\n", joystick_input.pos_x, joystick_input.pos_y);
		////printf("Button pressed: %d \r\n", joystick_input.button_pressed);
		////printf("Left slider value: %d, Right slider value: %d \r\n", slider_input.pos_l_slider, slider_input.pos_r_slider);
	//}
//}
//
////mcp2515_write(0x1F, 0x02);

//SPI_select();
//SPI_send(0xff);
//SPI_deselect();
//
//menu_main();
//pos_joy_read();
//pos_j joystick_pos;
//dir joystick_dir = mov_get_joy_dir();
//int i = mov_read_r_slider_button();
//
//int j = mov_read_joy_button();
//int k = mov_read_l_slider_button();
////char x = adc_rd(JOYSTICK_CHANNEL_X);
//char y = adc_rd(JOYSTICK_CHANNEL_Y);

//
//pos_s slider_pos;
//slider_pos = mov_get_slider_pos();
//char data = 'H';
//char *pointer = &data;
//OLED_print('H');
////
//dir current_dir;
//current_dir = mov_get_joy_dir();

//printf("X value: %d, Y value: %d \r\n", joystick_pos.pos_x, joystick_pos.pos_y);

//printf("X value: %d p, Y value: %d p \r\n", x, y);
//printf("Right slider value: %d, Left slider value: %d \r\n", right, left);
//printf("Right slider value: %d, Left slider value: %d \r\n", slider_pos.pos_r_slider, slider_pos.pos_l_slider);
