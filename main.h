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

/* Function prototypes */
static void buttonEvent(uint8_t pad);
void startMainboard(void);
extern void set_led(int8_t led_number);
extern void reset_led(int8_t led_num);
extern void write_led(uint8_t led_num, bool state);
extern void set_rgb(uint8_t r, uint8_t g, uint8_t b);
// ramp worker
extern THD_WORKING_AREA(wa_ramp, 128);
extern void ramp(void*);

#include "board/index.h"
