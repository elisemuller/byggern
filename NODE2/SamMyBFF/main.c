/*
 * SamMyBFF.c
 *
 * Created: 11.10.2021 13:53:47
 * Author : elisegm
 */ 


#include "sam.h"
#include <stdio.h>
#include <unistd.h>
#include "time.h"

#include "blink.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "PWM_driver.h"
#include "test_driver.h"
#include "adc_driver.h"
#include "motor_driver.h"
#include "game_driver.h"
#include "buzzer_driver.h"
#include "PID_controller.h"
#include "melodies.h"

#define DEBUG 0


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	led_enable();
	can_init_def_tx_rx_mb();
	PWM_init();
	printf("NODE 2 STARTING UP\n\r");
	adc_init();
	motor_init();
	solenoid_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	//printf("Hello\r\n");
	//printf("Goodbye muddafucca\r\n");
	
	//blink();
	//servo_dutycycle_modify_x(-100);
	//test_adc_read();
	//
	//time_t start_time = time(NULL);
	//time_t now_time = time(NULL);
	//
	input_j joystick;
	int highscore; 
	PID_init();
	
	
	SysTick_Config(84);
	
	motor_reset_encoder();
	
	printf("#####################################################\n\r");

	//REG_PWM_CDTYUPD5 = (int)( ( (1.5 - 0.6 * (100-50) / 50) / 20 ) * 40000 );
	//REG_PWM_CDTYUPD6 = (int)( ( (1.5 - 0.6 * (0-50) / 50) / 20 ) * 40000 );
	//motor_reset_encoder();
	//motor_calibrate_encoder();
	//time_delay_ms(10000);
	//time_delay_us(10000000);
//
	NVIC_EnableIRQ(TC0_IRQn);


    while (1) 
    {
		switch (game_get_state()){
			case INIT: {
				if(DEBUG){printf("In init state \n\r");}
		
				game_set_state(LOBBY);
				break;
			}
			case LOBBY: {
				if(DEBUG){printf("In lobby state \n\r");}
				//buzzer_adjust_volume(10);
				//buzzer_play_music(HAPPY_BIRTHDAY);
				//buzzer_play_note(NOTE_B7,1000);
				//buzzer_play_note(NOTE_D8,3000);
				//buzzer_play_note(NOTE_CS2,2000);
				//PID_timer_test();
				//motor_reset_encoder();
				
				//motor_read_encoder();
				//play music
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
				break;
			}
			
		}
		
		
		//PID_timer_test();
		
		//blink();
		//CAN_MESSAGE end_game_msg;
		//end_game_msg.id = CAN_GAME_END_ID;
		//end_game_msg.data_length = 2;
		//end_game_msg.data[0] = 1;
		//end_game_msg.data[1] = 2;
		//can_send(&end_game_msg, 0);	// Mailbox 0?
			
		//PWM->PWM_CH_NUM[6].PWM_CDTYUPD = (int)( ( (1.5 - 0.6 * (100-50) / 50) / 20 ) * 40000 );
		
		//game_joystick_controller();

    }
			
}
