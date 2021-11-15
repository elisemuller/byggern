/*
 * CAN_driver.c
 *
 * Created: 04.10.2021 10:38:07
 *  Author: elisegm
 */ 

#include "CAN_driver.h"
#include "mcp2515.h"
#include "UART_driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "game_driver.h"

// Higher priority message 
volatile uint8_t READ_B0_MESSAGE = 0;

// Lower priority message
volatile uint8_t READ_B1_MESSAGE = 0;

volatile highscore record_msg; 



void CAN_init(uint8_t mode){
	mcp2515_init(); //Config mode
	CAN_interrupt_init();
	mcp2515_bit_modify(MODE_MASK, mode, MCP_CANCTRL);
}

// Gjør det noe at vi alltid sender via transmit buffer 0? Kan hende vi vil bruke en annen buffer for andre meldinger i fremtidig kode

void CAN_send_message(can_message* p_msg) {
	// Wait for transmit buffer 0 to be empty
	while(MCP_TXB0CTRL & (1 << TXREQ));
	
	// Write message ID
	uint8_t id_high = (uint8_t) ((p_msg->id & 0b11111111000) >> 3);
	uint8_t id_low = (uint8_t) ((p_msg->id & 0b111) << 5);
	
	mcp2515_bit_modify(0xE0, id_low, MCP_TXB0SIDL);
	mcp2515_write(id_high, MCP_TXB0SIDH);
	
	// Write data length
	mcp2515_bit_modify(0x0F, p_msg->length, MCP_TXB0DLC);
	
	// Write data with specified length
	for(int byte = 0; byte < p_msg->length; byte++){
		mcp2515_write(p_msg->data[byte], MCP_TXB0D0+byte);
	}
	
	// Request to send message for transmit buffer 0
	mcp2515_request_to_send(1,0,0);
	
	//printf("Transmitted message: X: %x, Y: %x , button: %x and direction : %x \r\n", p_msg->data[0], p_msg->data[1],  p_msg->data[2],  p_msg->data[3]);
	
}


// Vi har ikke lest filter and masks som spesifisert i lab lecture. 

void CAN_receive_message(can_message* p_msg) {
	if(READ_B0_MESSAGE){
		
		// Read data length
		uint8_t length = mcp2515_read(MCP_RXB0DLC);
		p_msg->length = (0b1111 & length);
	
		// Read data with specified length
		for (int byte = 0; byte < p_msg->length; byte ++){
			p_msg->data[byte] = mcp2515_read(MCP_RXB0D0+byte);
		}
		// Read message ID
		short id_high = (short) mcp2515_read(MCP_RXB0SIDH);
		short id_low = (short) (mcp2515_read(MCP_RXB0SIDL) & (0b11100000));
		
		p_msg->id = ((id_high << 3) | (id_low >> 5));
	
		// Clear receive flag for receive buffer 0. 
		READ_B0_MESSAGE = 0;
		
		//printf("Received message: X: %x, Y: %x , button: %x and direction : %x \r\n", p_msg->data[0], p_msg->data[1],  p_msg->data[2],  p_msg->data[3]);
	}
	
	else if(READ_B1_MESSAGE){
		
		// Read data length
		uint8_t length = mcp2515_read(MCP_RXB1DLC);
		p_msg->length = (0b1111 & length);
		
		// Read data with specified length
		for (int byte = 0; byte < p_msg->length; byte ++){
			p_msg->data[byte] = mcp2515_read(MCP_RXB1D0+byte);
		}
		// Read message ID
		short id_high = (short) mcp2515_read(MCP_RXB1SIDH);
		short id_low = (short) (mcp2515_read(MCP_RXB1SIDL) & (0b11100000));
		
		p_msg->id = ((id_high << 3) | (id_low >> 5));
		
		// Clear receive flag for receive buffer 1. 
		READ_B1_MESSAGE = 0;
		
		printf("Received message: %x \r\n", p_msg->data[0]);
	}
}



void CAN_interrupt_init(void){
	
	// Disable global interrupts
	cli();
	
	
	
	DDRD &= ~(1 << PD2);
	
	// Interrupt at falling edge of INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	// Define INT0 as interrupt input
	GICR |= (1 << INT0);
	
	// Enable interrupts on MCP for when messages are received in the receive buffers
	mcp2515_bit_modify(0b00000011, 0xFF, MCP_CANINTE);

	// Enable global interrupts
	sei();
}

ISR(INT0_vect){
	uint8_t interrupt_flag = mcp2515_read(MCP_CANINTF);
	//printf("Received message\n\r");
	if (interrupt_flag & 0x01){
		// Set receive flag for receive buffer 0
		READ_B0_MESSAGE = 1;
		
		// Clear interrupt flag to allow new message reception
		mcp2515_bit_modify(0x01, 0x00, MCP_CANINTF);
	}
	if (interrupt_flag & 0x02){
		// Set receive flag for receive buffer 1
		READ_B1_MESSAGE = 1;
		
		// Clear interrupt flag to allow new message reception
		mcp2515_bit_modify(0x02, 0x00, MCP_CANINTF);
	}

	CAN_message_handler();
}



void CAN_message_handler(void){
	can_message msg; 
	if (READ_B0_MESSAGE || READ_B1_MESSAGE ){
		
		CAN_receive_message(&msg);
	}
	switch (msg.id){
		case CAN_GAME_END_ID: {
			printf("END GAME MESSAGE RECEIVED\n\r");
			if (record_msg.last_playtime < msg.data[0]){
				record_msg.best_highscore = msg.data[0];
			}
			record_msg.last_playtime = msg.data[1];
			game_set_state(GAME_OVER);
			game_interrupt_disable();
		}
	}
}


highscore CAN_get_highscore(void){
	return record_msg;
}