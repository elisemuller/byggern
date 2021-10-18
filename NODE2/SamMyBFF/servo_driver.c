#include "servo_driver.h"
#include "sam.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void servo_pwm_init(void){
	// Disable PIO, select peripheral
	PIOC->PIO_PDR |= PIO_PDR_P19;// | PIO_PDR_P18;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;// | PIO_ABSR_P18;
	
	// Peripheral clock enable
	PMC->PMC_PCR |= PMC_PCR_EN | (0 << PMC_PCR_DIV_Pos) | (ID_PWM << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID36 );
	
	// PWM clock. Velger 84 MHz / 42 = 2 MHz
	// PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);
	PWM->PWM_CLK = PWM_CLK_PREB(0) | PWM_CLK_DIVB(42);
	
	// Channel mode. High polarity. Left aligned.
	// REG_PWM_CMR6 = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;
	REG_PWM_CMR5 = PWM_CMR_CPRE_CLKB | PWM_CMR_CPOL;
	
	// Channel period = T * MCK / X = 0,020*84000000/42=40000
	// REG_PWM_CPRD6 = 40000;
	REG_PWM_CPRD5 = 40000;
	
	// Duty cycle: (1.5 ms / 20 ms) * 40000 = 3000 -> ca midt på [0.9 , 2.1]
	// REG_PWM_CDTY6 = 3000;
	REG_PWM_CDTY5 = 3000;
	
	// Enable PWM channels
	PWM->PWM_ENA |= (PWM_ENA_CHID5); // | (PWM_ENA_CHID6);
}

void servo_dutycycle_modify_x(int x){
	// max - min = 2.1 - 0.9 = 1.2
	// coeff = 1.2 / 2 = 0.6
	// mid = 0.9 + 0.6 = 1.5
	// signal width = 1.5 + 0.6 * pos/100
	// dutycycle = signal width / 20ms * 40000
	if((x <= 100) | (x >= -100)){
		REG_PWM_CDTYUPD5 = ( ( (1.5 + 0.6 * x / 100) / 20 ) * 40000 );
		//REG_PWM_CDTY5 = ( ( (1.5 + 0.6 * x / 100) / 20 ) * 40000 );
	}
}