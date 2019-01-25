#include "ch.h"
#include "hal.h"

//#error selam

THD_WORKING_AREA(wa_ramp, 128);
THD_FUNCTION(ramp, arg) {
    (void) arg;
    while(!0){
        palSetPad(GPIOA, 1);
    	chThdSleepMicroseconds(400);
        palClearPad(GPIOA, 1);
    	chThdSleepMicroseconds(400);
    }
}
