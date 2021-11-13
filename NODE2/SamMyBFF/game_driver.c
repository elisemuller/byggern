#include "game_driver.h"
#include "sam.h"
#include "PWM_driver.h"
#include "motor_driver.h"
#include "can_interrupt.h"
#include "adc_driver.h"
#include "time.h"
#include "blink.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

volatile int NEW_MOV_INPUT = 0; 
volatile int GAME_START = 0; 
volatile int playtime = 0; 
volatile int game_over = 0; 
volatile highscore record; 
volatile int start_time = 0; 

volatile game_state current_state = INIT;

void game_init(void){
	motor_power(1);
	start_time = time_get_count(s); 
	//playtime = 0; 
    //Pass på at servo er i nullposisjon på en eller annen måte. 
}

void game_update_highscore(void){
	record.last_playtime = playtime;
	if(playtime > record.best_highscore){
		record.best_highscore = playtime;
	}
	printf("Current playtime is: %d \r\n", playtime);
	printf("Highscore: %d\n\r", record.best_highscore);
}

void game_joystick_controller(void){
	
	if (NEW_MOV_INPUT){
		//printf("controlling joystick \n\r");
		int debug = 0;
		input_s slider = can_get_slider_input();
		PWM_dutycycle_modify(debug, SERVO_CHANNEL, 0);
		motor_controller();
		// PID_controller();
		solenoid_shoot(slider.l_button_pressed);
		NEW_MOV_INPUT = 0; 
	}
}

void game_update_mov_msg(void){ 
	
	NEW_MOV_INPUT = 1; 
}

void game_ended(void){
	GAME_START = 0;
	game_over = 0; 
	motor_power(0); // Turns off motor
	//time_stop_counter_us(); // Stops
	game_update_highscore();
	printf("Game over. Playtime: %d \n\r",playtime);

	CAN_MESSAGE end_game_msg;
	end_game_msg.id = CAN_GAME_END_ID;
	end_game_msg.data_length = 2;
	end_game_msg.data[0] = record.best_highscore;
	end_game_msg.data[1] = record.last_playtime;
	NVIC_DisableIRQ(TC0_IRQn);
	can_send(&end_game_msg, 0);	// Mailbox 0?
}

void game_play(void){
	motor_reset_encoder();
	NVIC_EnableIRQ(TC0_IRQn);
	playtime = 0; 
	printf("Game started\n\r");
	game_init();
	int ir_beam_lower_lim = 800; 
		
	while (!game_over){
			
		int current_time = time_get_count(s); 
		//motor_read_encoder();
		game_joystick_controller();
		uint32_t ir_beam = adc_rd();
		//printf("IR value: %d\n\r",ir_beam);
		if (ir_beam < ir_beam_lower_lim){
			game_over = 1; 
		}
		int time_diff = (current_time - start_time);
		playtime = time_diff;
		//printf("Playtime : %d\n\r",playtime);
	}
	game_set_state(GAME_OVER);
}



void game_set_state(game_state state){
	current_state = state;
}

game_state game_get_state(void){
	return current_state;
}

