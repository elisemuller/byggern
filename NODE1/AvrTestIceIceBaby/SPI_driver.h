/*
 * SPI.h
 *
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

/**
* @brief Initializes the SPI. Followed the init procedure from the Atmega162 datasheet, page 160. 
* @param void
* @return void                                                                     
*/
void SPI_init(void);

/**
* @brief Transmits @p cData to the SPI data register.
* @param cData The data to be transmitted
* @return void                                                                     
*/
void SPI_send(char cData);

/**
* @brief Reads data from the SPI data register. 
* @param void
* @return char The contents of the SPI data register                                                                     
*/
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
