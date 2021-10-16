/*
 * Movement_driver.h
 *
 * Created: 20.09.2021 16:54:56
 *  Author: elisegm
 */ 


#ifndef MOVEMENT_DRIVER_H_
#define MOVEMENT_DRIVER_H_

typedef struct pos_joystick {
	int pos_x;
	int pos_y;
} pos_j;

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

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	UNDEFINED
} dir;

typedef struct pos_slider {
	int pos_r_slider;
	int pos_l_slider;
} pos_s;


/**
* @brief Finds the neutral position of the joystick for x and y
* 
* @return void
*/
void mov_init(void);

/**
* @brief Reads the joystick position for x and y
*
* @return void
*/
void mov_pos_joy_rd(void);

void mov_pos_slider_rd(void);

pos_j mov_get_joy_pos(void);

dir mov_get_joy_dir(void);

pos_s mov_get_slider_pos(void);

int mov_read_joy_button(void);

int mov_read_r_slider_button(void);

int mov_read_l_slider_button(void);

input_j mov_get_joy_input(void);

input_s mov_get_slider_input(void);

#endif /* MOVEMENT_DRIVER_H_ */
