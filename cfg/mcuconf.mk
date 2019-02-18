# Define linker script file here
include $(CHIBIOS)/os/hal/ports/STM32/STM32F1xx/platform.mk

# Startup files.
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f1xx.mk

LDSCRIPT= $(STARTUPLD)/STM32F103xB.ld
