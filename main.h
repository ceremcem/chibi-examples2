/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

/* Macro definitions */
#define S2ST(sec) ((systime_t)((uint32_t)(sec) * (uint32_t)CH_CFG_ST_FREQUENCY))
#define MS2ST(msec) ((systime_t)(((((uint32_t)(msec)) * ((uint32_t)CH_CFG_ST_FREQUENCY)) + 999UL) / 1000UL))

#define ADC_BUF_DEPTH 1 // We only read one by one
#define ADC_CH_NUM 4    // How many channel you use at same time

/* Function prototypes */
uint8_t calculateFCS(uint8_t *buffer, uint8_t count);
uint8_t getData(uint8_t *buffer, uint8_t count);
void prepareFrame(uint8_t *to_send, uint8_t *received);
static void timerCallback(GPTDriver *gptp);
void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n);
static void buttonEvent(uint8_t pad);
void startMainboard(void);


/* Hal configurations */
static PWMConfig pwmcfg =
{
	10000,                                  /* 100 Khz PWM clock frequency.   */
	100,                                    /* 100 period in ticks,thus 1 kHz sample freq.*/
	NULL,									/* callback function*/
	{										/* open all channels*/
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}
	},
	0,
	0
};

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

static const GPTConfig timer_config = {
  frequency:    80000U,
  callback:     timerCallback,
  cr2:          0,
  dier:         0U
};
