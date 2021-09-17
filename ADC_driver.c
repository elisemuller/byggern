/*
 * ADC_driver.c
 *
 * Created: 06.09.2021 15:25:05
 *  Author: elisegm
 */

#define F_CPU 4915200

// channel1: 0x0001
// channel2: 0x0010
// channel3: 0x0100

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "ADC_driver.h"
#include "xmem.h"

//volatile char *ext_mem = (char *) BASE_ADDRESS_ADC; Edited

void adc_init(void){
	
	//DDRB |= 1;
	//
	//TCCR0 |= (1 << WGM01);
	//TCCR0 &= ~(1 << WGM01);
	//
	//TCCR0 &= ~(1 << COM01);
	//TCCR0 |= (1 << COM00);
	//
	//TCCR0 &= ~(1 << CS02);
	//TCCR0 &= ~(1 << CS01);
	//TCCR0 |= (1 << CS00);
	//
	//OCR0 = 0;


	DDRD |= (1 << PD5);		// Set PORTD pin 5 to output
	
	// PWM, phase correct
	TCCR1A &= ~(0b1111 << WGM10);
	// TCCR1A |= (1 << WGM11) | (1 << WGM10); // 0011. Phase correct. 10 bit.?????
	// TCCR1A |= (1 << WGM13);
	// TCCR1A |= (1 << WGM13) | (1 << WGM10); // Phase and frequency correct
	TCCR1A |= (1 << WGM13) | (1 << WGM11) | (1 << WGM10);
	
	TCCR1A |= (1 << COM1A1); // 10. Clear when up-counting.
	TCCR1A &= ~(1 << COM1A0);
	
	// frequency: f/8
	TCCR1B &= ~(7 << CS10);	// set 0 on CS11 and CS12
	TCCR1B |= (1 << CS10);	// set 1 on CS10
	
	OCR1A = 0x01FF; // duty cycle 50%
}

void adc_init(void) {
	//Configure PD5 pin as output
	DDRD |= (1 << PD5); 
	
	//Timer without prescaling
	TCCR0 &= ~(7 << CS00); // Set CS00, CS01, CS02 to 0
	TCCR0 |= (1 << CS00); // Set CS00 to 1
	
	// Waveform generation mode = CTC, Top = OCR0
	TCCR0 &= ~(1 << WGM00); // WGM00 = 0
	TCCR0 |= (1 << WGM01); // WGM01 = 1
	
	// Toggles pin PD5 when TCNT0 = OCR0
	TCCR0 &= ~(1 << COM01); // COM01 = 0
	TCCR0 |= (1 << COM00); // COM00 = 1
	
	// Defines the top value for the counter
	OCR0 = 1;
}	

volatile uint8_t adc_read(uint8_t channel){
	
	//ext_mem[0] = (0x80 | channel); edited
	
	xmem_write(channel, BASE_ADDRESS_ADC, 0x1000); //edited

	_delay_ms((9*4*2/F_CPU)); //t_conv evt bruk delay = 20 us
	
	char data;
	
	//consecutive read pulses
	for (int i = 0; i <= channel; i++){
		//data = ext_mem[0];
		data = xmem_read(BASE_ADDRESS_ADC, 0x1000); //edited
	}
	
	
	return data;

}

//void adc_calibrate(void); //should find the returned adc values at the extrems of the x and y axis


//these returned adc values should then be used in pos_read for calculating
//pos_t pos_read(void); //and returning the joystick state on a more suitable scale (ex: 1-100 for each axis) 


