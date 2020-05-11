#include "hal.h"
#include "io.h"


void init_io(void){
    // LED Out
    palSetPadMode(GPIOA, GPIOA_LED_OUT, PAL_MODE_OUTPUT_PUSHPULL);

}
