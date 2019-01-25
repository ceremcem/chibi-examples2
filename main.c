
#include "main.h"

bool fan_auto = true;
uint16_t temp_min = 250;
uint16_t temp_max = 350;
uint16_t temp_read[4] = {0xffff, 0xffff, 0xffff, 0xffff};

static THD_FUNCTION(glow_led, arg) {
    uint8_t led_num = arg;
    uint16_t period = 15;
    uint16_t duty = 0;
    bool direction = FORWARD;

    while (1){
        if (direction == FORWARD){
            duty++;
            if (duty == period){
                direction = BACKWARD;
            }
        }
        else {
            duty--;
        }
        if ((direction == BACKWARD) && (duty == 0)){
            break;
        }
        set_led(led_num);
        chThdSleepMilliseconds(duty);
        reset_led(led_num);
        chThdSleepMilliseconds(period - duty);
    }
}


static THD_FUNCTION(glow_rgb, arg) {
    uint16_t period = 15;
    uint16_t duty = 0;
    uint8_t limit = 100;
    for (uint8_t i = 0; i < 100; i++){
        set_rgb(i, i, i);
        chThdSleepMilliseconds(2);
    }
    for (uint8_t i = 100; i > 0; i--){
        set_rgb(i, i, i);
        chThdSleepMilliseconds(2);
    }
    set_rgb(0, 0, 0);
}

static THD_WORKING_AREA(wa_scanner_leds, 256);
static THD_FUNCTION(scanner_leds, arg) {
    set_led(0); // leave power led on
    uint8_t start_led = 2;
    unsigned i = start_led;
    thread_t *tp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    bool direction = FORWARD;
    while (!chThdShouldTerminateX()) {
        /* Toggling a LED while the main thread is busy.*/
        if (tp[i] != 0) {
            chThdWait(tp[i]);
            //chThdRelease(tp[i]);
        }


        if (i == 0){
            tp[i] = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(256), "hello",
                NORMALPRIO + 1, glow_rgb, i);
        }
        else {
            tp[i] = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(128), "hello",
                NORMALPRIO + 1, glow_led, i);
        }

        chThdSleepMilliseconds(150); //// debugger

        if (direction == FORWARD){
            if (i == 8) {
                direction = BACKWARD;
                chThdWait(tp[i]);
            }
            else {
                i++;
            }
        }
        else {
            if (i == start_led) {
                direction = FORWARD;
                chThdWait(tp[i]);
            }
            else {
                i--;
            }
        }
    }
    /*
    for (uint8_t i = 0; i < 10; i++){
        chThdWait(tp[i]);
    }*/
}


static THD_WORKING_AREA(wa_blink_led, 128);
static THD_FUNCTION(blink_led, arg) {
    uint8_t led = ((uint8_t *) arg)[1];
    uint8_t duration = ((uint8_t *) arg)[2];

    set_led(led);
    chThdSleepMilliseconds(duration);
    reset_led(led);
}

void set_motor_speed(uint8_t speed){
        // PWMD1.1: TIM1_CH3: PA10
        pwmEnableChannel(&PWMD1, 3, 512);
}

/* Register callbacks (1/2) */
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


int main(void)
{
	halInit();
	chSysInit();

    /* Register callbacks (2/2) */
    timer_config.callback = timerCallback;
    adccg.end_cb = adcReadCallback;

    // create scanner leds
    thread_t *tp_scanner_leds = chThdCreateStatic(wa_scanner_leds, sizeof(wa_scanner_leds),
        NORMALPRIO + 1, scanner_leds, NULL);

	uint8_t buffer[12] = {0,0,0,0,0,0,0,0};
	uint8_t send_buffer[12];
	int8_t send_length;

	/*pin configurations are done in board.h*/
	sdStart(&SD2, NULL);
	pwmStart(&PWMD1, &pwmcfg1);

	//adcStart(&ADCD1, &adccfg);
    //palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(2));

	gptStart(&GPTD3, &timer_config);

	nvicDisableVector(EXTI0_IRQn);
	nvicDisableVector(EXTI1_IRQn);
	/*Not tested*/
	//AFIO->EXTICR[0] &= 0xFFFFFF00; /*set a0 and a1 to external interrupt*/
	EXTI->IMR |= 0x00000003;	 /*set them as interrupt*/
	EXTI->EMR &= ~(0x00000003);  /*not event*/
	EXTI->RTSR |= 0x00000003;    /* Rising edge enable */
	EXTI->FTSR |= (0x00000003); /* Falling edge enable */


    // restart mb
    thread_t *t_restart_mb = chThdCreateStatic(wa_restart_mb, sizeof(wa_restart_mb),
        NORMALPRIO + 1, restart_mb, NULL);

    thread_t *t_ramp = chThdCreateStatic(wa_ramp, sizeof(wa_ramp),
        NORMALPRIO + 1, ramp, NULL);

    uint8_t mb_restart_limit = 3;
    uint8_t mb_restart_count = 0;
	/*Main task loop*/
	while(!0)
	{
		/*enable input interrupts*/
		nvicEnableVector(EXTI0_IRQn, STM32_EXT_EXTI0_IRQ_PRIORITY);
		nvicEnableVector(EXTI1_IRQn, STM32_EXT_EXTI1_IRQ_PRIORITY);

		/* poll the thermometers */
		gptStartContinuous(&GPTD3, 40000);

        set_motor_speed(5000);

		/*stop pwm*/
		gptStopTimer(&GPTD3);
		/*disable inputs*/
		nvicDisableVector(EXTI0_IRQn);
		nvicDisableVector(EXTI1_IRQn);

	}
}

static void buttonEvent(uint8_t pad)
{
	uint8_t message[] = {0x03, 0, 0, 0};
	message[1] = pad; //// debugger
    message[2] = (uint8_t) palReadPad(GPIOA, pad);
	message[3] = calculateFCS(message,3);
	sdAsynchronousWrite(&SD2, message, 4);

    if (palReadPad(GPIOA, pad) == 0){ // low/high
        palClearPad(GPIOA, 1);
    } else {
        palSetPad(GPIOA, 1);
    }
}

void adcReadCallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
	(void) adcp;
	(void) n;
    for (uint8_t i = 0; i < 4; i++){
        temp_read[i] = buffer[i];
        if (temp_read[i] > 40){
            temp_read[i] -= 40;
        }
        else {
            temp_read[i] = 0;
        }
    }
    uint16_t diff = temp_max - temp_min;
    if (diff < 20){
        diff = 20;
    }
    int16_t curr = ((temp_read[0] - temp_min) * 100 / diff);
    uint8_t auto_speed;
    if (fan_auto) {
        if (curr < 10){
            auto_speed = 0;
        }
        else if (curr > 100){
            auto_speed = 100;
        }
        else {
            auto_speed = (uint8_t) curr;
        }
    }
}

static void timerCallback(GPTDriver *gptp)
{
	(void) gptp;
    adcStartConversionI (&ADCD1, &adccg, samples_buf, ADC_BUF_DEPTH);
}

void prepareFrame(uint8_t *to_send, uint8_t *received)
{
	to_send[0] = 0x55; // SOT
    to_send[1] = received[0];
	return;
}

uint8_t getData(uint8_t *buffer, uint8_t count)
{
    count++; // for fcs
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
