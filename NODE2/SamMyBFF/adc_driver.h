/**
 * @file
 * @brief Driver for analog to digital conversion on NODE2
 */


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include <stdint.h>


/**
* @brief Initializes adc. Enables the peripheral clock and channel 0. 
**/

void adc_init(void);


/**
 * @brief Converts and read the data on the selected @p channel
 * @param channel The channel selected for adc conversion
 * @return The converted data 
 */
volatile uint32_t adc_rd(void);



#endif /* ADC_DRIVER_H_ */
