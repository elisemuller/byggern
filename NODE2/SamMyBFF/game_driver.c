
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
#include "buzzer_driver.h"


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

void game_wifi_init(void) {
	PIOD->PIO_PER |= PIO_PER_P3 | PIO_PER_P4 | PIO_PER_P5 | PIO_PER_P6 | PIO_PER_P7 | PIO_PER_P8;
	PIOD->PIO_OER |= PIO_OER_P3 |  PIO_OER_P4 | PIO_OER_P5 | PIO_OER_P6 | PIO_OER_P7 | PIO_OER_P8;
	PIOD->PIO_CODR |= PIO_CODR_P3 |  PIO_CODR_P4 | PIO_CODR_P5 | PIO_CODR_P6 | PIO_CODR_P7 | PIO_CODR_P8;
}

void game_init(void){
	PWM_init();
	adc_init();
	solenoid_init();
	PID_init();
	motor_reset_encoder();
	game_wifi_init();
}

void game_write_score_wifi(int game_score) {
	int pin0 = (game_score & (1 << 0));
	int pin1 = (game_score & (1 << 1));
	int pin2 = (game_score & (1 << 2));
	int pin3 = (game_score & (1 << 3));
	int pin4 = (game_score & (1 << 4));
	int pin5 = (game_score & (1 << 5));
	if (pin0) {
		PIOD->PIO_SODR |= (PIO_SODR_P4);
	} else {
		PIOD->PIO_CODR |= (PIO_CODR_P4);
	}
	if (pin1) {
		PIOD->PIO_SODR |= (PIO_SODR_P5);
	} else {
		PIOD->PIO_CODR |= (PIO_CODR_P5);
	}
	if (pin2) {
		PIOD->PIO_SODR |= (PIO_SODR_P7);
	} else {
		PIOD->PIO_CODR |= (PIO_CODR_P7);
	}
	if (pin3) {
		PIOD->PIO_SODR |= (PIO_SODR_P8);
	} else {
		PIOD->PIO_CODR |= (PIO_CODR_P8);
	}
	if (pin4) {
		PIOD->PIO_SODR |= (PIO_SODR_P3);
		} else {
		PIOD->PIO_CODR |= (PIO_CODR_P3);
	}
	if (pin5) {
		PIOD->PIO_SODR |= (PIO_SODR_P6);
	} else {
		PIOD->PIO_CODR |= (PIO_CODR_P6);
	}
}

void game_update_highscore(void){
	game_write_score_wifi(playtime);
	record.last_playtime = playtime;
	if(playtime > record.best_highscore){
		record.best_highscore = playtime;
		game_set_state(VICTORY);
	}
	else{
		game_set_state(GAME_OVER);
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

	//printf("Game over. Playtime: %d \n\r",playtime);

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
	printf("Playtime: %d\r\n", playtime);
	game_update_highscore();
	buzzer_stop_music(0);
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
			PID_set_parameters(3, 3);
			break;
		case HARD:
			PID_set_parameters(1, 2);
			break;
		default:
			printf("Invalid level chosen, EASY by default\n\r");
			PID_set_parameters(1, 2);
			break;
	}
}

