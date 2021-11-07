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
	//printf("NODE 2 STARTING UP");
	adc_init();
	motor_init();
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
	//motor_reset_encoder();
	
    while (1) 
    {
		
		game_play();
		
		//motor_read_encoder();


    }
}
