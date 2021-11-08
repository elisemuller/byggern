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
	//motor_reset_encoder(1);
	
	SysTick_Config(84);

	//REG_PWM_CDTYUPD5 = (int)( ( (1.5 - 0.6 * (100-50) / 50) / 20 ) * 40000 );
	//REG_PWM_CDTYUPD6 = (int)( ( (1.5 - 0.6 * (0-50) / 50) / 20 ) * 40000 );
	
    while (1) 
    {
		
		//blink();
		//CAN_MESSAGE end_game_msg;
		//end_game_msg.id = CAN_GAME_END_ID;
		//end_game_msg.data_length = 2;
		//end_game_msg.data[0] = 1;
		//end_game_msg.data[1] = 2;
		//can_send(&end_game_msg, 0);	// Mailbox 0?
		game_play();
		
		//PWM->PWM_CH_NUM[6].PWM_CDTYUPD = (int)( ( (1.5 - 0.6 * (100-50) / 50) / 20 ) * 40000 );
		
		//game_joystick_controller();

    }
}
