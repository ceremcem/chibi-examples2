include $(CHIBIOS)/os/hal/ports/STM32/STM32F1xx/platform.mk

# Startup files.
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f1xx.mk

# RTOS file
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v7m.mk

# Linker script
LDSCRIPT= $(STARTUPLD)/STM32F103xB.ld
