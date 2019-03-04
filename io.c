#include "hal.h"
#include "io.h"

PWMConfig pwmcfg = {
	frequency: 2000000,                   // PWM clock frequency
	period: 100,                          // PWM resolution (overall PWM signal frequency: PCF/PR)
	callback: NULL,                       // No callback
	channels: {
		{PWM_OUTPUT_DISABLED, NULL},      // 0
		{PWM_OUTPUT_DISABLED, NULL},      // 1
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},      // 2
		{PWM_OUTPUT_DISABLED, NULL}    // 3
	}
};

void init_io(void){
      palSetPadMode(GPIOA, GPIOA_DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);
}
