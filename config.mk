#APP_NAME	:= basic
#APP_NAME	:= spi-example
APP_NAME	:= uart

Target      := Debug
App 		:= ./app/$(APP_NAME)
Hardware    := ./hw/for-$(APP_NAME)-app/f030x4-custom-breakout
GCC_Path    := $(HOME)/gcc/gcc-arm-none-eabi-5_3-2016q1/bin
