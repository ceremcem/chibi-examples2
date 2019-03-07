#include "ch.h"
#include "hal.h"
#include "io.h"

extern bool motion_enable;
extern PWMConfig pwmcfg;

THD_WORKING_AREA(wa_ramp, 128);
THD_FUNCTION(ramp, arg) {
    (void) arg;
    const int period_offset = pwmcfg.period;
    int offset = period_offset;
    bool motion_enable0 = false;

    pwmStart(&pulse_PWM_dr, &pwmcfg);
    uint16_t percentage = 5000; // unit: 1/10_000
    pwmEnableChannel(&pulse_PWM_dr, pulse_PWM_ch, PWM_PERCENTAGE_TO_WIDTH (&pulse_PWM_dr, percentage));

    while(!chThdShouldTerminateX()){
        if (!motion_enable0 && motion_enable){
            // rising edge, start ramp
            offset = period_offset;
        }
        motion_enable0 = motion_enable;
        if (motion_enable){
            if (offset > 30){
                offset--;
            }
            pwmChangePeriod(&pulse_PWM_dr, offset); // period
            pwmEnableChannel(&pulse_PWM_dr, pulse_PWM_ch, PWM_PERCENTAGE_TO_WIDTH (&pulse_PWM_dr, percentage));

            chThdSleepMilliseconds(1000);
        } else {
            chThdSleepMilliseconds(1);
        }
    }
}
