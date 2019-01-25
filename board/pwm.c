/* QUICK HOWTO:

A "PWM Driver" (PWMDx) corresponds to a TIMx of the MCU.
A PWM Driver has 4 channels (TIMx_CH{1..4})

Usage:
1. See MCU datasheet to see which channel (TIMx_CHy) is connected to which physical pin. (see pinouts section.)
2. Enable PWM in halconf.h
3. Create a PWMConfig instance to setup corresponding channels of a timer.
4. Start the driver: pwmStart(&PWMD1, &pwmcfg)
5. Set and change the actual values of a channel by pwmEnableChannel(&PWMD1, 1, ...)

*/

#include "hal.h"

PWMConfig pwmcfg1 =
{
	10000,                                  /* 100 Khz PWM clock frequency.   */
	100,                                    /* 100 period in ticks,thus 1 kHz sample freq.*/
	NULL,									/* callback function*/
	{										/* open all channels*/
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}
	},
	0,
	0
};

// Setup PWM3/1
// configure STM32_PWM_USE_TIM3 in mcuconf.h
PWMConfig pwmcfg3 =
{
	100000,                                 /* PWM clock frequency in Hz */
	100,                                    /* Number of PWM clock cycles per sample*/
	NULL,									/* callback function*/
	{										/* setup channels from CH1 to CH4*/
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL}
	},
	0,
	0
};


void initializePWM(void){
    pwmStart(&PWMD3, &pwmcfg3);
}

void set_motor_speed(uint8_t speed){
    pwmEnableChannel(&PWMD3, 1, speed); // PA6
}
