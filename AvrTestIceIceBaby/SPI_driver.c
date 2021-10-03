#include "SPI_driver.h"

void SPI_MasterInit(void){
  // Set MOSI, SS and SCK output, all others input
  DDRB = (1 << PB5) | (1 << PB4) | (1 << PB7);
  DDRB &= ~(1 << PB6); // PB6 = 0, MISO is input
  // Enable SPI, Master, set clock rate fck/16
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
  SPCR &= ~(1 << SPR1); // SPR1 = 0
}


void SPI_MasterTransmit(char cData){
  //Start transmission
  SPDR = cData; //SPI Data register
  //Wait for transmission complete
  while(!(SPSR & (1 << SPIF)){ //SPIF sets interrupt flag IF when transmission is completed
  }
}

char SPI_MasterReceive(void){
  //Send dummy byte
  SPI_MasterTransmit(0x00); //SPI Data register
  //Wait for transmission complete
  while(!(SPSR & (1 << SPIF)){ //SPIF sets interrupt flag IF when transmission is completed
  }
  return SPDR;
}

void SPI_select(void){
  //skru på ss signal
}
        
void SPI_deselect(void){
  //skru av ss signal
}
