/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

#include "hal.h"

typedef struct {
        GPIO_TypeDef * port;
        uint8_t pin_number;
} GPIO_PIN;

// GPIOB
GPIO_PIN PWM0_pin={GPIOB, 1};

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config =
{
  {VAL_GPIOAODR, VAL_GPIOACRL, VAL_GPIOACRH},
  {VAL_GPIOBODR, VAL_GPIOBCRL, VAL_GPIOBCRH},
  {VAL_GPIOCODR, VAL_GPIOCCRL, VAL_GPIOCCRH},
  {VAL_GPIODODR, VAL_GPIODCRL, VAL_GPIODCRH},
  {VAL_GPIOEODR, VAL_GPIOECRL, VAL_GPIOECRH},
};
#endif

void set_cr(GPIO_TypeDef * GPIOx, uint8_t pin_number, uint8_t mode){
    uint32_t c;
    if (pin_number < 8) {
        c = GPIOx->CRL;
    } else {
        c = GPIOx->CRH;
    }
    c &= ~(0xf << PIN_NUM(pin_number)); // clear the tuple
    c |= (mode << PIN_NUM(pin_number));
    if (pin_number < 8) {
        GPIOx->CRL = c;
    } else {
        GPIOx->CRH = c;
    }
}

void set_pin_mode(GPIO_PIN* pin, uint8_t mode){
    set_cr(pin->port, pin->pin_number, mode);
}

void hw_init_io(void){
    set_pin_mode(&PWM0_pin, PWM_CONF_50MHZ);
}

PWMConfig pwmcfg = {
	frequency: 2000000,                   // PWM clock frequency
	period: 100,                          // PWM resolution (overall PWM signal frequency: PCF/PR)
	callback: NULL,                       // No callback
	channels: {
		{PWM_OUTPUT_DISABLED, NULL},      // 0
		{PWM_OUTPUT_DISABLED, NULL},      // 1
		{PWM_OUTPUT_DISABLED, NULL},      // 2
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}    // 3
	}
};

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {
    stm32_clock_init();
}

/*
 * Board-specific initialization code.
 */
void boardInit(void) {
    hw_init_io();
}
