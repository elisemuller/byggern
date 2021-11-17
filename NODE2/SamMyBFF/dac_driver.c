
#include <stdint.h>

#include "sam.h"
#include "dac_driver.h"

void dac_init(void) {
    // free running mode word transfer, does not sleep between conversions, channel 1 selected
    DACC->DACC_MR |= DACC_MR_WORD_WORD | DACC_MR_USER_SEL_CHANNEL1; //Dacc->??
    // enable channel 1 and disable channel 0
    DACC->DACC_CHER |= DACC_CHER_CH1;
    DACC->DACC_CHDR |= DACC_CHDR_CH0;
    //diable interrupts - vet ikke om vi trenger dette
    DACC->DACC_IDR |= DACC_IDR_TXRDY | DACC_IDR_EOC | DACC_IDR_ENDTX | DACC_IDR_TXBUFE;
}

void dac_wr(uint32_t game_score) {
    DACC->DACC_CDR = game_score;
}