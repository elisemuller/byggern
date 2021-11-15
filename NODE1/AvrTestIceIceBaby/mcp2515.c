
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "mcp2515.h"
#include "SPI_driver.h"



#define F_CPU 4915200
#define F_OSC 16000000
#define BAUD 125000
#define TQ_NUM 16
#define PS1 6
#define PS2 5
#define BRP (F_OSC/(2*BAUD*TQ_NUM))-1


// Define timing config values

// Enable CLKOUT pin for SOF signal, enable wakeup filter, PS2
#define CNF3_REG_VALUE ( SOF_ENABLE | PS2 )

// Set bit 7 to 1 = BTLMODE. Sample 3x = SAMPLE_3X, PS1 on pos 3 and 0
#define CNF2_REG_VALUE ( BTLMODE | SAMPLE_1X | (PS1 << 3) | (1 << 0) )

// Two top bits are 11 (4 x TQ). Bottom bits are BRP.
#define CNF1_REG_VALUE ( SJW4 | BRP )										




uint8_t mcp2515_init(void){
	uint8_t value; 
	SPI_init();
	mcp2515_reset();
 
	//Self-test (Should be implemented in all drivers)
	value = mcp2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset: %x\r\n", value);
		return 1;        
	}
	
	// Bit timing configuration
	mcp2515_bit_modify(0xC7, CNF3_REG_VALUE, MCP_CNF3); // Modify CNF3, bits 7, 6, 2-0. 
	mcp2515_bit_modify(0xFF, CNF2_REG_VALUE, MCP_CNF2); // Modify CNF2.
	mcp2515_bit_modify(0xFF, CNF1_REG_VALUE, MCP_CNF1); // Modify CNF1.
	
	return 0; 
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result; 
  
	SPI_select();// Select CAN-controller
	SPI_send(MCP_READ); //Send read instruction
	SPI_send(address); //Send address
	result = SPI_read();
  
	SPI_deselect(); // Deselect CAN-controller
  
	return result; 
}

void mcp2515_write(uint8_t data, uint8_t address){
	SPI_select();
	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);
	SPI_deselect();
}

void mcp2515_request_to_send(int buff_tx0, int buff_tx1, int buff_tx2){
	SPI_select();
	if(buff_tx0){
		SPI_send(MCP_RTS_TX0);
	}
	if(buff_tx1){
		SPI_send(MCP_RTS_TX1);
	}
	if(buff_tx2){
		SPI_send(MCP_RTS_TX2);
	}
	SPI_deselect();
}

void mcp2515_bit_modify(uint8_t mask_byte, uint8_t data_byte, uint8_t address){
	SPI_select();
	SPI_send(MCP_BITMOD);
	SPI_send(address);
	SPI_send(mask_byte);
	SPI_send(data_byte);
	SPI_deselect();
}

void mcp2515_reset(void){
	SPI_select();
	SPI_send(MCP_RESET);
	SPI_deselect();
	
}

char mcp2515_read_status(void){
	char status = 0; 
	SPI_select();
	SPI_send(MCP_READ_STATUS);
	status = SPI_read();
	SPI_deselect();
	return status;
}
