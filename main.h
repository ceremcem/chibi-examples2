#include "ch.h"
#include "hal.h"

/* Macro definitions */
#define S2ST(sec) ((systime_t)((uint32_t)(sec) * (uint32_t)CH_CFG_ST_FREQUENCY))
#define MS2ST(msec) ((systime_t)(((((uint32_t)(msec)) * ((uint32_t)CH_CFG_ST_FREQUENCY)) + 999UL) / 1000UL))

/* Function prototypes */
uint8_t calculateFCS(uint8_t *buffer, uint8_t count);
uint8_t getData(uint8_t *buffer, uint8_t count);
void prepareFrame(uint8_t *to_send, uint8_t *received);
static void timerCallback(GPTDriver *gptp);
void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n);
static void buttonEvent(uint8_t pad);
void startMainboard(void);

// Create buffer to store ADC results. This is
// one-dimensional interleaved array
#define ADC_BUF_DEPTH 1 // We only read one by one
#define ADC_CH_COUNT 4    // How many channel you use at same time
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_COUNT]; // results array

#include "board/index.h"
