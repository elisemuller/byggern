#include "adc_driver.h"
#include "sam.h"

void adc_init(void){
	// Disable PIO, select peripheral
	PIOC->PIO_PDR |= PIO_PDR_P18;// Velge riktig pin her
	PIOC->PIO_ABSR |= PIO_ABSR_P18;// 
	
	// Peripheral clock enable
	// PMC->PMC_PCR |= PMC_PCR_EN | (0 << ADC_PCR_DIV_Pos) | (ID_ADC << PMC_PCR_PID_Pos); // - unødvendig?
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID37 ); //ADC ID = 37
	
	// Enable channel
	// ADC_CHER |= (1 << CHx);, der x er tallet på kanalen vi vil enable
	
	// Freerun mode, og sover mellom conversions. Kan eventuelt sette opp fast wake up? 
	// ADC_MR |= (1 << ADC_MR_FREERUN) | (1 << ADC_MR_SLEEP); 
  }

volatile uint8_t adc_rd(uint8_t channel){
	//Begin analog-to-digital conversion
	ADC_CR = (0b10); // START = 1, SWRST = 0
	uint8_t data;
	// data = ADC_CDRx; // x = valgt kanal
	
}
