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
#include "UART_driver.h"
#include <stdint.h>
#include <stdlib.h>


volatile int x_pos;
volatile int y_pos;

volatile int r_pos;
volatile int l_pos;


volatile int null_x;
volatile int null_y;




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

volatile uint8_t adc_rd(uint8_t channel){
		
	xmem_write(channel, OFFSET_ADC);
	_delay_ms((9*4*2/F_CPU));
	
	uint8_t channel_data;
	
	for (int ch = 0; ch < channel; ch++){
		channel_data = xmem_read(OFFSET_ADC);
	}
	
	return channel_data;
}



