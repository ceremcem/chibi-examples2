
#include "main.h"

static uint8_t temp_thr;
//static int8_t last_temp_val;

#define STM32_DISABLE_EXTI0_HANDLER
OSAL_IRQ_HANDLER(Vector58)
{
    // Vector58 : event for first bit of a port, see chibios
	OSAL_IRQ_PROLOGUE();

	buttonEvent(0);
	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000001U;

	OSAL_IRQ_EPILOGUE();
}

#define STM32_DISABLE_EXTI1_HANDLER
OSAL_IRQ_HANDLER(Vector5C)
{
    // Vector5C: event for second bit of a port, see chibios

	OSAL_IRQ_PROLOGUE();

	buttonEvent(1);
	/* Tell you read the interrupt*/
	EXTI->PR |= 0x00000002U;

	OSAL_IRQ_EPILOGUE();
}

/*
LED_0: GPIOA, 12
LED_1: GPIOB, 2
LED_2: PB1

*/
void set_led(int8_t led_num){
    switch(led_num){
        case 0:
            palSetPad(GPIOA, 12);
            break;
        case 1:
            palSetPad(GPIOB, 2);
            break;
        case 2:
            palSetPad(GPIOB, 1);
            break;
        case 3:
            palSetPad(GPIOB, 0);
            break;
        case 4:
            palSetPad(GPIOB, 3);
            break;
        case 5:
            palSetPad(GPIOB, 4);
            break;
        case 6:
            palSetPad(GPIOB, 5);
            break;
        case 7:
            palSetPad(GPIOB, 6);
            break;
        case 8:
            palSetPad(GPIOB, 7);
            break;
    }
}

void reset_led(int8_t led_num){
    switch(led_num){
        case 0:
            palClearPad(GPIOA, 12);
            break;
        case 1:
            palClearPad(GPIOB, 2);
            break;
        case 2:
            palClearPad(GPIOB, 1);
            break;
        case 3:
            palClearPad(GPIOB, 0);
            break;
        case 4:
            palClearPad(GPIOB, 3);
            break;
        case 5:
            palClearPad(GPIOB, 4);
            break;
        case 6:
            palClearPad(GPIOB, 5);
            break;
        case 7:
            palClearPad(GPIOB, 6);
            break;
        case 8:
            palClearPad(GPIOB, 7);
            break;
    }
}



static THD_WORKING_AREA(waBlinker, 128);
static THD_FUNCTION(Blinker, arg) {
  unsigned i = 0;

  while (!chThdShouldTerminateX()) {
    /* Toggling a LED while the main thread is busy.*/
    set_led(i);
    set_led(i + 1);

    /* Delay of 250 milliseconds.*/
    chThdSleepMilliseconds(250);

    reset_led(i);

    /* Counting the number of blinks.*/
    i++;
    i = i % 9;
  }

  /* Returning the number of iterations.*/
  chThdExit((msg_t)i);
}

int main(void)
{
	halInit();
	chSysInit();

    thread_t *tp = chThdCreateStatic(waBlinker, sizeof(waBlinker),
                                       NORMALPRIO + 1, Blinker, NULL);

	uint8_t buffer[8] = {0,0,0,0,0,0,0,0};
	uint8_t send_buffer[8];
	uint8_t send_length;
	temp_thr = 40; /*set 40 Celcius as default*/

	/*pin configurations are done in board.h*/
	sdStart(&SD2, NULL);
	pwmStart(&PWMD1, &pwmcfg);
	adcStart(&ADCD1, &adccfg);
	gptStart(&GPTD3, &timer_config);

	nvicDisableVector(EXTI0_IRQn);
	nvicDisableVector(EXTI1_IRQn);
	/*Not tested*/
	//AFIO->EXTICR[0] &= 0xFFFFFF00; /*set a0 and a1 to external interrupt*/
	EXTI->IMR |= 0x00000003;	 /*set them as interrupt*/
	EXTI->EMR &= ~(0x00000003);  /*not event*/
	EXTI->RTSR |= 0x00000003;    /* Rising edge enable */
	EXTI->FTSR |= (0x00000003); /* Falling edge enable */


    palSetPad(GPIOD, 1);
	chThdSleepMilliseconds(500);
    palClearPad(GPIOD, 1);
	chThdSleepMilliseconds(200);
    palSetPad(GPIOD, 1);


    // initial motor speed
	pwmEnableChannel(&PWMD1, 3, 50);/* motor out */


	/*Main task loop*/
	while(!0)
	{
		//startMainboard();

		/*enable input interrupts*/
		nvicEnableVector(EXTI0_IRQn, STM32_EXT_EXTI0_IRQ_PRIORITY);
		nvicEnableVector(EXTI1_IRQn, STM32_EXT_EXTI1_IRQ_PRIORITY);

		/*start doing own job*/
		gptStartContinuous(&GPTD3, 40000);

		/* expect a message in 60 seconds otherwise reset the board */
		while(sdReadTimeout(&SD2, buffer, 1,S2ST(30)))
		{
			if(0x1 == buffer[0] && getData(buffer, 3)) //debugger
			{
				/* output set */
				send_length = 4;
				prepareFrame(send_buffer, buffer, 3);
				uint32_t output_data = (buffer[1] << 8) | buffer[2];

				GPIOB->ODR = output_data; //debugger
                int a12 = output_data & (1 << 8);
                if(a12 != 0){
                    palSetPad(GPIOA, 12);
                }
                else {
                    palClearPad(GPIOA, 12);
                }
                chThdTerminate(tp);

			}
			else if(0x2 == buffer[0] && getData(buffer, 1))
			{
				/*output get */
				send_length = 4;
				prepareFrame(send_buffer, buffer, 1);
				uint16_t data_on_output; //debugger
				data_on_output = (uint16_t) GPIOB->ODR;
				send_buffer[2] = (uint8_t) ((data_on_output & 0xFF00) >> 8);
				send_buffer[3] = (uint8_t) data_on_output & 0x00FF;
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
            else if(0x7 == buffer[0] && getData(buffer, 3))
            {
                prepareFrame(send_buffer, buffer, 2);
                int manual_speed = buffer[2]; // debugger
				pwmEnableChannel(&PWMD1, 3, manual_speed);/* motor out */
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

		/*stop pwm*/
		gptStopTimer(&GPTD3);
		/*disable inputs*/
		nvicDisableVector(EXTI0_IRQn);
		nvicDisableVector(EXTI1_IRQn);

	}
}

/* Not tested */
static void buttonEvent(uint8_t pad)
{
	uint8_t message[] = {0x03, 0, 0, 0};
	message[1] = pad; // debugger
    message[2] = (uint8_t) palReadPad(GPIOA, pad);
	message[3] = calculateFCS(message,3);
	sdAsynchronousWrite(&SD2, message, 4);
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
		mainboard_ready = 0;
		/*main wake-up algorithm*/

		/* Use pc0 to open mainboard
		 * it's configured as push-pull in board.h */

		palClearPad(GPIOC, 0);
		chThdSleepMilliseconds(200);
		palSetPad(GPIOC, 0);
		chThdSleepMilliseconds(200);
		palClearPad(GPIOC, 0);

		start_time = chVTGetSystemTimeX();
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
	(void) buffer;
    buffer; //// debugger
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
    // TODO: use timeout read
	sdRead(&SD2, &(buffer[1]), count);
	uint8_t crc = calculateFCS(buffer, count);


    /******** FIXME: returning immediately only for debugging purposes ****/
    //return true;


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
