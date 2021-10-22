#include "adc_driver.h"
#include "sam.h"

void adc_init(void){
	// Disable PIO, select peripheral
	PIOC->PIO_PDR |= PIO_PDR_P19;// | PIO_PDR_P18;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;// | PIO_ABSR_P18;
	
	// Peripheral clock enable
	// PMC->PMC_PCR |= PMC_PCR_EN | (0 << ADC_PCR_DIV_Pos) | (ID_ADC << PMC_PCR_PID_Pos); // - unødvendig?
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID37 ); //ADC ID = 37
  }
