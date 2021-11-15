/*
 * game_driver.c
 *
 * Created: 25.10.2021 14:49:45
 *  Author: elisegm
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "game_driver.h"
#include "movement_driver.h"
#include "menu.h"


volatile int SEND_GAME_MSG =  0;

volatile game_state current_state = INIT; 

void game_set_state(game_state state){
	current_state = state;
}

game_state game_get_state(void){
	return current_state;
}



void game_interrupt_enable(void){
	TIMSK = (1 << TOIE0) | (1 << TOIE1); // enable timer overflow 
	
	// frequency = 4915200 / 255 (0xFF) / 1024 = 18.82 times per sec
	TCNT0 = 0x00; // initial value is 0
	TCCR0 = ( 1 << CS02) | ( 1 << CS00); // start with 1024 prescaler
}

void game_interrupt_disable(void){
	TIMSK &= ~((1 << TOIE0) | (1 << TOIE1));
}

ISR(TIMER0_OVF_vect){

	SEND_GAME_MSG = 1;

	// reset TCNT0
	TCNT0 = 0x00;
}


void game_play(void){
	if(SEND_GAME_MSG){
		mov_send_can_message(CAN_JOYSTICK_ID);
		mov_send_can_message(CAN_SLIDER_ID);
		SEND_GAME_MSG = 0; 
	}
}
