# ADC example
# -----------
App	        := ./app/adc
Hardware    := ./hw/for-adc-app/STM32F030x4

# Basic example
# -----------
#App 		:= ./app/basic
#Hardware	:= ./hw/for-basic-app/f030x4-custom-breakout

# SPI example
# -----------
#App 		:= ./app/spi-example
#Hardware	:= ./hw/for-spi-example-app/f030x4-custom-breakout

# Uart example
# -----------
#App 		:= ./app/uart
#Hardware	:= ./hw/for-uart-app/f030x4-custom-breakout

Target			:= Debug
ChibiOS_Path 	:= $(HOME)/embedded/ChibiOS/ChibiOS
GCC_PATH		:= $(HOME)/embedded/gcc/gcc-arm-none-eabi-5_3-2016q1/bin

FLASHER				:= openocd
#GDB_ADDR			:= 192.168.56.103:4242
OPENOCD_INTERFACE 	:= stlink-v2.cfg
OPENOCD_TARGET 		:= stm32f0x.cfg