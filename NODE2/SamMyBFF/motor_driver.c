/*
 * motor_driver.c
 *
 * Created: 25.10.2021 09:01:08
 *  Author: elisegm
 */ 

#include "motor_driver.h"
#include <stdint.h>
#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "time.h"


#define MJ2_ENCODER_DATA (PIO_PER_P1 | PIO_PER_P2 | PIO_PER_P3 | PIO_PER_P4 | PIO_PER_P5 | PIO_PER_P6 | PIO_PER_P7 | PIO_PER_P8)


void motor_init(void){
	
	// Enable peripheral clocks
	PMC->PMC_PCER1 |= PMC_PCER1_PID38; // DACC
	PMC->PMC_PCER0 |= (PMC_PCER0_PID13 | PMC_PCER0_PID14); // PIOC and PIOD
	
	// Select channel 1 for DACC
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CHER |= DACC_CHER_CH1;
	
	// MJ2: Enable IO pins for encoder data D(0-7)
	PIOC->PIO_PER |= MJ2_ENCODER_DATA;
	
	// MJ2: Disable output, enable input for encoder data D(0-7)
	PIOC->PIO_ODR |= MJ2_ENCODER_DATA;
	
	// MJ1: Enable IO pins 
	PIOD->PIO_PER |= PIO_PER_P0; // !OE
	PIOD->PIO_PER |= PIO_PER_P1; // !RST
	PIOD->PIO_PER |= PIO_PER_P2; // SEL
	PIOD->PIO_PER |= PIO_PER_P10; //DIR

	PIOD->PIO_PER |= PIO_PER_P9; // EN
	
	// MJ1: Enable output
	PIOD->PIO_OER |= (PIO_PER_P0 | PIO_PER_P1 | PIO_PER_P2 | PIO_PER_P10);
	PIOD->PIO_OER |= (PIO_PER_P9);
	
}

//PD0 --> Input for analog signal som skal konverteres til a_out [-5 5]

void motor_set_speed(uint32_t speed){
	DACC->DACC_CDR = DACC_CDR_DATA(speed);
	
	//Implementere direction utfira om speed er negativ/positiv
	//Set motor speed by adjusting dac voltage
	// Use DACC_CDR register to write to motor speed. 
	//PIOD->PIO_SODR = PIO_SODR_P9; // EN = 1 --> Skrur p� motoren
}

void motor_power(int on){
	if (on){
		PIOD->PIO_SODR = PIO_SODR_P9;
	}
	else {
		PIOD->PIO_CODR = PIO_CODR_P9; 
	}
	
}

void motor_reset_encoder(int reset){
	if (reset){
		PIOD->PIO_CODR = PIO_CODR_P1;
	}
	else {
		PIOD->PIO_SODR = PIO_SODR_P1;
	}
	
}

uint16_t motor_read_encoder(void){
	uint16_t high_byte;
	uint16_t low_byte;
	uint16_t encoder_data;
	int debug = 1; 
	motor_reset_encoder(0);
	// Legge inn at dersom retning er i negativ retning s� vil vi m�tte lese 2's komplement.
	PIOD->PIO_CODR = PIO_CODR_P0; // !OE low to enable output of encoder
	PIOD->PIO_CODR = PIO_CODR_P2; // SEL low to get high byte
	
	time_delay_us(20);
	high_byte = ((PIOC->PIO_PDSR | MJ2_ENCODER_DATA) << 8);
	PIOD->PIO_SODR = PIO_SODR_P2; // SEL high to get low byte
	
	time_delay_us(20);
	low_byte = (PIOC->PIO_PDSR | MJ2_ENCODER_DATA);
	encoder_data = (high_byte | low_byte);
	
	//Reset dersom vi hele tida vil resette hvor encoderen er? 
	if(debug){printf("Encoder data: %d\r\n", encoder_data);}
	PIOD->PIO_SODR = PIO_SODR_P0; // !OE high to disable output of encoder
	return encoder_data;
}

void motor_set_direction(dir direction){
	if(direction == RIGHT) {
		PIOD->PIO_SODR |= PIO_SODR_P10;
	}
	else if (direction == LEFT) {
		PIOD->PIO_CODR |= PIO_CODR_P10;
	}
	//Stop motor in neutral
}

void motor_controller(void){
	input_j joystick = can_get_joy_input();
	int j_x = joystick.pos_x;
	            // if j_x is represented by a negative number in two's complement:
	            // --> Convert to negative number between -100 and 0
	if((j_x <= 0xff) && (j_x >= 0x9c)){
		j_x = ~(j_x-1) * (-1);
	}

	if((j_x <= 100) && (j_x >= 5)){
		uint32_t speed = j_x * 20; 
		//printf("speed in right direction: %d\r\n",speed);
		motor_set_direction(RIGHT);
		motor_set_speed(speed);
	}
	
	else if((j_x >= -100) && (j_x < -5)){
		uint32_t speed = -(j_x * 20);
		//printf("speed in left direction: %d\r\n",speed);
		motor_set_direction(LEFT);
		motor_set_speed(speed);
	}
	else{
		motor_set_speed(0);
	}
}


// testing push from pc 