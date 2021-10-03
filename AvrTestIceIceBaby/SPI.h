/*
 * SPI.h
 *
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);

//To read something from the slave the master must transmit a dummy byte
uint8_t SPI_read(void);

void SPI_send(uint8_t);

#endif /* SPI_H_ */
