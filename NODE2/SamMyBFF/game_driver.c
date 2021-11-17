
#include <stdio.h>
#include <stdint.h>

#include "game_driver.h"
#include "sam.h"
#include "PWM_driver.h"
#include "motor_driver.h"
#include "can_interrupt.h"
#include "adc_driver.h"
#include "time.h"
#include "PID_controller.h"
#include "solenoid.h"
#include "dac_driver.h"


volatile int NEW_MOV_INPUT = 0;
volatile int GAME_START = 0;
volatile int playtime = 0;
volatile int game_over = 0;
volatile highscore record;
volatile int start_time = 0;

volatile game_state current_state = INIT;

void game_start(void){
	start_time = time_get_count(s);
}

void game_init(void){
	PWM_init();
	adc_init();
	solenoid_init();
	PID_init();
	motor_reset_encoder();
	dac_init();
}

void game_update_highscore(void){
	record.last_playtime = playtime;
	dac_wr(playtime);
	if(playtime > record.best_highscore){
		record.best_highscore = playtime;
	}
	printf("Current playtime is: %d \r\n", playtime);
	printf("Highscore: %d\n\r", record.best_highscore);
}

void game_joystick_controller(void){

	if (NEW_MOV_INPUT){
		int debug = 0;
		input_s slider = can_get_slider_input();
		PWM_dutycycle_modify();
		//motor_controller();
		solenoid_shoot(slider.l_button_pressed);
		NEW_MOV_INPUT = 0;
	}
	PID_controller();
}

void game_update_mov_msg(void){

	NEW_MOV_INPUT = 1;
}

void game_ended(void){
	GAME_START = 0;
	game_over = 0;
	game_update_highscore();
	printf("Game over. Playtime: %d \n\r",playtime);

	CAN_MESSAGE end_game_msg;
	end_game_msg.id = CAN_GAME_END_ID;
	end_game_msg.data_length = 2;
	end_game_msg.data[0] = record.best_highscore;
	end_game_msg.data[1] = record.last_playtime;
	can_send(&end_game_msg, 0);
	NVIC_DisableIRQ(TC0_IRQn);
	PID_reset();
}

void game_play(void){
	motor_reset_encoder();
	NVIC_EnableIRQ(TC0_IRQn);
	playtime = 0;
	game_start();

	int ir_beam_lower_lim = 800;

	while (!game_over){

		int current_time = time_get_count(s);
		motor_read_encoder();
		game_joystick_controller();
		uint32_t ir_beam = adc_rd();
		if (ir_beam < ir_beam_lower_lim){
			game_over = 1;
		}
		int time_diff = (current_time - start_time);
		playtime = time_diff;
	}
	motor_set_direction(RIGHT);
	motor_set_speed(1000);
	time_delay_ms(1000);
	game_set_state(GAME_OVER);
}



void game_set_state(game_state state){
	current_state = state;
}

game_state game_get_state(void){
	return current_state;
}

void game_set_level(game_level lv){
	switch (lv) {
		case EASY:
			PID_set_parameters(3, 3, 0);
			break;
		case HARD:
			PID_set_parameters(1, 2, 0);
			break;
		default:
			printf("Invalid level chosen, EASY by default\n\r");
			PID_set_parameters(1, 2, 3);
			break;
	}
}

