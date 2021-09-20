/*
 * ADC_driver.h
 *
 * Created: 06.09.2021 15:25:20
 *  Author: elisegm
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#define JOYSTICK_CHANNEL_X 1
#define JOYSTICK_CHANNEL_Y 2
#define SLIDER_CHANNEL_R 3
#define SLIDER_CHANNEL_L 4

#define NUM_JOYSTICK_CHANNELS 4

typedef struct pos_joystick {
	int pos_x;
	int pos_y;
} pos_t;

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
* Initializes PWM signal to be used in ADC conversion
**/
void adc_init(void); 

volatile uint8_t adc_rd(uint8_t channel);

void pos_joy_read(void); 

void adc_calibrate(void); //should find the returned adc values at the extrems of the x and y axis

//
////these returned adc values should then be used in pos_read for caluculating
//pos_t pos_read(void); //and returning the joystick state on a more suitable scale (ex: 1-100 for each axis) 

pos_t get_joy_pos(void);

dir get_dir(void);

pos_s get_slider_pos(void);

void pos_slider_read(void);

pos_t get_pos(void);

#endif /* ADC_DRIVER_H_ */
