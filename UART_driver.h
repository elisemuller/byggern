#ifndef UART_driver_h
#define UART_driver_h

#define FOSC 4915200		// Clock speed (crystal oscillator)
#define BAUD 9600			// Baud rate

#define MYUBRR FOSC/16/BAUD-1

void uart_init(unsigned int ubrr);

void uart_transmit(unsigned char message);

unsigned char uart_receive();

#endif

