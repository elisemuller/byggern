/*
 * AvrTestIceIceBaby.c
 *
 * Created: 30.08.2021 10:20:55
 * Author : elisegm
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "UART_driver.h"

int main(void)
{
    /* Replace with your application code */
	uart_init( MYUBRR );
	
	fdevopen(uart_transmit,uart_receive);
	
	int a = 0;
	
	while(a < 10)
	{
		uart_transmit('a');
		a++;
	}
	while(1)
	{	
		//unsigned char msg = uart_receive();
		//uart_transmit(msg);

		printf("hallo");
		
		
	}
	
}



/*
DDRA = 0x1;

PORTA = 0x1;

while (1)
{
	PORTA &= (0x00);
	
	PORTA |= (0xFF);
}*/