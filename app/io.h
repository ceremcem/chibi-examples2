#define INDEX_OFFSET        1u
#define TIMER_CH3           (3 - INDEX_OFFSET)

#define DIR_OUT                 GPIOA_0
#define UPWARD_BUTTON           GPIOA_1
#define DOWNWARD_BUTTON         GPIOA_2
#define LOWER_LIMIT_SWITCH      GPIOA_3
#define UPPER_LIMIT_SWITCH      GPIOA_4
// TIM1_CH3 -> PA10, Pin setup is handled in board.c/h
#define pulse_PWM_dr      PWMD1        // TIM1
#define pulse_PWM_ch      TIMER_CH3    // DON'T forget to update pwmcfg.channels
// end of TIM1_CH3
