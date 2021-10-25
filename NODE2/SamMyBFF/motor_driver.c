/*
 * motor_driver.c
 *
 * Created: 25.10.2021 09:01:08
 *  Author: elisegm
 */ 

#include "motor_driver.h"
#include <stdint.h>
#include "sam.h"

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
	PIOD->PIO_PER |= PIO_PER_P9; // EN
	PIOD->PIO_PER |= PIO_PER_P10; //DIR
	
	// MJ1: Enable output
	PIOD->PIO_OER |= (PIO_PER_P0 | PIO_PER_P1 | PIO_PER_P2 | PIO_PER_P9 | PIO_PER_P10);
	
}

//PD0 --> Input for analog signal som skal konverteres til a_out [-5 5]

void motor_set_speed(uint8_t speed){
	//Implementere direction utfira om speed er negativ/positiv
	//Bruker servo signal for å bestemme motor speed? 
	//Enable 
}
