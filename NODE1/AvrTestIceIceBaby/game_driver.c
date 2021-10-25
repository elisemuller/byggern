/*
 * game_driver.c
 *
 * Created: 25.10.2021 14:49:45
 *  Author: elisegm
 */ 

#include "game_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

void game_interrupt_enable(void){
	TIMSK = (1 << TOIE0) | (1 << TOIE1); // enable timer overflow 
	
	// frequency = 4915200 / 255 (0xFF) / 1024 = 18.82 times per sec
	TCNT0 = 0x00; // initial value is 0
	TCCR0 = ( 1 << CS02) | ( 1 << CS00); // start with 1024 prescaler
}

void game_interrupt_disable(void){
	// disable
	TIMSK &= ~((1 << TOIE0) | (1 << TOIE1));
}

ISR(TIMER0_OVF_vect){
	// send joystick pos
	input_j joystick_pos = mov_get_joy_input();
	CAN_send_message(&joystick_pos);
	// send slider pos
	input_s slider_pos = mov_get_slider_input();
	CAN_send_message(&slider_pos);
	// reset TCNT0
	TCNT0 = 0x00;
}