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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the Olimex STM32-P103 proto board.
 */

/*
 * Board identifier.
 */
#define BOARD_OLIMEX_STM32_P103
#define BOARD_NAME              "STM32F103C8T6"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xB

/*
 * IO pins assignments.
 */
#define GPIOA_BUTTON            0
#define GPIOA_SPI1NSS           4

#define GPIOB_SPI2NSS           12

#define GPIOC_USB_P             4
#define GPIOC_MMCWP             6
#define GPIOC_MMCCP             7
#define GPIOC_CAN_CNTL          10
#define GPIOC_USB_DISC          11
#define GPIOC_LED               12

/*
 * IO lines assignments.
 */
#define LINE_BUTTON                 PAL_LINE(GPIOA, 0U)
#define LINE_SPI1NSS                PAL_LINE(GPIOA, 4U)
#define LINE_SPI2NSS                PAL_LINE(GPIOB, 12U)
#define LINE_USB_P                  PAL_LINE(GPIOC, 4U)
#define LINE_MMCWP                  PAL_LINE(GPIOC, 6U)
#define LINE_MMCCP                  PAL_LINE(GPIOC, 7U)
#define LINE_CAN_CNTL               PAL_LINE(GPIOC, 10U)
#define LINE_USB_DISC               PAL_LINE(GPIOC, 11U)
#define LINE_LED                    PAL_LINE(GPIOC, 12U)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

#define INPUT_ANALOG 			0x0
#define OUTPUT_PUSHPULL_10MHZ 	0x1
#define OUTPUT_PUSHPULL_2MHZ  	0x2
#define OUTPUT_PUSHPULL_50MHZ	0x3
#define INPUT_DIGITAL 			0x4
#define OUTPUT_OPEN_DRAIN_10MHZ	0x5
#define OUTPUT_OPEN_DRAIN_2MHZ	0x6
#define OUTPUT_OPEN_DRAIN_50MHZ	0x7

/*
 * Port A setup.
 */
#define VAL_GPIOACRL            0x00008B44      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x8882BBBB      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
 * Everything output push pull
 */
#define VAL_GPIOBCRL            0x22222222      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x22222222      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC4  - Normal input because there is an external resistor.
 * PC6  - Normal input because there is an external resistor.
 * PC7  - Normal input because there is an external resistor.
 * PC10 - Push Pull output (CAN CNTRL).
 * PC11 - Push Pull output (USB DISC).
 * PC12 - Push Pull output (LED).
 * PC13 - Push Pull output (LED).
 */
#define VAL_GPIOCCRL            0x44848882      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x88333388      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input (XTAL).
 * PD1  - Normal input (XTAL).
 */
#define VAL_GPIODCRL            0x88888833      /*  PD7...PD0 */
// WARNING: PD0 and PD1 is remapped to be used as outputs, see board.c
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
