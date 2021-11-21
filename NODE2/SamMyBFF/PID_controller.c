/*
 * PID.c
 *
 * Created: 08.11.2021 14:29:56
 *  Author: emiliamo
 */ 

#include <stdint.h>

#include "PID_controller.h"
#include "sam.h"
#include "motor_driver.h"

#define MCK 84000000
#define SAMPLING_PERIOD 1/1000
#define ENC_LOWER_LIM 0
#define ENC_UPPER_LIM 9000
#define DEBUG 0

volatile int Kp_inv = 3;
volatile int Ki = 3; 

volatile int us = 0;
volatile int posteriori_error = 0; 
volatile int ref_pos = 0; 
volatile int integration_error = 0; 

volatile int UPDATE_PID = 0; 
volatile dir direction = NEUTRAL;



void PID_controller(void){
	if(DEBUG){printf("UPDATE_PID: %d\n\r", UPDATE_PID);}
	if (UPDATE_PID){
		PID_set_ref();
		uint16_t curr_pos = motor_read_encoder();
		
		if( curr_pos & (1 << 15) ){
			curr_pos = ENC_UPPER_LIM;
			if(DEBUG){printf("Lower lim\n\r");}
		}
		else if (curr_pos > ENC_UPPER_LIM){
			curr_pos = ENC_LOWER_LIM;
			if(DEBUG){printf("Upper lim\n\r");}
		}
		
		
		if(DEBUG){printf("Current position = %d \n\r", curr_pos);}
		
		int priori_error = posteriori_error; 
		posteriori_error = (ref_pos - curr_pos);
		integration_error += posteriori_error*SAMPLING_PERIOD;
	
		//int input_u = Kp*error + (Kd/SAMPLING_PERIOD)*(posteriori_error - priori_error); // PD
		int input_u = posteriori_error/Kp_inv+ Ki*integration_error; // PI
		//int input_u = posteriori_error/Kp_inv+ Ki*integration_error + (Kd/SAMPLING_PERIOD)*(posteriori_error - priori_error); // PID
	
		input_u = abs(input_u);		
		
		if(DEBUG){printf("Error: %d \n\r", posteriori_error);}
			
		printf("\n\r");
		
		if(posteriori_error > 20 ){
			direction = LEFT;
		}
		else if (posteriori_error < -20){
			direction = RIGHT;
		}
		
		
	
		if(DEBUG){printf("direction: %d \n\r", direction);}
			
		motor_set_direction(direction);
		motor_set_speed((uint16_t)input_u);
		UPDATE_PID = 0; 
	}
}


void PID_init(void){
	motor_init();
	
    PMC->PMC_PCER0 |= PMC_PCER0_PID27; // ID TC0

    // Timer clock = MCK/128 , RC Compare resets the counter and starts the counter clock
    TC0->TC_CHANNEL[0].TC_CMR |= (TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_CPCTRG);

    // Enables the timer clock
    TC0->TC_CHANNEL[0].TC_CCR |= (TC_CCR_CLKEN | TC_CCR_SWTRG); 

    TC0->TC_CHANNEL[0].TC_RC = 656; // MCK/128/TC_RC 
	
	// Enables interrupt when RC = TC_CV (Current val in counter)
    TC0->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS;

    
    TC0->TC_CHANNEL[0].TC_CCR &= ~(TC_CCR_CLKDIS);
	
}


void TC0_Handler(void){
	TC0->TC_CHANNEL[0].TC_SR;
	UPDATE_PID = 1;
}

void PID_set_ref(void){
	float ref;
	input_s slider = can_get_slider_input();
	int s_r = slider.pos_r_slider;
	if(DEBUG) {printf("Slider pos: %d \n\r", s_r);}
	
	int s_l = slider.pos_l_slider;
	s_l -= 100;
	s_l = abs(s_l);
	
	if(DEBUG) {printf("Slider pos: %d \n\r", s_l);}
	
	ref_pos = 90*(s_l);	

	if (DEBUG) {printf("Reference for encoder: %d\n\r", ref_pos);}
}



void PID_reset(void){
	posteriori_error = 0; 
	integration_error = 0; 
	ref_pos = 0; 
}

void PID_set_parameters(int kp_inv, int ki){
	Kp_inv = kp_inv;
	Ki = ki;
}