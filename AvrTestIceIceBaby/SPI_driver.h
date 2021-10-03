/*
 * SPI.h
 *
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

void SPI_init(void);

//Henter fra Atmega s.160
void SPI_MasterInit(void);
void SPI_send(char cData);

//To read something from the slave the master must transmit a dummy byte
char SPI_read(void);

/**
* @brief Selects CAN-controller
* @param void
* @return void                                                                     
*/
void SPI_select(void);

/**
* @brief Deselects CAN-controller
* @param void
* @return void                                                                     
*/
void SPI_deselect(void);

#endif /* SPI_DRIVER_H_ */
