/*
 * delay.c
 *
 * Created: 01.11.2021 16:53:14
 *  Author: elisegm
 */ 

#include "sam.h"
#include <stdio.h>
#include <unistd.h>
#include "time.h"
#include "uart.h"

#define F_CPU 84000000UL


volatile int us_counter = 0;
volatile int ms_counter = 0;
volatile int s_counter = 0;


void time_delay_ms(int delay){
	ms_counter = time_get_count(ms);
	int start_time = ms_counter;
	
	while((ms_counter-start_time) < delay){
		ms_counter = time_get_count(ms);
		//printf("ms_counter %d\n\r", ((ms_counter-start_time)/1000));
	}
}

void time_delay_us(int delay){
	int start_time = us_counter;
	
	
	while((us_counter-start_time) < delay){
		//printf("us_counter %d\n\r", ((us_counter-start_time)/1000000));
	}

}


int time_get_count(time count){
	switch (count){
		case us: {
			return us_counter; 
		}
		case ms: {
			return us_counter/1000;
		}
		case s: {
			//printf("Seconds\n\r");
			s_counter = us_counter/1000000;
			return s_counter;
		}
	}
}

SysTick_Handler(){
	us_counter++;
}