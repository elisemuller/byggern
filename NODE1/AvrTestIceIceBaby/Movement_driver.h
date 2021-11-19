/*
 * Movement_driver.h
 *
 * Created: 20.09.2021 16:54:56
 *  Author: elisegm
 */

/**
 * @file
 * @brief Functionality and hardware interface for the joystick and slider
 */


#ifndef MOVEMENT_DRIVER_H_
#define MOVEMENT_DRIVER_H_

/**
* @enum Button types.
*/
typedef enum {
	jb,
	rb,
	lb,
} button;

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
	int j_button_pressed;
	dir direction;
} input_j;

typedef struct input_slider {
	int pos_r_slider;
	int pos_l_slider;
	int r_button_pressed;
	int l_button_pressed;
} input_s;


/**
* @brief Calibrates the neutral state of the joystick and configures button pins as input.
*/
void mov_init(void);

/**
* @brief Reads the position of the joystick controller
*/
void mov_pos_joy_rd(void);

/**
* @brief Reads the position of the slider
*/
void mov_pos_slider_rd(void);


/**
* @brief Calculates the direction of the joystick controller
* @return The direction of the joystick controller
*/
dir mov_get_joy_dir(void);

/**
* @brief Calculates the direction of the joystick controller
* @param[in] b Button type
* @return 1 if the button type @p b is pressed, else 0
*/
int mov_read_button(button b);

/**
* @brief Collects input from the joystick controller
* @return Input information from joystick controller
*/
input_j mov_get_joy_input(void);

/**
* @brief Collects input from the slider
* @return Input information from slider
*/
input_s mov_get_slider_input(void);

/**
* @brief Creates and send a can message containing input info from the joystick or slider
* @param[in] CAN_ID that spesifices what type of message is to be sent
*/
void mov_send_can_message(int CAN_ID);

#endif /* MOVEMENT_DRIVER_H_ */
