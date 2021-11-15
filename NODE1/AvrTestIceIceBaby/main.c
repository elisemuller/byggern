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
#include "game_driver.h"


#define DEBUG 0

// -Wl,--defsym=__heap_start=0x801800,--defsym=__heap_end=0x801fff -Wl,--relax

int main(void)
{
	uart_init( MYUBRR );
	xmem_init();
	adc_init();
	mov_init();
	CAN_init(MODE_NORMAL);
	//menu_init();
	

	printf("######## Starting new session ########\n\r");
	
	//test_CAN_loopback();
	// Error test first

	game_set_state(INIT);
	
	while (1) {
		switch (game_get_state()){
			case INIT: {
				if(DEBUG){printf("In init state \n\r");}
				//Flytte init i andre som allerede bruker de for å ikke ha så mange koblinger
				
				menu_init();
				
				game_set_state(LOBBY);
				break;
			}
			case LOBBY: {
				if(DEBUG){printf("In lobby state \n\r");}
				menu_state_controller();
				break;
			}
			case PLAY: {
				if(DEBUG){printf("In play state \n\r");}
				game_play();
				break;
			}
			case GAME_OVER:{
				if(DEBUG){printf("In game over state \n\r");}
				
				menu_print();
				game_set_state(LOBBY);
				break;
			}
		}
	}
}
