#include "hal.h"

extern void button_callback(uint8_t pad);

void init_io(){
    // see chibios/os/hal/include/hal_pal.h for modes
    palSetPadMode(GPIOA, 2, PAL_MODE_OUTPUT_PUSHPULL); // pulse
    palSetPadMode(GPIOA, 3, PAL_MODE_OUTPUT_PUSHPULL); // dir

    palSetPadMode(GPIOA, 0U, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, 0U, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, 0U, button_callback, 0);

    palSetPadMode(GPIOA, 1U, PAL_MODE_INPUT);
    palEnablePadEvent(GPIOA, 1U, PAL_EVENT_MODE_BOTH_EDGES);
    palSetPadCallback(GPIOA, 1U, button_callback, 1);

}
