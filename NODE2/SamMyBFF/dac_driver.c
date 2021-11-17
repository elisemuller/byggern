
#include "sam.h"
#include "dac_driver.h"

void dac_init(void) {
    // free running mode word transfer, does not sleep between conversions, channel 1 selected + startup time??
    DACC->DACC_MR |= DACC_MR_WORD_WORD | DACC_MR_USER_SEL_CHANNEL1; //Dacc->??
    // enable channel 1 and disable channel 0
    DACC->DACC_CHER |= DACC_CHER_CH1;
    DACC->DACC_CHDR |= DACC_CHDR_CH0;
    //diable interrupts - vet ikke om vi trenger dette
    DACC->DACC_IDR |= DACC_IDR_TXRDY | DACC_IDR_EOC | DACC_IDR_ENDTX | DACC_IDR_TXBUFE;
    // enable interrupts ??
    // DACC->DACC_IER |= DACC_IER_TXRDY
}

void dac_wr(uint32_t int) {
    //check if the dac is ready to accept conversion request
    //if (DACC->DACC_ISR[0]) {
        DACC->DACC_CDR = 4*game_score;  //multiply with 4 because esp has smaller bit resolution
    //}

}