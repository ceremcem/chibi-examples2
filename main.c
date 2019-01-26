
#include "main.h"



void button_callback(){
    
}

/* Register callbacks (1/2) */
#define STM32_DISABLE_EXTI0_HANDLER
OSAL_IRQ_HANDLER(Vector58)
{
    // Vector58 : event for first bit of a port, see chibios
	OSAL_IRQ_PROLOGUE();

    button_callback(0); // debugger

	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000001U;

	OSAL_IRQ_EPILOGUE();
}

#define STM32_DISABLE_EXTI1_HANDLER
OSAL_IRQ_HANDLER(Vector5C)
{
    // Vector5C: event for second bit of a port, see chibios

	OSAL_IRQ_PROLOGUE();

    button_callback(1); // debugger

	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000002U;

	OSAL_IRQ_EPILOGUE();
}

int main(void)
{
	halInit();
	chSysInit();

	/*Main task loop*/
	while(!0)
	{
        chThdSleepMilliseconds(400);
	}
}
