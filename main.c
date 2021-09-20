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


int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	SRAM_test();
	adc_init();
	//mov_null_pos_calibrate();
	//OLED_init();

	
	while(1){
		//pos_joy_read();
		//pos_t joystick_pos;
		//joystick_pos = get_joy_pos();
		char x = adc_rd(JOYSTICK_CHANNEL_X);
		char y = adc_rd(JOYSTICK_CHANNEL_Y);
		
		
		//pos_s slider_pos; 
		//slider_pos = mov_get_slider_pos();
		
		
		//dir current_dir;
		//current_dir = mov_get_joy_dir();
		//OLED_write_d(0b00011000);
		//OLED_write_d(0b00011000);
		//OLED_write_d(0b01111110);
		//OLED_write_d(0b00111100);
		//OLED_write_d(0b00011000);
		

		printf("X value: %d p, Y value: %d p \r\n", x, y);
		//printf("Right slider value: %d, Left slider value: %d \r\n", right, left);
		//printf("Right slider value: %d, Left slider value: %d \r\n", slider_pos.pos_r_slider, slider_pos.pos_l_slider);

	}

}