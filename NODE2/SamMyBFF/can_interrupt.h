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






#endif /* CAN_INTERRUPT_H_ */
