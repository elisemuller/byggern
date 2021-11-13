/*
 * PID.c
 *
 * Created: 08.11.2021 14:29:56
 *  Author: emiliamo
 */ 


#include "PID_controller.h"
#include "sam.h"
#include "stdlib.h"
#include "motor_driver.h"

#define MCK 84000000
#define SAMPLING_PERIOD 1/1000
#define ENC_LOWER_LIM 0
#define ENC_UPPER_LIM 0
#define ENC_MID_POS 0

volatile int Kp;
volatile int Ki; 
volatile int Kd;
volatile int us= 0;

volatile int timer_test;
volatile int posteriori_error = 0; 
volatile int ref_pos = 0; 
volatile int integration_error = 0; 
volatile int UPDATE_PID = 0; 


// Vi må finne rangen til encoderen 
// --> Gjøres ved å kjøre encoderen helt til høyre, lese ut verdi, og så samme for venstre. 
// --> Lurt å regne ut midtverdi sånn ca. 
// Dette kalibreres da ut ifra joysticken, som vi sier gir ut -100 til 100. Altså vil vi kanskje kunne lese ut encoder, se om vi ligger høyre eller venstre og sette encoder utifra dette? 


void PID_controller(void){
	if (UPDATE_PID){
		PID_set_ref();
		uint16_t curr_pos = motor_read_encoder();
		dir direction;
		int priori_error = posteriori_error; 
		posteriori_error = (ref_pos - curr_pos);
		integration_error += posteriori_error*integration_error*SAMPLING_PERIOD;
	
		//int input_u = Kp*error + (Kd/SAMPLING_PERIOD)*(posteriori_error - priori_error); // PD
		int input_u = Kp*posteriori_error + Ki*integration_error; // PI
	
		if (input_u < 0){
			direction = LEFT;
		}
		else {
			direction = RIGHT;
		}
	
		input_u = abs(input_u);
	
		motor_set_direction(direction);
		motor_set_speed((uint16_t)input_u);
		UPDATE_PID = 0; 
	}
}

// Timer counter channel 0 slik at vi kan ha fastbestemt T

void PID_init(void){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27; // ID TC0

    // Timer clock = MCK/128 , RC Compare resets the counter and starts the counter clock
    TC0->TC_CHANNEL[0].TC_CMR |= (TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_CPCTRG);

    // Enables the timer clock
    TC0->TC_CHANNEL[0].TC_CCR |= (TC_CCR_CLKEN | TC_CCR_SWTRG); //Se om det finnes annen syntaks på dette

    TC0->TC_CHANNEL[0].TC_RC = 656; // MCK/128/TC_RC = 10 - dette skal liksom gi ms? (ifølge insp, men vil få matten til å gi mening selv)
	
	// Enables interrupt when RC = TC_CV (Current val in counter)
    TC0->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS;

    
    TC0->TC_CHANNEL[0].TC_CCR &= ~(TC_CCR_CLKDIS);
	
}


void TC0_Handler(void){
	TC0->TC_CHANNEL[0].TC_SR;
	UPDATE_PID = 1;
	us++;
	//timer_test++;
}

void PID_timer_test(void){
	printf("time: %d \n\r", timer_test/1000);
}

void PID_set_ref(void){
	int ref; 
	input_j joystick = can_get_joy_input();
	
	int j_x = joystick.pos_x;
	
	if((j_x <= 0xff) && (j_x >= 0x9c)){
		j_x = ~(j_x-1) * (-1);
	}
	
	ref_pos = (ENC_MID_POS-ENC_MID_POS*j_x/100)/(ENC_UPPER_LIM-ENC_LOWER_LIM);
}


void PID_delay_us(int delay){
	int start_time = us;
	
	
	while((us-start_time) < delay){
		//printf("us_counter %d\n\r", ((us_counter-start_time)/1000000));
	}
}
