/*
 * motor_driver.c
 *
 * Created: 25.10.2021 09:01:08
 *  Author: elisegm
 */ 

#include <stdint.h>

#include "motor_driver.h"
#include "sam.h"
#include "can_interrupt.h"
#include "time.h"


#define MJ2_ENCODER_DATA (0xFF)

volatile uint16_t start_point = 0;
volatile uint16_t end_point = 0;


void motor_init(void){
	
	// Enable peripheral clocks
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; // DACC
	PMC->PMC_PCER0 |= (PMC_PCER0_PID13 | PMC_PCER0_PID14); // PIOC and PIOD
	
	// Select channel 1 for DACC, 16 LSB data
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1 | DACC_MR_WORD_HALF;
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	
	
	// MJ1: Enable IO pins 
	PIOD->PIO_PER |= PIO_PER_P9; // EN
	PIOD->PIO_PER |= PIO_PER_P10; //DIR
	PIOD->PIO_PER |= PIO_PER_P2; // SEL
	PIOD->PIO_PER |= PIO_PER_P0; // !OE
	PIOD->PIO_PER |= PIO_PER_P1; // !RST
	
	PIOD->PIO_OER |= PIO_OER_P9; // EN
	PIOD->PIO_OER |= PIO_OER_P10; //DIR
	PIOD->PIO_OER |= PIO_OER_P2; // SEL
	PIOD->PIO_OER |= PIO_OER_P0; // !OE
	PIOD->PIO_OER |= PIO_OER_P1; // !RST	
	
	// MJ2: Enable IO pins for encoder data D(0-7)
	PIOC->PIO_PER |= MJ2_ENCODER_DATA;
	
	// MJ2: Disable output, enable input for encoder data D(0-7)
	PIOC->PIO_ODR |= MJ2_ENCODER_DATA;
	
	
	// MJ1: Enable output
	PIOD->PIO_CODR |= PIO_CODR_P0;
	
	motor_power(1);
		
}


void motor_set_speed(uint32_t speed){
	DACC->DACC_CDR = DACC_CDR_DATA(speed);
	
}

void motor_power(int on){
	if (on){
		PIOD->PIO_SODR |= PIO_SODR_P9;
	}
	else {
		PIOD->PIO_CODR |= PIO_CODR_P9; 
	}
	
}

void motor_reset_encoder(void){
	// Toggle to reset, active low reset pin. 
	PIOD->PIO_CODR = PIO_CODR_P1;
	time_delay_us(20);
	PIOD->PIO_SODR = PIO_SODR_P1;
	
}

void motor_calibrate_encoder(void){
	motor_power(1);
	motor_set_direction(RIGHT);
	motor_set_speed(2000);
	time_delay_ms(200);
	motor_set_speed(1000);
	time_delay_ms(1300);
	motor_reset_encoder();	
	start_point = motor_read_encoder();
	motor_set_direction(LEFT);
	motor_set_speed(600);
	time_delay_ms(1500);
	end_point = motor_read_encoder();
	uint16_t total_distance = end_point-start_point;
	printf("starting point: %d \n\r",start_point);
	printf("end point: %d \n\r",end_point);
	printf("distance: %d \n\r",total_distance);
	motor_power(0);
}

int16_t motor_read_encoder(void){
	uint16_t high_byte = 0;
	uint16_t low_byte = 0;
	int16_t encoder_data = 0;
	int debug = 0; 

	PIOD->PIO_CODR |= PIO_CODR_P2; // !OE low to enable output of encoder
	
	
	//PIOD->PIO_CODR |= PIO_CODR_P2; // SEL low to get high byte
	time_delay_us(30);
	// Right shift by 1 as encoder data is on pins 1-8. Then left shift by 8 to get high byte. 
	encoder_data |= (((PIOC->PIO_PDSR & MJ2_ENCODER_DATA) >> 1) << 8);
	

	PIOD->PIO_SODR = PIO_SODR_P2; // SEL high to get low byte
	time_delay_us(30);
	// Right shift by 1 as encoder data is on pins 1-8. 
	encoder_data |= (PIOC->PIO_PDSR & MJ2_ENCODER_DATA >> 1);

	if(encoder_data & (1 << 15)){
		encoder_data = -(~encoder_data + 1);
	}
	
	if(debug){printf("Encoder data: %d\n\r", encoder_data);}

	return encoder_data;
}


void motor_set_direction(dir direction){
	if(direction == RIGHT) {
		PIOD->PIO_SODR |= PIO_SODR_P10;
	}
	else if (direction == LEFT) {
		PIOD->PIO_CODR |= PIO_CODR_P10;
	}
}

void motor_controller(void){
	input_j joystick = can_get_joy_input();
	int j_x = joystick.pos_x;

	if((j_x <= 0xff) && (j_x >= 0x9c)){
		j_x = ~(j_x-1) * (-1);
	}
	if((j_x <= 100) && (j_x >= 5)){
		uint32_t speed = j_x * 20; 
		motor_set_direction(RIGHT);
		motor_set_speed(speed);
	}
	else if((j_x >= -100) && (j_x < -5)){
		uint32_t speed = -(j_x * 20);
		motor_set_direction(LEFT);
		motor_set_speed(speed);
	}
	else{
		motor_set_speed(0);
	}
}



