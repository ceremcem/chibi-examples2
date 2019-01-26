#include "ch.h"
#include "hal.h"

//#error selam

THD_WORKING_AREA(wa_ramp, 128);
THD_FUNCTION(ramp, arg) {
    (void) arg;
    while(!chThdShouldTerminateX()){
        palSetPad(GPIOA, 2);
    	chThdSleepMicroseconds(400);
        palClearPad(GPIOA, 2);
    	chThdSleepMicroseconds(400);
    }
}
