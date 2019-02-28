#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * MCU type
 */
#define STM32F103xB

// See pal_default_config in board.c in order to see what variables to set

/*
 * IO pins assignments.
 */
/* GPIOA */
#define DQ0                     0
#define DQ1                     1
#define DI0                     2
#define DI1                     3
#define DI2                     4
#define DI3                     5

// GPIOB
#define PWM0                    1

/*
 * I/O Assignment
 *
 * Refer to board.c/hw_init_io for additional settings
 *
 * Please refer to the STM32 Reference Manual for details.
 */
#define CR_DEFAULT    0x44444444
#define ODR_DEFAULT    0x00000000

#define GPIO_MODE_INPUT             0b00
#define GPIO_MODE_OUTPUT_10MHZ      0b01
#define GPIO_MODE_OUTPUT_2MHZ       0b10
#define GPIO_MODE_OUTPUT_50MHZ      0b11

// valid only GPIO_MODE is 0
#define GPIO_CNF_ANALOG             (0b00 << 2)
#define GPIO_CNF_INPUT_FLOATING     (0b01 << 2)
#define GPIO_CNF_INPUT_PUPD         (0b10 << 2)
// valid only GPIO_MODE > 0
#define GPIO_CNF_OUTPUT_PP          (0b00 << 2)
#define GPIO_CNF_OUTPUT_OD          (0b01 << 2)
#define GPIO_CNF_AF_PP              (0b10 << 2)
#define GPIO_CNF_AF_OD              (0b11 << 2)

// GPIO configurations for device peripherals
#define PWM_CONF_50MHZ              (GPIO_CNF_AF_PP | GPIO_MODE_OUTPUT_50MHZ)

#define PIN_NUM(x)                  (4 * x % 8)     // 4 bits per pin config

/*
 * Mass settings
 */
// Port A setup
#define VAL_GPIOACRL            CR_DEFAULT      /*  PA7...PA0 */
#define VAL_GPIOACRH            CR_DEFAULT      /* PA15...PA8 */
#define VAL_GPIOAODR            ODR_DEFAULT

// Port B setup
#define VAL_GPIOBCRL            CR_DEFAULT      /*  PA7...PA0 */
#define VAL_GPIOBCRH            CR_DEFAULT      /* PA15...PA8 */
#define VAL_GPIOBODR            ODR_DEFAULT

// Port C setup
#define VAL_GPIOCCRL            CR_DEFAULT      /*  PA7...PA0 */
#define VAL_GPIOCCRH            CR_DEFAULT      /* PA15...PA8 */
#define VAL_GPIOCODR            ODR_DEFAULT

// Port D setup
#define VAL_GPIODCRL            CR_DEFAULT      /*  PA7...PA0 */
#define VAL_GPIODCRH            CR_DEFAULT      /* PA15...PA8 */
#define VAL_GPIODODR            ODR_DEFAULT

// Port E setup
#define VAL_GPIOECRL            CR_DEFAULT      /*  PA7...PA0 */
#define VAL_GPIOECRH            CR_DEFAULT      /* PA15...PA8 */
#define VAL_GPIOEODR            ODR_DEFAULT


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
