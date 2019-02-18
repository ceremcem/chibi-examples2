#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * MCU type, supported types are defined in ChibiOS/os/hal/platforms/hal_lld.h.
 */
//#define STM32F103xB
#define STM32F103xB // STM32F030F4P6

/*
 * IO pins assignments.
 */
/* GPIOA */
#define PULSE_OUT               0u
#define DIR_OUT                 1u
#define UPWARD_BUTTON           2u
#define DOWNWARD_BUTTON         3u
#define LOWER_LIMIT_SWITCH      4u
#define UPPER_LIMIT_SWITCH      5u

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
