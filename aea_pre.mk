# Define project name here
PROJECT = ch

# Imported source files and paths.
CHIBIOS  := $(HOME)/ChibiOS
CONFDIR  := ./cfg
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
# ./io.c
ALLCSRC += io.c
