#include "hal.h"
#include "io.h"

// actual PWM frequency is: pwmcfg.frequency / pwmcfg.period
PWMConfig pwmcfg = {
	frequency: 200000,                   // PWM clock frequency
	period: 150,
	callback: NULL,
	channels: {
		{PWM_OUTPUT_DISABLED, NULL},      // CH1
		{PWM_OUTPUT_DISABLED, NULL},      // CH2
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},   // CH3
		{PWM_OUTPUT_DISABLED, NULL}       // CH4
	}
};

void init_io(void){
      palSetPadMode(GPIOA, GPIOA_DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);
      palSetPadMode(GPIOA, GPIOA_TEST_OUTPUT, PAL_MODE_OUTPUT_PUSHPULL);
}
