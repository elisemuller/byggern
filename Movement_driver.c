///*
 //* Movement_driver.c
 //*
 //* Created: 20.09.2021 16:55:21
 //*  Author: elisegm
 //*/ 
//
//#include <avr/io.h>
//#include "ADC_driver.h"
//#include "Movement_driver.h"
//#include "UART_driver.h"
//#include <stdint.h>
//#include <stdlib.h>
//
//
//volatile int null_x;
//volatile int null_y;
//
//volatile int x_pos;
//volatile int y_pos;
//
//volatile int r_pos;
//volatile int l_pos;
//
//
//
//void mov_null_pos_calibrate(void){
	//null_x = adc_rd(JOYSTICK_CHANNEL_X);
	//null_y = adc_rd(JOYSTICK_CHANNEL_Y);
//}
//
//
//void mov_pos_joy_rd(void){
	//char x = adc_rd(JOYSTICK_CHANNEL_X);
	//char y = adc_rd(JOYSTICK_CHANNEL_Y);
	//int32_t data_x = (int32_t)x;
	//int32_t data_y = (int32_t)y;
//
	//if (data_x >= null_x ){
		//x_pos = (data_x - null_x)*100/(255 - null_x);
	//}
	//else {
		//x_pos = (data_x - null_x)*100/(null_x);
	//}
	//if (data_y >= null_y ){
		//y_pos = (data_y - null_y)*100/(255 - null_y);
	//}
	//else {
		//y_pos = (data_y - null_y)*100/(null_y);
	//}
//}
	//
//void mov_pos_slider_rd(void){
	//char right = adc_rd(SLIDER_CHANNEL_R);
	//char left = adc_rd(SLIDER_CHANNEL_L);
	//int32_t data_right = (int32_t)right;
	//int32_t data_left = (int32_t)left;
	//r_pos = (data_right*100)/255;
	//l_pos = (data_left*100)/255;
//}
//
	//
//pos_j mov_get_joy_pos(void){
	//mov_pos_joy_rd();
	//pos_j joystick_pos;
	//joystick_pos.pos_x = x_pos;
	//joystick_pos.pos_y = y_pos;
	//return joystick_pos;
//}
//
//pos_s mov_get_slider_pos(void){
	//mov_pos_slider_rd();
	//pos_s slider_pos;
	//slider_pos.pos_l_slider = l_pos;
	//slider_pos.pos_r_slider = r_pos;
	//return slider_pos;
	//
//}
//
//
//dir mov_get_joy_dir(void){
	//mov_pos_joy_rd();
	//const int neutral_threshold = 30;
	//dir direction = UNDEFINED;
	//
	//int abs_x = abs(x_pos);
	//int abs_y = abs(y_pos);
	//
	//if (abs_x < neutral_threshold && abs_y < neutral_threshold){
		//direction = NEUTRAL;
		//printf("Direction: NEUTRAL \r\n");
	//}
	//else if((abs_x > abs_y) && (abs_x > neutral_threshold)){
		//if (x_pos > 0){
			//direction = RIGHT;
			//printf("Direction: RIGHT \r\n");
		//}
		//else {
			//printf("Direction: LEFT \r\n");
			//direction = LEFT;
		//}
	//}
	//else if ((abs_y > abs_x) && (abs_y > neutral_threshold)){
		//if(y_pos > 0){
			//direction = UP;
			//printf("Direction: UP \r\n");
		//}
		//else{
			//direction = DOWN;
			//printf("Direction: DOWN \r\n");
		//}
	//}
	//return direction;
//}
//
//
