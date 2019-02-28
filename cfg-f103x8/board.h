#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * MCU type, supported types are defined in ChibiOS/os/hal/platforms/hal_lld.h.
 */
#define STM32F103xB

/*
 * IO pins assignments.
 */
/* GPIOA */
#define PA0_OUTPUT              0

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
 #define PIN_MODE_ANALOG(n)         (0x00 << ((n) * 2U))
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))

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
 * Port A setup. (see STM32F103 Reference, 9.2 GPIO registers)
 */
//#define VAL_GPIOACRL            0x00008B44      /*  PA7...PA0 */
//#define VAL_GPIOACRH            0x8882BBBB      /* PA15...PA8 */
//#define VAL_GPIOAODR            0x00000000
#define VAL_GPIOACRL            0x44444444      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x44444444      /* PA15...PA8 */
#define VAL_GPIOAODR            0x00000000



/*
 * Port B setup.
 * Everything output push pull
 */
#define VAL_GPIOBCRL            0x22222222      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x22222222      /* PB15...PB8 */
#define VAL_GPIOBODR            0x00000000

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
