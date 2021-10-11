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

volatile uint8_t READ_B0_MESSAGE = 0;
volatile uint8_t READ_B1_MESSAGE = 0;



void CAN_init(uint8_t mode){
	mcp2515_init(); //Config mode
	CAN_interrupt_init();
	mcp2515_bit_modify(MODE_MASK, mode, MCP_CANCTRL);
}

void CAN_send_message(can_message* p_msg) {
	// wait for transmit buffers to be empty
	while(MCP_TXB0CTRL & (1 << TXREQ));
	
	// write id
	uint8_t id_high = (uint8_t) ((p_msg->id & 0b11111111000) >> 3);
	uint8_t id_low = (uint8_t) ((p_msg->id & 0b111) << 5);
	
	mcp2515_bit_modify(0xE0, id_low, MCP_TXB0SIDL);
	mcp2515_write(id_high, MCP_TXB0SIDH);
	
	// write length
	mcp2515_bit_modify(0x0F, p_msg->length, MCP_TXB0DLC);
	
	// write data
	for(int byte = 0; byte < p_msg->length; byte++){
		mcp2515_write(p_msg->data[byte], MCP_TXB0D0+byte);
	}
	
	mcp2515_request_to_send(1,0,0);
	
	printf("Transmitted data: %x \r\n", p_msg->data[0]);
	
}

void CAN_receive_message(can_message* p_msg) {
	if(READ_B0_MESSAGE){
		// read length
		uint8_t length = mcp2515_read(MCP_RXB0DLC);
		p_msg->length = (0b1111 & length);
	
		// read data
		for (int byte = 0; byte < p_msg->length; byte ++){
			p_msg->data[byte] = mcp2515_read(MCP_RXB0D0+byte);
		}
		// read id
		short id_high = (short) mcp2515_read(MCP_RXB0SIDH);
		short id_low = (short) (mcp2515_read(MCP_RXB0SIDL) & (0b11100000));
		
		p_msg->id = ((id_high << 3) | (id_low >> 5));
	
		//check receive interrupt -> clear when set
		READ_B0_MESSAGE = 0;
		
		printf("Received message: %x \r\n", p_msg->data[0]);
	}
	
	else if(READ_B1_MESSAGE){
		// les ut RXBnDLC bit 0-3. sett disse lik msg.length
		uint8_t length = mcp2515_read(MCP_RXB1DLC);
		p_msg->length = (0b1111 & length);
		
		// les ut RXBnDm, alle bits. = msg.data
		for (int byte = 0; byte < p_msg->length; byte ++){
			p_msg->data[byte] = mcp2515_read(MCP_RXB1D0+byte);
		}
		// les ut id
		short id_high = (short) mcp2515_read(MCP_RXB1SIDH);
		short id_low = (short) (mcp2515_read(MCP_RXB1SIDL) & (0b11100000));
		
		p_msg->id = ((id_high << 3) | (id_low >> 5));
		
		//check receive interrupt -> clear when set
		READ_B1_MESSAGE = 0;
		
		printf("Received message: %x \r\n", p_msg->data[0]);
	}
}

//void CAN_communication(void){
	////sjekker for interrupts
//}

void CAN_interrupt_init(void){
	// Disable global interrupts
	cli();
	
	// Enable desired interrupts on MCP
	mcp2515_bit_modify(0b00000011, 0xFF, MCP_CANINTE);
	
	DDRD &= ~(1 << PD2);
	
	
	// Interrupt at falling edge of INT0
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);

	// Define INT0 as interrupt input
	GICR |= (1 << INT0);
	
	// Enable global interrupts
	sei();
}

ISR(INT0_vect){
	uint8_t interrupt_flag = mcp2515_read(MCP_CANINTF);
	//printf("Interrupt flag: %d \r\n", interrupt_flag);
	if (interrupt_flag & 0x01){
		READ_B0_MESSAGE = 1;
		mcp2515_bit_modify(0x01, 0x00, MCP_CANINTF);
	}
	if (interrupt_flag & 0x02){
		READ_B1_MESSAGE = 1;
		mcp2515_bit_modify(0x02, 0x00, MCP_CANINTF);
	}
	
}