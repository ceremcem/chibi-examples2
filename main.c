
#include "main.h"

static uint8_t temp_thr;
static int8_t last_temp_val;

int main(void)
{
	halInit();
	chSysInit();
	
	uint8_t buffer[8] = {0,0,0,0,0,0,0,0};
	uint8_t send_buffer[8];
	uint8_t send_length;
	temp_thr = 40; /*set 40 Celcius as default*/
	
	/*pin configurations are done in board.h*/
	sdStart(&SD2, NULL);
	pwmStart(&PWMD1, &pwmcfg);
	adcStart(&ADCD1, &adccfg);
	gptStart(&GPTD3, &timer_config);
	
	chThdSleepMilliseconds(2000);
	
	/*Main task loop*/
	while(!0)
	{
		startMainboard();
		
		/*start doing own job*/
		gptStartContinuous(&GPTD3, 40000);
		
		/* expect a message in 60 seconds otherwise reset the board */
		while(sdReadTimeout(&SD2, buffer, 1,S2ST(30)))
		{
			if(0x1 == buffer[0] && getData(buffer, 3))
			{
				/* output set */
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
				/* invalid frame */
				continue;
			}
			
			send_buffer[send_length] = calculateFCS(send_buffer, send_length);
			send_length++;/*crc added to end*/
			sdWrite(&SD2, send_buffer, send_length);
		}
		gptStopTimer(&GPTD3);
	}
}


void startMainboard(void)
{	
	uint8_t data_buffer;
	const uint8_t wakeup_message[8] = {0xca,0xfe,0xba,0xbe,0xde,0xad,0xbe,0xef};
	uint8_t counter = 0;
	uint8_t mainboard_ready;
	uint32_t start_time;
	do
	{
		palSetPad(GPIOC, 13);
		chThdSleepMilliseconds(100);
		palClearPad(GPIOC, 13);
		chThdSleepMilliseconds(100);
		start_time = chVTGetSystemTimeX();
		mainboard_ready = 0;
		/*main wake-up algorithm*/
		
		/* Use pc0 to open mainboard
		 * it's configured as push-pull in board.h */
		 
		palClearPad(GPIOC, 0);
		chThdSleepMilliseconds(200);
		palSetPad(GPIOC, 0);
		chThdSleepMilliseconds(200);
		palClearPad(GPIOC, 0);
		
		/*expect wake up signal in 15 seconds*/
		while(chVTGetSystemTimeX() - start_time < S2ST(15))
		{
			sdReadTimeout(&SD2, &data_buffer, 1, 100);
			if(data_buffer == wakeup_message[counter])
			{
				counter++;
				if(counter == 8)
				{
					mainboard_ready = 1;
					break;
				}
			}
			else if(data_buffer == wakeup_message[0])
			{
				counter = 1;
			}
			else
			{
				counter = 0;
			}
		}
	}while(0 == mainboard_ready);
	
	/* send deadbeefcafebabe */
	sdWrite(&SD2, wakeup_message + 4, 4);
	sdWrite(&SD2, wakeup_message, 4);
}

void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
	(void) adcp;
	(void) n;
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
