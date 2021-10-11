#include <avr/io.h>
#include <stdio.h>
#include "UART_driver.h"

// Kode er hentet fra datablad til ATMega162

// Here, using USART0-registers

void uart_init(unsigned int ubrr){
	// Baud rate
	UBRR0H = (unsigned char) (ubrr >> 8);	// Baud rate high register
	UBRR0L = (unsigned char) (ubrr);		// Baud rate low register
	// Enable receivers and transmitter on usart 0
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Data format (char = 8 bit, + 2 stop bit)
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
	fdevopen(uart_transmit,uart_receive);
}

void uart_transmit(unsigned char message){
	while ( !(UCSR0A & (1 << UDRE0)) ); // Wait until last message has been sent and transmit buffer is empty.
	UDR0 = message;						// Put data in buffer
}

unsigned char uart_receive(void){
	while ( !(UCSR0A & (1 << RXC0)) );	// Wait until last message has been received
	
	UCSR0A |= (1 << RXC0);
	return UDR0;					// Put data in buffer
}

//printf * fdevopen(uart_transmit, uart_receive);

//void printf(){
	//fdevopen(uart_transmit, uart_receive);
//}