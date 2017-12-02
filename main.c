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

#define BUFFER_LENGTH 16


uint8_t calculateFCS(uint8_t *buffer, uint8_t count);
uint8_t getData(uint8_t *buffer, uint8_t count);
void prepareFrame(uint8_t *to_send, uint8_t *received, uint8_t length);
//static void timerCallback(void *arg);
static void timerCallback(GPTDriver *gptp);
void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n);


SerialConfig sConfig = 
{
	115200,
	0,
	USART_CR2_CLKEN | USART_CR2_STOP1_BITS | USART_CR2_LINEN,
	0
};

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
#define ADC_BUF_DEPTH 1 // We only read one by one
#define ADC_CH_NUM 4    // How many channel you use at same time
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


static uint8_t temp_thr;
static int8_t last_temp_val;

int main(void)
{
	halInit();
	chSysInit();
	
	uint8_t buffer[8] = {0,0,0,0,0,0,0,0};
	uint8_t send_buffer[8];
	uint8_t send_length;
	
	/* USART 2
	 * A2 - TX
	 * A3 - RX*/
	/*done in board.h why not here..*/
	/*palSetPadMode(GPIOA, 2, 0xB);*/
	/*palSetPadMode(GPIOA, 3, 0x8);*/
	
	
	/*Pin of built in led*/
	palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
	temp_thr = 40; /*40 Celcius as default*/
	
	sdStart(&SD2, NULL);
	pwmStart(&PWMD1, &pwmcfg);
	adcStart(&ADCD1, &adccfg);
	gptStart(&GPTD3, &timer_config);
	
	pwmEnableChannel(&PWMD1, 3, 50);
	gptStartContinuous(&GPTD3, 40000);
	
	
	while(!0)
	{
		sdRead(&SD2, buffer, 1);
		if(0x1 == buffer[0] && getData(buffer, 3))
		{
			/*output set */
			send_length = 4;
			prepareFrame(send_buffer, buffer, 3);
			uint16_t output_data = (buffer[1] << 8) | buffer[2];
			/*for debug*/
			if(0xFFFF == output_data)
				palSetPad(GPIOC, 13);
			else
				palClearPad(GPIOC, 13);
				
			//palWritePort(GPIOB, output_data);
			GPIOB->ODR = output_data;
		}
		else if(0x2 == buffer[0] && getData(buffer, 1))
		{
			/*output get */
			send_length = 4;
			prepareFrame(send_buffer, buffer, 1);
			uint16_t data_on_output;
			data_on_output = GPIOB->ODR & 0x0000FFFF;
			send_buffer[2] = (data_on_output & 0xFF00) >> 8;
			send_buffer[3] = data_on_output & 0x00FF;
		}
		else if(0x3 == buffer[0] && getData(buffer, 1))
		{
			/*input get */
			prepareFrame(send_buffer, buffer, 2);
			send_length = 3;
			uint8_t input_data= GPIOA->IDR & 0x0003;
			send_buffer[2] = input_data;
		}
		else if(0x4 == buffer[0] && getData(buffer, 4))
		{
			/*rgb set */
			prepareFrame(send_buffer, buffer, 4);
			send_length = 4;
			pwmEnableChannel(&PWMD1, 0, buffer[1]);/* red */
			pwmEnableChannel(&PWMD1, 1, buffer[2]);/* green */
			pwmEnableChannel(&PWMD1, 2, buffer[3]);/* blue */
		}
		else if(0x5 == buffer[0] && getData(buffer, 1))
		{
			/*therm get */
			prepareFrame(send_buffer, buffer, 1);
			send_length = 1;
		}
		else if(0x6 == buffer[0] && getData(buffer, 2))
		{
			/*motor val set*/
			prepareFrame(send_buffer, buffer, 2);
			send_length = 2;
			temp_thr = buffer[1];
		}
		else 
		{
			/*invalid frame*/
			continue;
		}
		
		send_buffer[send_length] = calculateFCS(send_buffer, send_length);
		send_length++;/*crc added to end*/
		sdWrite(&SD2, send_buffer, send_length);
	}
}

void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
	(void) adcp;
	(void) n;
    sdAsynchronousWrite(&SD2, (uint8_t *)buffer, 8);
}

static void timerCallback(GPTDriver *gptp)
{
	(void) gptp;
    adcStartConversionI (&ADCD1, &adccg, samples_buf, ADC_BUF_DEPTH);
}

void prepareFrame(uint8_t *to_send, uint8_t *received, uint8_t length)
{
	uint8_t i;
	to_send[0] = 0x55;/*ACK*/
	for(i = 0; i < length; i++)
	{
		to_send[i+1] = received[i];
	}
	return;
}

uint8_t getData(uint8_t *buffer, uint8_t count)
{
	sdRead(&SD2, &(buffer[1]), count);
	uint8_t crc = calculateFCS(buffer, count);
	return (crc == buffer[count]);
}

uint8_t calculateFCS(uint8_t *buffer, uint8_t count)
{
	uint8_t val, i;
	val = 0;
	for(i = 0; i < count; i++)
	{
		val = val ^ buffer[i];
	}
	return val;
}
