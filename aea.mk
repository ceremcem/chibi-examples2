# IMPORTANT: In order to debug, enable the following:
#USE_VERBOSE_COMPILE := yes

# Define project name here
PROJECT = ch

# Imported source files and paths.
CHIBIOS  := $(HOME)/ChibiOS
# use cfg-f030x4 or cfg-f103x8
CONFDIR  := ./cfg-f030x4
BUILDDIR := ./build
DEPDIR   := ./.dep

# Dynamically import all source files under ./include
SRCEXT := c
SRCDIR := $(CURDIR)/include
SRCS   := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCINC := $(shell find $(SRCDIR) -type d)
ALLCSRC += $(SRCS)
ALLINC += $(SRCINC)

# Software level IO configuration
#
APPDIR := $(CURDIR)/app
ALLCSRC += $(APPDIR)/io.c
ALLINC += $(APPDIR)

.DEFAULT_GOAL := all

# Take a note for the dependencies
CHIBIOS_BRANCH := $(shell cd ${CHIBIOS} && git branch | grep \* | cut -d ' ' -f2)
CHIBIOS_COMMIT := $(shell cd ${CHIBIOS} && git rev-parse HEAD)
GCC_VERSION := $(shell gcc --version | grep ^gcc | sed 's/^.* //g')

DEPS_DB := $(CURDIR)/dependencies.txt

PRE_MAKE_ALL_RULE_HOOK:
	@true > $(DEPS_DB)
	@echo "ChibiOS/$(CHIBIOS_BRANCH) $(CHIBIOS_COMMIT)" >> $(DEPS_DB)
	@echo "GCC $(GCC_VERSION)" >> $(DEPS_DB)

POST_MAKE_ALL_RULE_HOOK:

CLEAN_RULE_HOOK:
	@echo "Cleanup hook..."
	@echo
	@find $(CURDIR) -iname '*.gch' -exec rm {} \;
	@rm $(CURDIR)/_breakpoints.txt 2> /dev/null || true
	@rm $(CURDIR)/core 2> /dev/null || true

include ./mcu-debug/main.mk
