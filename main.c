#include "main.h"
#include "io.h"

thread_t * motion_t;
bool motion_enable = false;

static PWMConfig pwmcfg = {
	frequency: 2000000,   // PWM clock frequency
	period: 100,       // PWM resolution (overall PWM signal frequency: PCF/PR)
	callback: NULL,      // No callback
	channels: {
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}
	}
};

int main(void)
{
	halInit();
	chSysInit();

    init_io();
    start_motion();

    pwmStart(&PWMD3, &pwmcfg);

    // configure PB1 as PWM3/4
    // set GPIOB_CRL -> CNF1 & MODE1
    // CNF1: 10 (alternate function output) & MODE1: 11 (50 MHz)
    // CNF1_MODE1: 0b1011
    uint32_t x = GPIOB->CRL;
    x &= ~(0xf << 4); // clear the tuple
    x |= (0b1011 << 4);
    GPIOB->CRL = x;

    pwmEnableChannel(&PWMD3, 3, PWM_PERCENTAGE_TO_WIDTH (&PWMD3, 3000));


	/*Main task loop*/
	while(!0)
	{
        chThdSleepMilliseconds(1400);
	}
}

void stop_motion(){
    //chThdTerminate(motion_t);
    //chThdWait(motion_t);
    motion_enable = false;
}

void start_motion(){
    motion_t = chThdCreateStatic(wa_ramp, sizeof(wa_ramp),
        HIGHPRIO, ramp, NULL);
}

void set_dir(bool dir){
    if (dir == TRUE){
        palSetPad(GPIOA, DIR_OUT);
    } else {
        palClearPad(GPIOA, DIR_OUT);
    }
    //palWritePad(GPIOA, DIR_OUT, dir);
}

bool reached_top(){
    return ! palReadPad(GPIOA, UPPER_LIMIT_SWITCH);
}

bool reached_bottom(){
    return ! palReadPad(GPIOA, LOWER_LIMIT_SWITCH);
}

void move_up(){
    if (! reached_top()){
        set_dir(UPWARD);
        motion_enable = true;
    }
}

void move_down(){
    if (! reached_bottom()){
        set_dir(DOWNWARD);
        motion_enable = true;
    }
}

void UPWARD_button(bool pressed){
    if (pressed){
        move_up();
    } else {
        stop_motion();
    }
}

void DOWNWARD_button(bool pressed){
    if (pressed){
        move_down();
    } else {
        stop_motion();
    }
}

void button_callback(uint8_t pad){
    bool state = ! palReadPad(GPIOA, pad); //// debugger
    if (pad == UPWARD_BUTTON){
        UPWARD_button(state);
    } else {
        DOWNWARD_button(state);
    }
}

void limit_switch(uint8_t pad){
    bool state = ! palReadPad(GPIOA, pad);

    if (state == PAL_HIGH){
        stop_motion();
    }
}
