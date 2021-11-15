/*
 * can_interrupt.h
 *
 * Author: Gustav O. Often and Eivind H. Jølsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 


#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_

#define CAN_JOYSTICK_ID 1
#define CAN_SLIDER_ID 2
#define CAN_GAME_START_ID 3
#define CAN_GAME_END_ID 4
#define CAN_BUZZER_ID 5
#define CAN_GAME_LEVEL_ID 6


#include "can_controller.h"

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	UNDEFINED
} dir;

typedef struct input_joystick {
	int pos_x;
	int pos_y;
	int button_pressed;
	dir direction; 
} input_j;

typedef struct input_slider {
	int pos_r_slider;
	int pos_l_slider;
	int r_button_pressed;
	int l_button_pressed;
} input_s;



void CAN0_Handler       ( void );

/**
* @brief Collects and redistributes data from message according to the message ID.  
* @param msg Message received from CAN bus
*/
void message_data_collector(CAN_MESSAGE msg);

/**
* @brief Returns the joystick variable updated in @func message_data_collector()
* @return input_j
**/
input_j can_get_joy_input(void);

/**
* @brief Returns the slider variable updated in @func message_data_collector()
* @return input_s
**/
input_s can_get_slider_input(void);



#endif /* CAN_INTERRUPT_H_ */
