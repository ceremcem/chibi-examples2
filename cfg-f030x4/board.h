/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

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
 * Setup for STMicroelectronics STM32F030F4P6 board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_STM32F030F4P6
#define BOARD_NAME                  "STMicroelectronics STM32F030F4P6"

/*
 * MCU type as defined in the ST header.
 */
#define STM32F030x4
#define STM32F030x6 // see https://github.com/ChibiOS/ChibiOS/pull/31




/*
 * IO pins assignments.
 */

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2U))
#define PIN_OSPEED_10M(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_40M(n)           (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup: DEFAULT
 *
 */

// defaults, see Reference Manual, 8.4
#define GPIOA_MODER_DEFAULT                 0x28000000
#define GPIOx_MODER_DEFAULT                 0
#define GPIOA_OTYPER_DEFAULT                0
#define GPIOx_OTYPER_DEFAULT                0
#define GPIOA_OSPEEDR_DEFAULT               0x0C000000
#define GPIOx_OSPEEDR_DEFAULT               0
#define GPIOA_PUPDR_DEFAULT                 0x24000000
#define GPIOx_PUPDR_DEFAULT                 0
#define GPIOA_ODR_DEFAULT                   0
#define GPIOx_ODR_DEFAULT                   0
#define GPIOA_AFRL_DEFAULT                  0
#define GPIOA_AFRH_DEFAULT                  0
#define GPIOx_AFRL_DEFAULT                  0
#define GPIOx_AFRH_DEFAULT                  0

#define VAL_GPIOA_MODER             GPIOA_MODER_DEFAULT
#define VAL_GPIOA_OTYPER            GPIOA_OTYPER_DEFAULT
#define VAL_GPIOA_OSPEEDR           GPIOA_OSPEEDR_DEFAULT
#define VAL_GPIOA_PUPDR             GPIOA_PUPDR_DEFAULT
#define VAL_GPIOA_ODR               GPIOA_ODR_DEFAULT
#define VAL_GPIOA_AFRL              GPIOA_AFRL_DEFAULT
#define VAL_GPIOA_AFRH              GPIOA_AFRH_DEFAULT

#define VAL_GPIOB_MODER             GPIOx_MODER_DEFAULT
#define VAL_GPIOB_OTYPER            GPIOx_OTYPER_DEFAULT
#define VAL_GPIOB_OSPEEDR           GPIOx_OSPEEDR_DEFAULT
#define VAL_GPIOB_PUPDR             GPIOx_PUPDR_DEFAULT
#define VAL_GPIOB_ODR               GPIOx_ODR_DEFAULT
#define VAL_GPIOB_AFRL              GPIOx_AFRL_DEFAULT
#define VAL_GPIOB_AFRH              GPIOx_AFRH_DEFAULT

#define VAL_GPIOC_MODER             GPIOx_MODER_DEFAULT
#define VAL_GPIOC_OTYPER            GPIOx_OTYPER_DEFAULT
#define VAL_GPIOC_OSPEEDR           GPIOx_OSPEEDR_DEFAULT
#define VAL_GPIOC_PUPDR             GPIOx_PUPDR_DEFAULT
#define VAL_GPIOC_ODR               GPIOx_ODR_DEFAULT
#define VAL_GPIOC_AFRL              GPIOx_AFRL_DEFAULT
#define VAL_GPIOC_AFRH              GPIOx_AFRH_DEFAULT

#define VAL_GPIOD_MODER             GPIOx_MODER_DEFAULT
#define VAL_GPIOD_OTYPER            GPIOx_OTYPER_DEFAULT
#define VAL_GPIOD_OSPEEDR           GPIOx_OSPEEDR_DEFAULT
#define VAL_GPIOD_PUPDR             GPIOx_PUPDR_DEFAULT
#define VAL_GPIOD_ODR               GPIOx_ODR_DEFAULT
#define VAL_GPIOD_AFRL              GPIOx_AFRL_DEFAULT
#define VAL_GPIOD_AFRH              GPIOx_AFRH_DEFAULT

#define VAL_GPIOE_MODER             GPIOx_MODER_DEFAULT
#define VAL_GPIOE_OTYPER            GPIOx_OTYPER_DEFAULT
#define VAL_GPIOE_OSPEEDR           GPIOx_OSPEEDR_DEFAULT
#define VAL_GPIOE_PUPDR             GPIOx_PUPDR_DEFAULT
#define VAL_GPIOE_ODR               GPIOx_ODR_DEFAULT
#define VAL_GPIOE_AFRL              GPIOx_AFRL_DEFAULT
#define VAL_GPIOE_AFRH              GPIOx_AFRH_DEFAULT

#define VAL_GPIOF_MODER             GPIOx_MODER_DEFAULT
#define VAL_GPIOF_OTYPER            GPIOx_OTYPER_DEFAULT
#define VAL_GPIOF_OSPEEDR           GPIOx_OSPEEDR_DEFAULT
#define VAL_GPIOF_PUPDR             GPIOx_PUPDR_DEFAULT
#define VAL_GPIOF_ODR               GPIOx_ODR_DEFAULT
#define VAL_GPIOF_AFRL              GPIOx_AFRL_DEFAULT
#define VAL_GPIOF_AFRH              GPIOx_AFRH_DEFAULT

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
