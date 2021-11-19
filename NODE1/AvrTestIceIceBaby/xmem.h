/**
 * @file
 * @brief Memory driver
 */


#ifndef XMEM_H_
#define XMEM_H_


/**
* @brief Initializes external memory
*/
void xmem_init(void);

/**
* @brief Writes @p data to @p offset address
* @param offset from base address
* @param data to be written to @p offset address
*/
void xmem_write(uint8_t data, uint16_t offset);

/**
* @brief Reads data from @p offset address
* @param offset from base address
* @return Data located at @p offset address
*/
uint8_t xmem_read(uint16_t offset);



#endif /* XMEM_H_ */
