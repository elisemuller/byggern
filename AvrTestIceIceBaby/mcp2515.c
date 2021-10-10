#define F_CPU 4915200

#include "mcp2515.h"
#include <stdio.h>
#include <avr/io.h>
#include "SPI_driver.h"
#include <util/delay.h>
#include <stdlib.h>



uint8_t mcp2515_init(void){
  uint8_t value; 
  
  SPI_init();
  mcp2515_reset();

  value = mcp2515_read(MCP_CANSTAT);
  if ((value & MODE_MASK) != MODE_CONFIG){
    printf("MCP2515 is NOT in configuration mode after reset: %x\r\n", value);
    return 1;        
  }
  printf("MCP2515 is in configuration mode after reset!\r\n");

  // Set CAN bitrate
  // CNF1/2/3
  
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
