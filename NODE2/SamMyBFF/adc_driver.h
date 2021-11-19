/**
 * @file
 * @brief Driver for analog to digital conversion on NODE2
 */


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_


/**
* @brief Initializes adc. Enables channel 0
**/

void adc_init(void);


/**
 * @brief Converts and reads the data on channel 0
 * @return The converted data 
 */
volatile uint32_t adc_rd(void);



#endif /* ADC_DRIVER_H_ */
