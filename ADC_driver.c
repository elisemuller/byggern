/*
 * ADC_driver.c
 *
 * Created: 06.09.2021 15:25:05
 *  Author: elisegm
 */

#define F_CPU 4915200

#define OFFSET_ADC 0x0400

#include <avr/io.h>
#include <util/delay.h>
#include "ADC_driver.h"
#include "xmem.h"

static pos_t joystick_pos;


void adc_init(void){
	// Configure PD5 pin as output
	DDRD |= (1 << DDD5);

	// Timer without prescaling
	TCCR1B &= ~(7 << CS10); // Set CS10, CS11, CS12 to 0
	TCCR1B |= (1 << CS10); // Set CS10 to 1

	// Waveform generation mode = CTC, Top = OCR0
	TCCR1A &= ~(1 << WGM10); // WGM10 = 0
	TCCR1A &= ~(1 << WGM11); // WGM11 = 0
	TCCR1B |= (1 << WGM12); // WGM12 = 1
	TCCR1B &= ~(1 << WGM13); // WGM13 = 0
	
	// Toggles pin PD5 when TCNT0 = OCR0
	TCCR1A &= ~(1 << COM1A1); // COM1A1 = 0
	TCCR1A |= (1 << COM1A0); // COM1A0 = 1
	
	// Defines the top value for the counter
	OCR1A = 1;
	
}

volatile uint8_t adc_read(uint8_t channel){
		
	xmem_write(channel, OFFSET_ADC);
	_delay_ms((9*4*2/F_CPU));
	
	char channel_data;
	for (int ch = 0; ch < channel; ch++){
		data = xmem_read(OFFSET_ADC);
	}
	
	return channel_data;
}

pos_t pos_read(void){
	
	
	
}

//should find the returned adc values at the extrems of the x and y axis
void adc_calibrate(void){
	// joystick_pos.pos_x = adc_read(JOYSTICK_CHANNEL_X);
	// joystick_pos.pos_y = adc_read(JOYSTICK_CHANNEL_Y);
	
	for (int ch = 1; ch <= JOYSTICK_CHANNELS; ch++){
		joystick_pos[ch-1] = adc_read(ch);
		joystick_pos[ch-1] = (joystick_pos[ch]*(40/51));
		if (joystick_pos[ch] < 100){
			joystick_pos[ch] = -(100 - joystick_pos[ch]);
		}
		else {
			joystick_pos[ch] -= 100;
		}
	}
}

//should find the returned adc values at the extrems of the x and y axis


//these returned adc values should then be used in pos_read for calculating
//pos_t pos_read(void); //and returning the joystick state on a more suitable scale (ex: 1-100 for each axis) 


