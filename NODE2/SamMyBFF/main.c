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

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	led_enable();
	can_init_def_tx_rx_mb();
    /* Replace with your application code */
    while (1) 
    {

		
    }
}
