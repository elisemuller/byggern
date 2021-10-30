/*
 * test.c
 *
 * Created: 06.09.2021 12:50:21
 *  Author: elisegm
 */ 

#define F_CPU 4915200

#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "test.h"
#include "CAN_driver.h"
#include "movement_driver.h"


// Egen test funksjon som tester alle driverne og returnerer antall feil 


void test_ADC(void) {
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


void test_SRAM(void){
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();
    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed);
    // reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++) {
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value) {
            printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}


void test_movement(void){
	input_j joystick_input;
	input_s slider_input;
	while (1)
	{	
		joystick_input = mov_get_joy_input();
		slider_input = mov_get_slider_input();
		printf("X value: %d, Y value: %d \r\n", joystick_input.pos_x, joystick_input.pos_y);
		//printf("Button pressed: %d \r\n", joystick_input.button_pressed);
		//printf("Left slider value: %d, Right slider value: %d \r\n", slider_input.pos_l_slider, slider_input.pos_r_slider);
	}
}

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
