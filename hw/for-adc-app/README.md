# Folder Structure 

Kernel configuration files:
* chconf.h
* halconf.h 

Hardware declaration folder:
 * my-board
     * board.c
     * board.h
     * board.mk
     * mcuconf.h
     * mcuconf.mk


# How to setup ADC Input:

1. Select an appropriate pin using datasheet: GPIOA_1 is ADC_IN1
2. Hardware setup:
    halconf.h -> HAL_USE_ADC -> TRUE 
    mcuconf.h -> STM32_ADC_USE_ADC1 -> TRUE 
    board.h -> Setup the analog mode by PIN_MODE_ANALOG() macro