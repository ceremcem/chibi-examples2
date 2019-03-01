include $(CHIBIOS)/os/hal/ports/STM32/STM32F1xx/platform.mk
MCU  = cortex-m3
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f1xx.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk
LDSCRIPT= $(STARTUPLD)/STM32F103xB.ld
