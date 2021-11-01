/*
 * test_driver.c
 *
 * Created: 25.10.2021 12:33:48
 *  Author: elisegm
 */ 

#include "uart.h"
#include "printf-stdarg.h"
#include "test_driver.h"
#include "sam.h"
#include "adc_driver.h"
#include <stdint.h>

void test_adc_read(void){
	while (1)
	{
		uint32_t data = adc_rd();
		printf("ADC data from IR score system: %d \r\n", data);
	}
}


