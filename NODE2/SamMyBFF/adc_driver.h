/**
 * @file
 * @brief Driver for analog to digital conversion on NODE2
 */


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include <stdint.h>

void adc_init(void);

volatile uint32_t adc_rd(void);



#endif /* ADC_DRIVER_H_ */
