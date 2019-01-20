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
uint8_t calculateFCS(uint8_t *buffer, uint8_t count);
uint8_t getData(uint8_t *buffer, uint8_t count);
void prepareFrame(uint8_t *to_send, uint8_t *received);
static void timerCallback(GPTDriver *gptp);
void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n);
static void buttonEvent(uint8_t pad);
void startMainboard(void);
extern void restart_mb(void*);
extern THD_WORKING_AREA(wa_restart_mb, 128);
extern void set_led(int8_t led_number);
extern void reset_led(int8_t led_num);
extern void write_led(uint8_t led_num, bool state);
extern void set_rgb(uint8_t r, uint8_t g, uint8_t b);

// Create buffer to store ADC results. This is
// one-dimensional interleaved array
#define ADC_BUF_DEPTH 1 // We only read one by one
#define ADC_CH_COUNT 4    // How many channel you use at same time
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_COUNT]; // results array

#include "board/index.h"
