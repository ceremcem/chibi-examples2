
#include "main.h"

void set_motor_speed(uint8_t speed){
        // PWMD1.1: TIM1_CH3: PA10
        pwmEnableChannel(&PWMD1, 3, speed);
}

/* Register callbacks (1/2) */
#define STM32_DISABLE_EXTI0_HANDLER
OSAL_IRQ_HANDLER(Vector58)
{
    // Vector58 : event for first bit of a port, see chibios
	OSAL_IRQ_PROLOGUE();

	buttonEvent(0); // debugger
	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000001U;

	OSAL_IRQ_EPILOGUE();
}

#define STM32_DISABLE_EXTI1_HANDLER
OSAL_IRQ_HANDLER(Vector5C)
{
    // Vector5C: event for second bit of a port, see chibios

	OSAL_IRQ_PROLOGUE();

	buttonEvent(1); // debugger
	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000002U;

	OSAL_IRQ_EPILOGUE();
}


int main(void)
{
	halInit();
	chSysInit();

    /* Register callbacks (2/2) */
    //timer_config.callback = timerCallback;
    //adccg.end_cb = adcReadCallback;

	/*pin configurations are done in board.h*/
	sdStart(&SD2, NULL);
	pwmStart(&PWMD1, &pwmcfg1);

    thread_t *t_ramp = chThdCreateStatic(wa_ramp, sizeof(wa_ramp),
        NORMALPRIO + 1, ramp, NULL);
    (void) t_ramp;

	/*Main task loop*/
	while(!0)
	{
        set_motor_speed((uint8_t)512);
        chThdSleepMilliseconds(400);
	}
}

static void buttonEvent(uint8_t pad)
{
    if (palReadPad(GPIOA, pad) == PAL_LOW){ // low/high
        palClearPad(GPIOA, 1);
    } else {
        palSetPad(GPIOA, 1);
    }
}
