#include "main.h"
#include "io.h"

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
    palWritePad(GPIOA, DIR_OUT, dir);
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

void button_callback(uint8_t pad){
    bool state = ! palReadPad(GPIOA, pad);
    if (pad == FORWARD_BUTTON){
        forward_button(state);
    } else {
        backward_button(state);
    }
}

void limit_switch(uint8_t pad){
    bool state = ! palReadPad(GPIOA, pad);

    if (state == PAL_HIGH){
        stop_motion();
    }
}

int main(void)
{
	halInit();
	chSysInit();

    init_io();
    start_motion();

	/*Main task loop*/
	while(!0)
	{
        chThdSleepMilliseconds(400);
	}
}
