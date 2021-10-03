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


int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	adc_init();
	mov_init();
	OLED_init();
	menu_init();
	//printHello();
	//printGoodBye();
	menu_print();

	
	//OLED_select_font(SMALL);
	//OLED_print("Hello world");

	//OLED_print_image(LMFAO);

	
	while(1){
		menu_main();
		//pos_joy_read();
		//pos_j joystick_pos;
		////dir joystick_dir = mov_get_joy_dir();
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
		//OLED_write_d(0xff);
		//OLED_write_d(0b00011000);
		//OLED_write_d(0b01111110);
		//OLED_write_d(0b00111100);
		//OLED_write_d(0b00011000);
		
		//printf("X value: %d, Y value: %d \r\n", joystick_pos.pos_x, joystick_pos.pos_y);

		//printf("X value: %d p, Y value: %d p \r\n", x, y);
		//printf("Right slider value: %d, Left slider value: %d \r\n", right, left);
		//printf("Right slider value: %d, Left slider value: %d \r\n", slider_pos.pos_r_slider, slider_pos.pos_l_slider);

	}

}