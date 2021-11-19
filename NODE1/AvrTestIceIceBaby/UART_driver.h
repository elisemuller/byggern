/**
 * @file
 * @brief Configuration of UART communication
 */

#ifndef UART_driver_h
#define UART_driver_h

#define FOSC 4915200		// Clock speed (crystal oscillator)
#define BAUD 9600			// Baud rate

#define MYUBRR FOSC/16/BAUD-1

/**
* @brief Initializes UART
* @param UBRR Baud rate
*/
void uart_init(unsigned int UBRR);

/**
* @brief Transmits @p message with UART
* @param message Message to be transmitted
*/
void uart_transmit(unsigned char message);

/**
* @brief Receives message with UART
* @return Message received
*/
unsigned char uart_receive(void);

#endif

