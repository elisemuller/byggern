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
#include "printf-stdarg.h"


void time_delay_ms(int delay){
	int counter = 0; 
	// Enables the counter
	SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
	
	// Value loaded to the VAL register when it reaches 0
	SysTick->LOAD |= (84000/8); // MCK / 8 / 1000
	
	while(counter < delay){
		if(SysTick->CTRL & (SysTick_CTRL_COUNTFLAG_Msk)){
			counter++;
		}
	}
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
}

void time_delay_us(int delay){
	int counter = 0;
	// Enables the counter
	SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
		
	// Value loaded to the VAL register when it reaches 0
	SysTick->LOAD |= (84/8); // MCK / 8 / 10^6
		
	while(counter < delay){
		if(SysTick->CTRL & (SysTick_CTRL_COUNTFLAG_Msk)){
			counter++;
		}
	}
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
}

void time_start_counter(void){
	SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
	SysTick->LOAD |= (84000000/8); // MCK / 8 

}

void time_update_counter(int &counter){
	if(SysTick->CTRL & (SysTick_CTRL_COUNTFLAG_Msk)){
		counter++;
		}
	}
}


void time_stop_counter(void){
	SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
}