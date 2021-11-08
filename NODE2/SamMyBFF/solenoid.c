/*
 * solenoid.c
 *
 * Created: 08.11.2021 12:18:28
 *  Author: emiliamo
 */ 

#include "solenoid.h"
#include "sam.h"
#include <stdio.h>

//volatile int triggered = 0;

void solenoid_init(void){
	PIOC->PIO_PER |= PIO_PER_P12;
	PIOC->PIO_OER |= PIO_OER_P12;
	PIOC->PIO_CODR |= PIO_CODR_P12;
	
}

void solenoid_shoot(int button_pushed){
	if (button_pushed){
		printf("I am sooo triggered right now!!!!\n\r");
		//triggered = 1;
		PIOC->PIO_SODR |= PIO_SODR_P12;
		//time_delay_ms(90);
		
		printf("Calm down omg.....\n\r");
	}
	else {
		PIOC->PIO_CODR |= PIO_CODR_P12;
		
		//triggered = 0;
	}
}