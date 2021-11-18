/*
 * uart.h
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 * A simple interface for receiving and transmitting characters to a computer using UART via the on board USB-connector
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#define UART_RINGBUFFER_SIZE 64
/*
 * Ringbuffer for receiving characters from  
 */
typedef struct uart_ringbuffer_t
{
	uint8_t head, tail;
	char data[UART_RINGBUFFER_SIZE];
} uart_ringbuffer;

/**
 * @brief Configure UART.
 */
void configure_uart(void);

/**
 * @brief Get character from UART
 *
 * @param c location of character
 *
 * @retval Success(0) or failure(1)
 */
int uart_getchar(uint8_t *c);

/**
 * @brief Sends a character through the UART interface
 *
 * @param c Character to be sent
 *
 * @retval Success(0) or failure(1).
 */
int uart_putchar(const uint8_t c);

void UART_Handler       ( void );



#endif /* UART_H_ */