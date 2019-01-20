#include "ch.h"
#include "hal.h"

//#error selam

THD_WORKING_AREA(wa_restart_mb, 128);
THD_FUNCTION(restart_mb, arg) {
    (void) arg;
    palSetPad(GPIOD, 1);
	chThdSleepMilliseconds(500);
    palClearPad(GPIOD, 1);
	chThdSleepMilliseconds(200);
    palSetPad(GPIOD, 1);
}
