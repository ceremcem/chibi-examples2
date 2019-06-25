# Description 

This application does:

* Blink (generate square wave) on GPIOA_DIR_OUT
* Write the inverse boolean state of GPIOA_TEST_INPUT to GPIOA_TEST_OUTPUT (via polling)
* Write the inverse boolean state of GPIOA_TEST_INPUT_2 to GPIOA_TEST_OUTPUT_2 (via callbacks)
* Generate PWM output on TIM1_CH3 pin with a ramp frequency on startup
