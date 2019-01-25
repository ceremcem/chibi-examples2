#include "ch.h"
#include "hal.h"

void set_led(int8_t led_num){
    switch(led_num){
        case 0:
            palSetPad(GPIOA, 12);
            break;
        case 1:
            palSetPad(GPIOB, 2);
            break;
        case 2:
            palSetPad(GPIOB, 1);
            break;
        case 3:
            palSetPad(GPIOB, 0);
            break;
        case 4:
            palSetPad(GPIOB, 3);
            break;
        case 5:
            palSetPad(GPIOB, 4);
            break;
        case 6:
            palSetPad(GPIOB, 5);
            break;
        case 7:
            palSetPad(GPIOB, 6);
            break;
        case 8:
            palSetPad(GPIOB, 7);
            break;
    }
}

void reset_led(int8_t led_num){
    switch(led_num){
        case 0:
            palClearPad(GPIOA, 12);
            break;
        case 1:
            palClearPad(GPIOB, 2);
            break;
        case 2:
            palClearPad(GPIOB, 1);
            break;
        case 3:
            palClearPad(GPIOB, 0);
            break;
        case 4:
            palClearPad(GPIOB, 3);
            break;
        case 5:
            palClearPad(GPIOB, 4);
            break;
        case 6:
            palClearPad(GPIOB, 5);
            break;
        case 7:
            palClearPad(GPIOB, 6);
            break;
        case 8:
            palClearPad(GPIOB, 7);
            break;
    }
}

void write_led(uint8_t led_num, bool state){
    if (state) {
        set_led(led_num);
    }
    else {
        reset_led(led_num);
    }
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b){
    pwmEnableChannel(&PWMD1, 1, r);/* red */
    pwmEnableChannel(&PWMD1, 0, g);/* green */
    pwmEnableChannel(&PWMD1, 2, b);/* blue */
}
