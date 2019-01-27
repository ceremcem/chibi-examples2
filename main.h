#include "ch.h"
#include "hal.h"

/* Macro definitions */
#define S2ST(sec) ((systime_t)((uint32_t)(sec) * (uint32_t)CH_CFG_ST_FREQUENCY))
#define MS2ST(msec) ((systime_t)(((((uint32_t)(msec)) * ((uint32_t)CH_CFG_ST_FREQUENCY)) + 999UL) / 1000UL))
#define MERGE_TWO_BYTES(a, b)                   ((a << 8) + b)
#define SPLIT_TWO_BYTES(target, index, src)     target[index] = ((src & 0xff00) >> 8); target[index+1] = (src & 0xff);
#define GET_BIT(source, bit_num) ((source >> bit_num) & 0x01)
#define FORWARD true
#define BACKWARD false

/* main.c */
static void buttonEvent(uint8_t pad);

// ramp.c
extern THD_WORKING_AREA(wa_ramp, 128);
extern void ramp(void*);

//board/pwm.c
//extern void initializePWM(void);
//extern void set_motor_speed(uint8_t speed);
