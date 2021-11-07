#include "game_driver.h"
#include "sam.h"
#include "PWM_driver.h"
#include "motor_driver.h"
#include "can_interrupt.h"
#include "adc_driver.h"
#include "time.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

volatile int NEW_MOV_INPUT = 0; 
volatile int GAME_START = 0; 
volatile int playtime = 0; 
volatile highscore record; 

void game_init(void){
	time_start_counter();
	motor_power(1);
	playtime = 0; 
    //Pass på at servo er i nullposisjon på en eller annen måte. 
}

void game_update_highscore(void){
	printf("Current playtime is: %d \r\n", playtime);
	record.last_playtime = playtime;
	if(playtime > record.best_highscore){
		record.best_highscore = playtime;
	}
}

void game_joystick_controller(void){
	if (NEW_MOV_INPUT){
		int debug = 0;
		PWM_dutycycle_modify(debug);
		motor_controller();
		NEW_MOV_INPUT = 0; 
	}
}

void game_update_mov_msg(void){ 
	NEW_MOV_INPUT = 1; 
}

void game_play(void){
	if (GAME_START){
		game_init();
		int game_over = 0; 
		int ir_beam_lower_lim = 200; // Hva er denne? 
		
		while (!game_over){

			game_joystick_controller();
			uint32_t ir_beam = adc_rd();
			if (ir_beam < ir_beam_lower_lim){
				game_over = 1; 
			}
			time_update_counter(playtime);
		}

		game_over();

	}
}

void game_set_start_flag(void){
	printf("Starting the ping pong game\r\n");
	GAME_START = 1; 
}

void game_over(void){
	GAME_START = 0; 
	motor_power(0); // Turns off motor
	time_stop_counter(); // Stops
	game_update_highscore();

	CAN_MESSAGE end_game_msg;
	end_game_msg.id = CAN_GAME_END_ID;
	end_game_msg.data_length = 2;
	end_game_msg.data[0] = record.best_highscore;
	end_game_msg.data[1] = record.last_playtime;
	can_send(&end_game_msg, 0);	// Mailbox 0? 
}