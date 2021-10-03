/**
 * @file xmem.h
 * @brief memory driver
 
 * @date 06.09.2021 08:56:06
 * @author elisegm
 */ 


#ifndef XMEM_H_
#define XMEM_H_


/**
* @brief Initializes external memory
* @param void
* @return void                                                                     
*/
void xmem_init(void);


/**
* @brief Configures whether portA on mcu will receive or send
* @param uint8_t mcu_in
* @return void
*/
void mcu_porta_io_config(uint8_t mcu_in);


/**
* @brief Writes @p data to offset address
* @param uint16_t @p offset Offset from base address
* @param uint8_t @p data Data to be written to offset address
* @return void
*/
void xmem_write(uint8_t data, uint16_t offset);

uint8_t xmem_read(uint16_t offset);



#endif /* XMEM_H_ */
