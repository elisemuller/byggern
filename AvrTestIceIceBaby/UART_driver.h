#ifndef UART_driver_h
#define UART_driver_h

#define FOSC 4915200		// Clock speed (crystal oscillator)
#define BAUD 9600			// Baud rate

#define MYUBRR FOSC/16/BAUD-1

/**
* @brief initialize UART
* @param unsigned int UBRR
* @return void
*/
void uart_init(unsigned int ubrr);

/**
* @brief transmit char with UART
* @param unsigned char message
* @return void
*/
void uart_transmit(unsigned char message);

/**
* @brief receive char with UART
* @param void
* @return unsigned char received
*/
unsigned char uart_receive(void);

#endif

