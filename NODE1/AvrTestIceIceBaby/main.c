/*
 * NODE1.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#define F_CPU 4915200
#include <avr/interrupt.h>

#include <avr/io.h>
#include <stdio.h>
#include "UART_driver.h"
#include "sram_test.h"
#include "test.h"
#include "xmem.h"
#include "ADC_driver.h"
#include "movement_driver.h"
#include "OLED_driver.h"
#include "menu.h"
#include "mcp2515.h"
#include "SPI_driver.h"
#include "CAN_driver.h"

// -Wl,--defsym=__heap_start=0x801800,--defsym=__heap_end=0x801fff -Wl,--relax

int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	adc_init();
	mov_init();
	CAN_init(MODE_NORMAL);
	OLED_init();
	printf("######## Starting new session ########\r\n");

	while (1) {
		game_play();		
	}

}
