#define INDEX_OFFSET        1u

#define GPIOA_DIR_OUT   1

// TIM1_CH3 -> PA10, Pin setup is handled in board.c/h
#define pulse_PWM_dr      PWMD1                 // TIM1
#define pulse_PWM_ch      (3 - INDEX_OFFSET)    // CH3, do not forget to update pwmcfg
