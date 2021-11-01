/*
 * delay.c
 *
 * Created: 01.11.2021 16:53:14
 *  Author: elisegm
 */ 

#include "sam.h"
#include <stdio.h>
#include <unistd.h>
#include "delay.h"
#include "uart.h"
#include "printf-stdarg.h"


void delay_ms(int delay){
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

void delay_us(int delay){
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