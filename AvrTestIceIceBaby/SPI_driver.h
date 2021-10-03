/*
 * SPI.h
 *
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

void SPI_init(void);

//Henter fra Atmega s.160
void SPI_MasterInit(void);

//To read something from the slave the master must transmit a dummy byte
uint8_t SPI_read(void);

void SPI_send(uint8_t);

#endif /* SPI_DRIVER_H_ */
