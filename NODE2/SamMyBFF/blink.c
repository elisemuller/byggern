/*
 * blink.c
 *
 * Created: 11.10.2021 12:53:11
 *  Author: elisegm
 */ 

#include "sam.h"
#include <stdio.h>
#include <unistd.h>
#include "delay.h"
#include "blink.h"

void led_enable(void){
	// bruker pin 19 og 20 på port A
	// peripheral enable register
	PIOA->PIO_PER |= (0b11 << 19);
	// output enable register
	PIOA->PIO_OER |= (0b11 << 19);
}

void blink(void) {
	// sett output
	PIOA->PIO_SODR = PIO_SODR_P19;
	PIOA->PIO_CODR = PIO_CODR_P20;
	delay_ms(1000);
	
	 //clear output
	PIOA->PIO_CODR = PIO_CODR_P19;

	PIOA->PIO_SODR = PIO_SODR_P20;
	delay_ms(1000);
}