#include "mcp2515.h"
#include "SPI.h"

uint8_t mcp2515_init(void){
  uint8_t value; 
  
  SPI_init();
  mcp2515_reset();
  
  //Self-test (Should be implemented in all drivers)
  mcp2515_read(MCP_CANSTAT, &value);
  if ((value & MODE_MASK) != MODE_CONFIG){
    printf("MCP2515 is NOT in configuration mode after reset!\r\n");
    return 1;        
  }
  
  //More initialization
  
  return 0; 
}

uint8_t mcp2515_read(uint8_t address){
  uint8_t result; 
  
  PORTB &= ~(1 << CAN_CS); // Select CAN-controller
  SPI_write(MCP_READ); //Send read instruction
  SPI_write(address); //Send address
  result = SPI_read();
  
  PORTB |= (1 << CAN_CS); // Deselect CAN-controller
  
  return result; 
}
