/* Hal configurations */
static PWMConfig pwmcfg =
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
