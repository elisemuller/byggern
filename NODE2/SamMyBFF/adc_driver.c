#include "adc_driver.h"
#include <stdint.h>
#include "sam.h"

void adc_init(void){
	// Peripheral clock enable
	// PMC->PMC_PCR |= PMC_PCR_EN | (0 << ADC_PCR_DIV_Pos) | (ID_ADC << PMC_PCR_PID_Pos); // - unødvendig?
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID37 ); //ADC ID = 37
	
	// Freerun mode, og sover mellom conversions. Kan eventuelt sette opp fast wake up? 
	ADC->ADC_MR |= (ADC_MR_FREERUN); //| (ADC_MR_SLEEP); //Bare gjetter på hva ting heter
	
	// Enable channel
	ADC->ADC_CHER |= ADC_CHER_CH0; // der x er tallet på kanalen vi vil enable
  }

volatile uint32_t adc_rd(void){
	// Begin analog-to-digital conversion
	ADC->ADC_CR |= ADC_CR_START; //(0b10); // START = 1, SWRST = 0
	// Read converted data 
	uint32_t data;
	data = ADC -> ADC_CDR[0]; // Channel 0
	return data;
}
