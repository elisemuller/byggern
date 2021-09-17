/**
 * @file xmem.h
 * @brief memory driver
 
 * @date 06.09.2021 08:56:06
 * @author elisegm
 */ 


#ifndef XMEM_H_
#define XMEM_H_


/**
* @brief initializes external memory
* @param void
* @return void                                                                     
*/
void xmem_init(void);


/**
* @brief configures whether portA on mcu will receive or send
* @param uint8_t mcu_in
* @return void
*/
void mcu_porta_io_config(uint8_t mcu_in);

// void xmem_write(uint8_t data, uint16_t offset); forslag - definer base_address i ext_mem.c

void xmem_write(uint8_t data, uint16_t address, uint16_t base);

uint8_t xmem_read(uint16_t address, uint16_t base);



#endif /* XMEM_H_ */
