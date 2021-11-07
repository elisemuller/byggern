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
	motor_power(1);
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
	//motor_reset_encoder();
	
    while (1) 
    {
		blink();

		//joystick = can_get_joy_input();
		//int j_y = joystick.pos_y;
		//PWM_dutycycle_modify(j_y,0);
		//game_joystick_controller();
		//motor_read_encoder();
		//printf("Joystick x pos: %d\r\n", joystick.pos_x);
		//game_joystick_controller();
		
		//motor_set_direction(LEFT);
		//motor_set_speed(2000);

		//now_time = time(NULL);
		//printf("Time: %d\r\n", now_time);
    }
}
