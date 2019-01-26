
#include "main.h"

thread_t * motion_t;
bool motion_enable = false;

void stop_motion(){
    //chThdTerminate(motion_t);
    //chThdWait(motion_t);
    motion_enable = false;
}

void start_motion(){
    motion_t = chThdCreateStatic(wa_ramp, sizeof(wa_ramp),
        NORMALPRIO + 1, ramp, NULL);
}

void set_dir(bool dir){
    palWritePad(GPIOA, 3, dir);
}

void move_forward(){
    set_dir(FORWARD);
    motion_enable = true;
}

void move_backward(){
    set_dir(BACKWARD);
    motion_enable = true;
}

void forward_button(bool pressed){
    if (pressed){
        move_forward();
    } else {
        stop_motion();
    }
}

void backward_button(bool pressed){
    if (pressed){
        move_backward();
    } else {
        stop_motion();
    }
}
#define FORWARD_BUTTON 0
#define BACKWARD_BUTTON 1

void button_callback(uint8_t pad){
    bool state = ! palReadPad(GPIOA, pad); //// debugger
    if (pad == FORWARD_BUTTON){
        forward_button(state);
    } else {
        backward_button(state);
    }
}

/* Register callbacks (1/2) */
#define STM32_DISABLE_EXTI0_HANDLER
OSAL_IRQ_HANDLER(Vector58)
{
    // Vector58 : event for first bit of a port, see chibios
	OSAL_IRQ_PROLOGUE();

    button_callback(0);

	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000001U;

	OSAL_IRQ_EPILOGUE();
}

#define STM32_DISABLE_EXTI1_HANDLER
OSAL_IRQ_HANDLER(Vector5C)
{
    // Vector5C: event for second bit of a port, see chibios

	OSAL_IRQ_PROLOGUE();

    button_callback(1);

	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000002U;

	OSAL_IRQ_EPILOGUE();
}

int main(void)
{
	halInit();
	chSysInit();

    start_motion();

    /*
    move_forward();
    chThdSleepMilliseconds(1400);
    stop_motion();
    chThdSleepMilliseconds(1400);
    move_backward();
    */

	/*Main task loop*/
	while(!0)
	{
        chThdSleepMilliseconds(400);
	}
}
