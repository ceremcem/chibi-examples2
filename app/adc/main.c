#include "main.h"


uint16_t half_period = 500; 
/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOA, GPIOA_LED_OUT); // debugger 
    chThdSleepMilliseconds(half_period);
    palClearPad(GPIOA, GPIOA_LED_OUT);
    chThdSleepMilliseconds(half_period);
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
    adcStart(&ADCD1, NULL);
    
    //adcStartConversion(&ADCD1, &adcgrpcfg1, samples_buf1, ADC_BUF_DEPTH);
    // ---------------- APP CODE STARTS HERE -------------------------

  // start the blinker thread
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  while (true) {
    if (half_period > 100){
        half_period -= 10;
    }
    chThdSleepMilliseconds(100); // debugger

  }
}

void adcReadCallback1(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
    (void) adcp;
    (void) n;
    for (uint8_t i = 0; i < ADC_CH_NUM; i++){
        // do something with buffer[i]
    }
}
