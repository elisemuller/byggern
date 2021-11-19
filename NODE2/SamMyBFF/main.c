/*
 * SamMyBFF.c
 *
 * Created: 11.10.2021 13:53:47
 * Author : elisegm
 */ 

#include <stdio.h>
#include <unistd.h>

#include "sam.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "game_driver.h"
#include "buzzer_driver.h"
#include "melodies.h"

#define DEBUG 0


int main(void)
{   	
    while (1) 
    {		
		switch (game_get_state()){
			case INIT: {
				SystemInit();
				configure_uart();
				can_init_def_tx_rx_mb();
				SysTick_Config(84);
				game_init();
				NVIC_EnableIRQ(TC0_IRQn);
				game_set_state(LOBBY);
				printf("######################### INIT COMPLETE ############################\n\r");
				break;
			}
			case LOBBY: {
				if(DEBUG){printf("In lobby state \n\r");}
				buzzer_play_playlist(LOBBY_MUSIC);
				break;
			}
			case PLAY: {
				if(DEBUG){printf("In play state \n\r");}
				game_play();
				break;
			}
			case GAME_OVER:{
				if(DEBUG){printf("In game over state \n\r");}
				game_ended();
				game_set_state(LOBBY);
				buzzer_play_playlist(LOSING_MUSIC);
				break;
			}
			case BIRTHDAY:{
				if(DEBUG){printf("In birthday state \n\r");}
				game_set_state(LOBBY);
				buzzer_play_playlist(BIRTHDAY_MUSIC);
				break; 
			}
			case VICTORY:{
				if(DEBUG){printf("In victory state \n\r");}
				game_ended();
				game_set_state(LOBBY);
				buzzer_play_playlist(WINNING_MUSIC);
				break;
			}
			
		}
		
    }
			
}
