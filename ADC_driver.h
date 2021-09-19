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

typedef struct {
  int pos_x;
  int pos_y;
} pos_t;

enum joystick_dir {
  LEFT,
  RIGHT, 
  UP, 
  DOWN, 
  NEUTRAL
  };
  
/** 
* Initializes PWM signal to be used in ADC conversion
**/
void adc_init(void); 

volatile uint8_t adc_read(uint8_t channel);

pos_t pos_read(void); 

void adc_calibrate(void); //should find the returned adc values at the extrems of the x and y axis
//
//
////these returned adc values should then be used in pos_read for caluculating
//pos_t pos_read(void); //and returning the joystick state on a more suitable scale (ex: 1-100 for each axis) 



#endif /* ADC_DRIVER_H_ */
