/*
 * NODE1.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 


#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"
#include "xmem.h"
#include "movement_driver.h"
#include "menu.h"
#include "CAN_driver.h"
#include "game_driver.h"


#define DEBUG 0


int main(void)
{
	game_set_state(INIT);
	
	while (1) {
		switch (game_get_state()){
			case INIT: {
				uart_init( MYUBRR );
				xmem_init();
				mov_init();
				CAN_init();
				menu_init();
				game_set_state(LOBBY);
				
				printf("######## INIT COMPLETE ########\n\r");
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
