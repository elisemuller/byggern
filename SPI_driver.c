#include "SPI_driver.h"
#include <avr/io.h>


#define CAN_CS PB4
#define SPI_PORT PORTB

void SPI_init(void){
  // Set MOSI, SS and SCK output, all others input
  DDRB |= (1 << PB5) | (1 << CAN_CS) | (1 << PB7);
  DDRB &= ~(1 << PB6); // PB6 = 0, MISO is input
	
  // Enable SPI, Master, set clock rate fck/16
  SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
  SPCR &= ~(1 << SPR1); // SPR1 = 0 (clk rate)
  
  // SPI Mode = 0 -> Leading edge: sample, Trailing edge: setup
  SPCR &= ~(1 << CPOL); // CPOL = 0
  SPCR &= ~(1 << CPHA); // CPHA = 0
}


void SPI_send(char cData){
  //Start transmission
  SPDR = cData; //SPI Data register
  //Wait for transmission complete
  while(!(SPSR & (1 << SPIF))){} //SPIF sets interrupt flag IF when transmission is completed
}

char SPI_read(void){
	//Send dummy byte
	SPDR = 0xFF; //SPI Data register
  
	//Wait for transmission complete
	while(!(SPSR & (1 << SPIF))){} //SPIF sets interrupt flag IF when transmission is completed
		
	return SPDR;
}

void SPI_select(void){
  SPI_PORT &= ~(1 << CAN_CS);
}
 
        
void SPI_deselect(void){
  SPI_PORT |= (1 << CAN_CS);
}
