#define INDEX_OFFSET        1u
#define TIMER_CH1           (1 - INDEX_OFFSET)
#define TIMER_CH2           (2 - INDEX_OFFSET)
#define TIMER_CH3           (3 - INDEX_OFFSET)
#define TIMER_CH4           (4 - INDEX_OFFSET)


#define GPIOA_DIR_OUT   1

// TIM1_CH3 -> PA10, Pin setup is handled in board.c/h
#define pulse_PWM_dr      PWMD1        // TIM1
#define pulse_PWM_ch      TIMER_CH3    // DON'T forget to update pwmcfg.channels
