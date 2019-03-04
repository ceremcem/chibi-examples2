#include "main.h"

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOA, GPIOA_DIR_OUT);
    chThdSleepMilliseconds(15);
    palClearPad(GPIOA, GPIOA_DIR_OUT);
    chThdSleepMilliseconds(15);
  }
}


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
  init_io();

  // start the blinker thread
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  // start PWM
  pwmStart(&pulse_PWM_dr, &pwmcfg);
  pwmEnableChannel(&pulse_PWM_dr, pulse_PWM_ch, PWM_PERCENTAGE_TO_WIDTH (&pulse_PWM_dr, 5000));

  while (true) {
    chThdSleepMilliseconds(1000); // debugger
  }
}
