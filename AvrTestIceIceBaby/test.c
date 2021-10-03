/*
 * test.c
 *
 * Created: 06.09.2021 12:50:21
 *  Author: elisegm
 */ 

#define F_CPU 4915200

#include "test.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

void test_address_decoder(void) {
	PORTC &= (0xF0);
	_delay_ms(250);
	
	PORTC |= (1 << 2); // 01
	_delay_ms(250);
	
	PORTC |= (1 << 3); // 11
	_delay_ms(250);
	
	PORTC &= (1 << 3); // 10
	_delay_ms(250);
}