#include "servo_driver.h"
#include "sam.h"
#include "PWM_driver.h"

#include <stdint.h>

#include "can_interrupt.h"

#define MCK 84000000
#define DIV 42

volatile int last_pwm = (1.5/20);

void PWM_init(void){
	// Disable PIO, select peripheral for pin 44 and pin 45
	PIOC->PIO_PDR |= PIO_PDR_P19;// | PIO_PDR_P18;
	PIOC->PIO_ABSR |= PIO_ABSR_P19;// | PIO_ABSR_P18;
	
	// Peripheral clock enable
	PMC->PMC_PCR |= PMC_PCR_EN | (0 << PMC_PCR_DIV_Pos) | (ID_PWM << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= ( PMC_PCER1_PID36 );
	
	// PWM clock. Velger 84 MHz / 42 = 2 MHz
	// PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);
	PWM->PWM_CLK = PWM_CLK_PREB(0) | PWM_CLK_DIVB(DIV);
	
	// Channel mode. High polarity. Left aligned.
	// REG_PWM_CMR6 = PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;
	REG_PWM_CMR5 = PWM_CMR_CPRE_CLKB | PWM_CMR_CPOL;
	
	// Channel period = T * MCK / X = 0,020*84000000/42=40000
	// REG_PWM_CPRD6 = 40000;
	REG_PWM_CPRD5 = 40000;
	
	// Duty cycle: (1.5 ms / 20 ms) * 40000 = 3000 -> ca midt p� [0.9 , 2.1]
	// REG_PWM_CDTY6 = 3000;
	REG_PWM_CDTY5 = 3000;
	
	// Enable PWM channels
	PWM->PWM_ENA |= (PWM_ENA_CHID5); // | (PWM_ENA_CHID6);
}

void PWM_dutycycle_modify(int debug){
    //switch (channel) {
        //case SERVO_CHANNEL:{
            // if j_x is represented by a negative number in two's complement: 
            // --> Convert to negative number between -100 and 0. 
		input_s slider = can_get_slider_input();
		int s_r = slider.pos_r_slider;
		
		if(debug){printf("right_slider = %d\r\n", s_r);}

        if((s_r <= 100) && (s_r >= 0)){
			
			REG_PWM_CDTYUPD5 = (int)( ( (1.5 - 0.6 * (s_r-50) / 50) / 20 ) * 40000 );
	    }

            //break;
        //}
        //case BUZZER_CHANNEL: {
            //REG_PWM_CDTYUPD6 = (int) (40000 * vol);
			//break;
        //}
        //default:{
	        //printf("Channel selected is not valid. \r\n");
	        //break;
        //}
    //}

}

void PWM_frequency_modify(int freq){
	if (freq == 0){
		REG_PWM_CPRD6 = 0; 
	}
	else{
		REG_PWM_CPRD6 = (int)(MCK/(DIV*freq));
	}
}