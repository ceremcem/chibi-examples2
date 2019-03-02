#include "main.h"

/*
 * Green LED blinker thread, times are in milliseconds.
 */
/*
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOA, GPIOA_LED_GREEN);
    chThdSleepMilliseconds(500);
    palClearPad(GPIOA, GPIOA_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}
*/

#define DIR_OUT 1

int main(void) {
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  palSetPadMode(GPIOA, DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);

  //chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  while (true) {
    palSetPad(GPIOA, DIR_OUT);
    chThdSleepMilliseconds(10); //// debugger
    palClearPad(GPIOA, DIR_OUT);
    chThdSleepMilliseconds(10); //// debugger

  }
}
