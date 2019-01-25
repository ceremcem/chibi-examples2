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

static PWMConfig pwmcfg1 =
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
