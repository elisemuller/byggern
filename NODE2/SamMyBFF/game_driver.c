#include "game_driver.h"
#include "sam.h"
#include "PWM_driver.h"
#include "motor_driver.h"
#include "can_interrupt.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

volatile int NEW_JOY_INPUT = 0; 

void game_init(void){
    //Pass på at servo er i nullposisjon på en eller annen måte. 
}

void game_end(void){

}

void game_score_counter(void){
	
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