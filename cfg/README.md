# Peripheral and physical pin connections

See https://electronics.stackexchange.com/a/422280/20285

# Abstraction Layers 

1. board
2. chconf
3. halconf
4. mcuconf

### board.c/h

Settings directly related to the physical board. `boardInit()` function is for
initialization procedures of external IC(s).

### chconf.h

Responsible for operating system abstraction (RT) settings, such as

* Frequency,
* Enable/disable semaphores, mailbox, dynamic threads
* etc.

### halconf.h

Responsible for Hardware Abstraction Layer settings. You need to enable/disable
appropriate driver (PAL (+callbacks?), ADC, CAN, PWM, SERIAL, etc.) to use
them in the app code.

### mcuconf.h

Settings for the exact model of the MCU:

* Select internal/external clock
* Enable/disable on-chip peripherals (ADC, CAN, I2C, USART, PWM, ...)
* etc.
