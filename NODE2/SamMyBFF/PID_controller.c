/*
 * PID.c
 *
 * Created: 08.11.2021 14:29:56
 *  Author: emiliamo
 */ 


#include "PID_controller.h"
#include "sam.h"
#include "stdlib.h"
#include "motor_driver.h"

#define MCK 84000000

volatile int Kp;
volatile int Ki; 
volatile int Kd;


// Vi må finne rangen til encoderen 
// --> Gjøres ved å kjøre encoderen helt til høyre, lese ut verdi, og så samme for venstre. 
// --> Lurt å regne ut midtverdi sånn ca. 
// Dette kalibreres da ut ifra joysticken, som vi sier gir ut -100 til 100. Altså vil vi kanskje kunne lese ut encoder, se om vi ligger høyre eller venstre og sette encoder utifra dette? 


void PID_controller(uint16_t ref_pos, uint16_t curr_pos){
    uint16_t error = ref_pos - curr_pos;

}

// Timer counter channel 0 slik at vi kan ha fastbestemt T

void PID_init(void){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27; // ID TC0

    // Timer clock = MCK/128 , RC Compare resets the counter and starts the counter clock
    TC0->TC_CHANNEL[0].TC_CMR |= (TIMER_CLOCK4 | CPCTRG);

    // Enables interrupt when RC = TC_CV (Current val in counter)
    TC0->TC_CHANNEL[0].TC_IER |= TC_IER_CPCS;

    TC0->TC_CHANNEL[0].TC_RC = 65625; // MCK/128/TC_RC = 10 - dette skal liksom gi ms? (ifølge insp, men vil få matten til å gi mening selv)

    // Enables the timer clock
    TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN; //Se om det finnes annen syntaks på dette
    TC0->TC_CHANNEL[0].TC_CCR &= ~(TC_CCR_CLKDIS);

}
