#include "sam.h"
#include "dac_driver.h"

void dac_init(void) {
    //free running mode and does not sleep between conversions
    DACC_MR |= (DIS) | WORD
    
}