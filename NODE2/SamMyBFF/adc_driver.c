
#include "sam.h"
#include "adc_driver.h"

void adc_init(void){
	// Peripheral clock enable
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID37 ); //ADC ID = 37
	
	// Freerun mode, and sleeps between conversions. 
	ADC->ADC_MR |= (ADC_MR_FREERUN)| (ADC_MR_SLEEP); 
	
	// Enable channel
	ADC->ADC_CHER |= ADC_CHER_CH0; // Channel 0 is at A7
  }

volatile uint32_t adc_rd(void){
	// Begin analog-to-digital conversion
	ADC->ADC_CR |= ADC_CR_START; 
	// Read converted data 
	uint32_t data;
	data = ADC -> ADC_CDR[0]; // Channel 0
	return data;
}
