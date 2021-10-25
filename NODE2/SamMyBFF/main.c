/*
 * SamMyBFF.c
 *
 * Created: 11.10.2021 13:53:47
 * Author : elisegm
 */ 


#include "sam.h"
#include <stdio.h>
#include <unistd.h>
//#include "delay.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "blink.h"
#include "can_controller.h"
#include "can_interrupt.h"
#include "servo_driver.h"
#include "test_driver.h"

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	led_enable();
	can_init_def_tx_rx_mb();
	servo_pwm_init();
	printf("NODE 2 STARTING UP");
	//blink();
	//servo_dutycycle_modify_x(-100);
	//test_adc_read();
	
    //while (1) 
    //{
		////move_PWM();		
    //}
}
