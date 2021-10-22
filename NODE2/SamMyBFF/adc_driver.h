/*
 * adc_driver.h
 *
 * Created: 18.10.2021 12:27:14
 *  Author: elisegm
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_


void adc_init(void);

volatile uint32_t adc_rd(void);



#endif /* ADC_DRIVER_H_ */
