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


/** 
* Initializes PWM signal to be used in ADC conversion
**/
void adc_init(void); 

volatile uint8_t adc_rd(uint8_t channel);


#endif /* ADC_DRIVER_H_ */
