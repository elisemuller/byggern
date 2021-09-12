/*
 * ADC_driver.c
 *
 * Created: 06.09.2021 15:25:05
 *  Author: elisegm
 */ 

//#define BASE_ADDRESS 0x1400

#include <avr/io.h>
#include <stdio.h>
#include "ADC_driver.h"
#include "xmem.h"




void adc_init(void); 

volatile uint8_t adc_read(uint8_t channel);

void adc_calibrate(void); //should find the returned adc values at the extrems of the x and y axis


//these returned adc values should then be used in pos_read for caluculating
pos_t pos_read(void); //and returning the joystick state on a more suitable scale (ex: 1-100 for each axis) 


