#include "ch.h"
#include "hal.h"

/* Macro definitions */
#define S2ST(sec) ((systime_t)((uint32_t)(sec) * (uint32_t)CH_CFG_ST_FREQUENCY))
#define MS2ST(msec) ((systime_t)(((((uint32_t)(msec)) * ((uint32_t)CH_CFG_ST_FREQUENCY)) + 999UL) / 1000UL))
#define MERGE_TWO_BYTES(a, b)                   ((a << 8) + b)
#define SPLIT_TWO_BYTES(target, index, src)     target[index] = ((src & 0xff00) >> 8); target[index+1] = (src & 0xff);
#define GET_BIT(source, bit_num) ((source >> bit_num) & 0x01)

#define UPWARD true
#define DOWNWARD false

/* main.c */
void stop_motion(void);
void start_motion(void);
void set_dir(bool dir);
bool reached_top(void);
bool reached_bottom(void);
void move_up(void);
void move_down(void);
void UPWARD_button(bool pressed);
void DOWNWARD_button(bool pressed);
void button_callback(uint8_t pad);
void limit_switch(uint8_t pad);

// ramp.c
extern THD_WORKING_AREA(wa_ramp, 128);
extern void ramp(void*);

//io.c
void init_io(void);
