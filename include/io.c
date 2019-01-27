#include "hal.h"
#include "io.h"

extern void button_callback(uint8_t pad);
extern void limit_switch();

void init_io(){
    // pulse out
    palSetPadMode(GPIOA, PULSE_OUT, PAL_MODE_OUTPUT_PUSHPULL);

    // direction out
    palSetPadMode(GPIOA, DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);

    // forward button
    palSetPadMode(GPIOA, FORWARD_BUTTON, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, FORWARD_BUTTON, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, FORWARD_BUTTON, button_callback, FORWARD_BUTTON);

    // backward button
    palSetPadMode(GPIOA, BACKWARD_BUTTON, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, BACKWARD_BUTTON, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, BACKWARD_BUTTON, button_callback, BACKWARD_BUTTON);

    // upper limit switch
    palSetPadMode(GPIOA, UPPER_LIMIT_SWITCH, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, UPPER_LIMIT_SWITCH, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, UPPER_LIMIT_SWITCH, limit_switch, UPPER_LIMIT_SWITCH);

    // lower limit switch
    palSetPadMode(GPIOA, LOWER_LIMIT_SWITCH, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, LOWER_LIMIT_SWITCH, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, LOWER_LIMIT_SWITCH, limit_switch, LOWER_LIMIT_SWITCH);
}
