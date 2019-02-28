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

#define PULSE_OUT               DQ0
#define DIR_OUT                 DQ1
#define UPWARD_BUTTON           DI0
#define DOWNWARD_BUTTON         DI1
#define LOWER_LIMIT_SWITCH      DI2
#define UPPER_LIMIT_SWITCH      DI3


/*
 * Mass assignment of I/O ports.
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define CR_DEFAULT    0x44444444
#define ODR_DEFAULT    0x00000000

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
