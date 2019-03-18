#include "pwm_helpers.h"

#define GPIOA_DIR_OUT           0
#define GPIOA_TEST_INPUT        2
#define GPIOA_TEST_OUTPUT       1

#define GPIOA_TEST_OUTPUT_2     7
#define GPIOA_TEST_INPUT_2      4

// TIM1_CH3 -> PA10 (@F030), Pin setup is handled in board.c/h
//          -> PA10 (@F103)
#define pulse_PWM_dr      PWMD1        // TIM1
#define pulse_PWM_ch      TIMER_CH3    // DON'T forget to update pwmcfg.channels

extern void button_callback(void);
