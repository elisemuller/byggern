///*
 //* Movement_driver.c
 //*
 //* Created: 20.09.2021 16:55:21
 //*  Author: elisegm
 //*/ 
//
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

#include "movement_driver.h"
#include "ADC_driver.h"
#include "CAN_driver.h"



/**
 * @def DEBUG_BUTTON
 * @brief A macro that is used to debug if the buttons are working when set to 1
 */
#define DEBUG_BUTTON 0

volatile int null_x; /*!< The calibrated neutral x position of the joystick */

volatile int null_y; /*!< The calibrated neutral y position of the joystick */

volatile int x_pos; /*!< The joystick position on the x axis */

volatile int y_pos; /*!< The joystick position on the y axis */

volatile int r_pos; /*!< The position of the right slider */

volatile int l_pos; /*!< The position of the left slider */




void mov_init(void){
	adc_init();
	null_x = adc_rd(JOYSTICK_CHANNEL_X);
	null_y = adc_rd(JOYSTICK_CHANNEL_Y);
	DDRB &= ~(0b111);
}


void mov_pos_joy_rd(void){
	char x = adc_rd(JOYSTICK_CHANNEL_X);
	char y = adc_rd(JOYSTICK_CHANNEL_Y);
	int32_t data_x = (int32_t)x;
	int32_t data_y = (int32_t)y;

	if (data_x >= null_x ){
		x_pos = (data_x - null_x)*100/(255 - null_x);
	}
	else {
		x_pos = (data_x - null_x)*100/(null_x);
	}
	if (data_y >= null_y ){
		y_pos = (data_y - null_y)*100/(255 - null_y);
	}
	else {
		y_pos = (data_y - null_y)*100/(null_y);
	}
}

void mov_pos_slider_rd(void){
	char right = adc_rd(SLIDER_CHANNEL_R);
	char left = adc_rd(SLIDER_CHANNEL_L);
	int32_t data_right = (int32_t)right;
	int32_t data_left = (int32_t)left;
	r_pos = (data_right*100)/255;
	l_pos = (data_left*100)/255;
}

dir mov_get_joy_dir(void){
	mov_pos_joy_rd();
	const int neutral_threshold = 70;
	dir direction = UNDEFINED;
	
	int abs_x = abs(x_pos);
	int abs_y = abs(y_pos);
	
	if (abs_x < neutral_threshold && abs_y < neutral_threshold){
		direction = NEUTRAL;
	}
	else if((abs_x > abs_y) && (abs_x > neutral_threshold)){
		if (x_pos > 0){
			direction = RIGHT;
		}
		else {
			direction = LEFT;
		}
	}
	else if ((abs_y > abs_x) && (abs_y > neutral_threshold)){
		if(y_pos > 0){
			direction = UP;
		}
		else{
			direction = DOWN;
		}
	}
	return direction;
}

int mov_read_button(button b){
	int button_pushed = 0; 
	switch (b){
		case jb:{
			if(DEBUG_BUTTON){
				printf("Reading joystick button:\r\n");
			}
			button_pushed = !(PINB & (1 << PB2));
			break;
		}
		case rb:{
			if(DEBUG_BUTTON){
				printf("Reading right slider button:\r\n");
			}
			button_pushed = PINB & (1 << PB0);
			break;
		}
		case lb:{
			if(DEBUG_BUTTON){
				printf("Reading left slider button:\r\n");
			}
			button_pushed = PINB & (1 << PB1);
			break;
		}
		default:{
			if(DEBUG_BUTTON){
				printf("Invalid button selected\r\n");
			}
			break;
		}
	}
	if (button_pushed){
		if(DEBUG_BUTTON){
			printf("Button pressed\r\n");
		}
		return 1; 
	}
	return 0; 
}


input_j mov_get_joy_input(void){
	mov_pos_joy_rd();
	input_j joy_input;
	joy_input.pos_x = x_pos;
	joy_input.pos_y = y_pos;
	joy_input.j_button_pressed = mov_read_button(jb);
	joy_input.direction = mov_get_joy_dir();
	return joy_input;
}

input_s mov_get_slider_input(void){
	mov_pos_slider_rd();
	input_s slider_input;
	slider_input.pos_l_slider = l_pos;
	slider_input.pos_r_slider = r_pos;
	slider_input.r_button_pressed =  mov_read_button(rb);
	slider_input.l_button_pressed = mov_read_button(lb);
	return slider_input;
}


void mov_send_can_message(int CAN_ID){
	can_message movement_msg;
	movement_msg.id = CAN_ID;
	movement_msg.length = 4;
	switch (CAN_ID){
		case CAN_JOYSTICK_ID:{
			printf("\n\r");
			input_j joystick_input = mov_get_joy_input();
			movement_msg.data[0] = joystick_input.pos_x;
			movement_msg.data[1] = joystick_input.pos_y;
			movement_msg.data[2] = joystick_input.j_button_pressed;
			movement_msg.data[3] = joystick_input.direction;
			CAN_send_message(&movement_msg);
			break;
			}
		case CAN_SLIDER_ID:{
			printf("\n\r");
			input_s slider_input = mov_get_slider_input();
			movement_msg.data[0] = slider_input.pos_r_slider;;
			movement_msg.data[1] = slider_input.pos_l_slider;
			movement_msg.data[2] = slider_input.r_button_pressed;
			movement_msg.data[3] = slider_input.l_button_pressed;
			CAN_send_message(&movement_msg);
			break;
		}
		default:
			printf("Invalid CAN message ID");
			break;
		}

}
