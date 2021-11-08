/*
 * game_driver.c
 *
 * Created: 25.10.2021 14:49:45
 *  Author: elisegm
 */ 

#include "game_driver.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "movement_driver.h"
#include "CAN_driver.h"
#include "menu.h"
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 4915200

volatile int send_counter = 0;


volatile int START_GAME = 0;

volatile int SEND_GAME_MSG =  0;


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

	SEND_GAME_MSG = 1;

	// reset TCNT0
	TCNT0 = 0x00;
}

void game_play(void){
	if(START_GAME){
		if(SEND_GAME_MSG){
			//printf("Sending message\r\n");
			mov_send_can_message(CAN_JOYSTICK_ID);
			mov_send_can_message(CAN_SLIDER_ID);
			SEND_GAME_MSG = 0; 
		}
	}
	else{
		menu_state_controller();
		
	}
	

}

void game_set_start_flag(void){
	START_GAME = 1; 
	game_interrupt_enable();
	can_message menu_msg;
	menu_msg.id = CAN_GAME_START_ID;
	menu_msg.length = 1;
	menu_msg.data[0] = 1;
	CAN_send_message(&menu_msg);
}

void game_set_end_flag(void){
	START_GAME = 0; 
	OLED_reset();
	OLED_print("Game over loser");
	_delay_ms(5000);
	menu_print();
	game_interrupt_disable();
	//fikse highscore her? 
}