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

volatile int NEW_JOY_INPUT = 0; 
volatile int playtime = 0; 

void game_init(void){
	time_start_counter();
    //Pass på at servo er i nullposisjon på en eller annen måte. 
}

int game_get_highscore(void){
	return playtime;
}

void game_joystick_controller(void){
	if (NEW_JOY_INPUT){
		int debug = 0;
		PWM_dutycycle_modify(debug);
		motor_controller();
		NEW_JOY_INPUT = 0; 
	}
}

void game_update_input_msg(void){
	NEW_JOY_INPUT = 1; 
}

void game_start(void){
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


}