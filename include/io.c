#include "hal.h"
#include "io.h"

extern void button_callback(uint8_t pad);
extern void limit_switch();

THD_WORKING_AREA(wa_poll_switches, 128);
THD_FUNCTION(poll_switches, arg) {
    (void) arg;
    bool up, up0 = false, down, down0 = false;
    while(!chThdShouldTerminateX()){
        up = palReadPad(GPIOA, UPPER_LIMIT_SWITCH);
        if (up0 ^ up){
            limit_switch(UPPER_LIMIT_SWITCH);
        }
        up0 = up;

        down = palReadPad(GPIOA, LOWER_LIMIT_SWITCH);
        if (down0 ^ down){
            limit_switch(LOWER_LIMIT_SWITCH);
        }
        down0 = down;

        chThdSleepMilliseconds(10);
    }
}

void init_io(){
    // pulse out
    palSetPadMode(GPIOA, PULSE_OUT, PAL_MODE_OUTPUT_PUSHPULL);

    // direction out
    palSetPadMode(GPIOA, DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);

    // forward button
    palSetPadMode(GPIOA, UPWARD_BUTTON, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, UPWARD_BUTTON, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, UPWARD_BUTTON, button_callback, UPWARD_BUTTON);

    // backward button
    palSetPadMode(GPIOA, DOWNWARD_BUTTON, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, DOWNWARD_BUTTON, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, DOWNWARD_BUTTON, button_callback, DOWNWARD_BUTTON);

    // upper limit switch
    palSetPadMode(GPIOA, UPPER_LIMIT_SWITCH, PAL_MODE_INPUT);
    //palEnablePadEvent(GPIOA, UPPER_LIMIT_SWITCH, PAL_EVENT_MODE_BOTH_EDGES);
    //palSetPadCallback(GPIOA, UPPER_LIMIT_SWITCH, limit_switch, UPPER_LIMIT_SWITCH);

    // lower limit switch
    palSetPadMode(GPIOA, LOWER_LIMIT_SWITCH, PAL_MODE_INPUT);
    //palEnablePadEvent(GPIOA, LOWER_LIMIT_SWITCH, PAL_EVENT_MODE_BOTH_EDGES);
    //palSetPadCallback(GPIOA, LOWER_LIMIT_SWITCH, limit_switch, LOWER_LIMIT_SWITCH);

    chThdCreateStatic(wa_poll_switches, sizeof(wa_poll_switches),
        NORMALPRIO + 1, poll_switches, NULL);
}
