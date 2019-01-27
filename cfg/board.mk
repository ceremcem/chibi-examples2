# List of all the board related files.
#BOARDSRC = ${CHIBIOS}/os/hal/boards/ST_NUCLEO64_F103RB/board.c
BOARDSRC = #$(CURDIR)/board.c

# Required include directories
BOARDINC = $(CURDIR)

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
