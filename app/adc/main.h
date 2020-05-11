#include "ch.h"
#include "hal.h"
#include "io.h"

// io.c
extern void init_io(void);

void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n);

#define ADC_BUF_DEPTH 1 // We only read one by one
#define ADC_CH_NUM 1    // How many channel you use at same time

// Create buffer to store ADC results. This is
// one-dimensional interleaved array
static adcsample_t samples_buf[ADC_BUF_DEPTH * ADC_CH_NUM]; // results array

/*dummy configure for adc*/
static const ADCConfig adccfg = {.dummy = 0};

static const ADCConversionGroup adccg = {
   // this 3 fields are common for all MCUs
      // set to TRUE if need circular buffer, set FALSE otherwise
      circular : FALSE,
      // number of channels
      num_channels : ADC_CH_NUM,
      // callback function when conversion ends
      end_cb : adcReadCallback,
      //callback function when error appears
      error_cb : NULL,
      //look to datasheet for information about the registers
      // CR1 register content
      cr1 : 0,
      // CR2 register content
      cr2 : ADC_CR2_SWSTART | ADC_CR2_EXTTRIG | (7 << 17),//means single conversion mode
      // SMRP1 register content
      smpr1 : 0,
      // SMRP2 register content
      smpr2 : ((0b111)<<12)|((0b111)<<15)| ((0b111)<<18)|((0b111)<<21), /* sampling time */
      // SQR1 register content
      sqr1 : ((ADC_CH_NUM - 1) << 20),
      // SQR2 register content
      sqr2 : 0,
      // SQR3 register content. We must select 1 channel
      // For example 6th channel
      // if we want to select more than 1 channel then simply
      // shift and logic or the values example (ch 15 & ch 10) : (15 | (10 << 5))
      sqr3 : 4 | (5 << 5) | (6 << 10) | (7 << 15) /*register channels*/
};
