#include "pwm_helpers.h"

#define GPIOA_DIR_OUT           1
#define GPIOA_TEST_OUTPUT       2
#define GPIOA_TEST_INPUT        3

// TIM1_CH3 -> PA10 (@F030), Pin setup is handled in board.c/h
//          -> PA10 (@F103)
#define pulse_PWM_dr      PWMD1        // TIM1
#define pulse_PWM_ch      TIMER_CH3    // DON'T forget to update pwmcfg.channels
