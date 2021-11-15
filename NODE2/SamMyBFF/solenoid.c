/*
 * solenoid.c
 *
 * Created: 08.11.2021 12:18:28
 *  Author: emiliamo
 */ 

#include <stdio.h>

#include "solenoid.h"
#include "sam.h"


volatile int not_triggered = 0;

void solenoid_init(void){
	PIOC->PIO_PER |= PIO_PER_P12;
	PIOC->PIO_OER |= PIO_OER_P12;
	PIOC->PIO_SODR |= PIO_SODR_P12;
}

void solenoid_shoot(int button_pushed){
	if (!not_triggered & button_pushed){
		not_triggered = 1;
		PIOC->PIO_CODR |= PIO_CODR_P12; 
		time_delay_ms(100);
		PIOC->PIO_SODR |= PIO_SODR_P12; 
	}
	else if (!button_pushed){
		not_triggered = 0;
	}
}