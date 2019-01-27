#include "ch.h"
#include "hal.h"

extern bool motion_enable;

THD_WORKING_AREA(wa_ramp, 128);
THD_FUNCTION(ramp, arg) {
    (void) arg;
    const int period_offset = 20;
    int offset = 20;
    bool motion_enable0 = false;

    while(!chThdShouldTerminateX()){
        if (!motion_enable0 && motion_enable){
            // rising edge, start ramp
            offset = period_offset;
        }
        motion_enable0 = motion_enable;
        if (offset > 0){
            offset--;
        }

        if (motion_enable){
            palSetPad(GPIOA, 2);
        	chThdSleepMicroseconds(50 + offset);
            palClearPad(GPIOA, 2);
        	chThdSleepMicroseconds(50 + offset);
        } else {
            chThdSleepMilliseconds(1);
        }
    }
}
