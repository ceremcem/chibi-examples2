#include "ch.h"
#include "hal.h"
#include "io.h"

extern bool motion_enable;

THD_WORKING_AREA(wa_ramp, 128);
THD_FUNCTION(ramp, arg) {
    (void) arg;
    const int period = 40; // main period (optimum value: 50)
    const int period_offset = 870;
    int offset = period_offset;
    bool motion_enable0 = false;

    while(!chThdShouldTerminateX()){
        if (!motion_enable0 && motion_enable){
            // rising edge, start ramp
            offset = period_offset;
        }
        motion_enable0 = motion_enable;
        if (motion_enable){
            if (offset > 0){
                offset--;
            }
            palSetPad(GPIOA, PULSE_OUT);
        	chThdSleepMicroseconds(period + offset);
            palClearPad(GPIOA, PULSE_OUT);
        	chThdSleepMicroseconds(period + offset);
        } else {
            chThdSleepMilliseconds(1);
        }
    }
}
