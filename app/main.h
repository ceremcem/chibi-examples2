#include "ch.h"
#include "hal.h"

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
extern PWMConfig pwmcfg;
