Hardware:
---------
Use `cfg-f030x4` or `cfg-f103x8` in `aea.mk` to select the hardware.

BOARD INFO:
-----------
Pinout: see cfg/board.c/h and io.h


GET
-----------

```
git clone --recursive https://github.com/ceremcem/chibi-examples2
cd chibi-examples2
```

Flashing and Debugging
---------------------
Basic instructions:

1. Flashing                    : `make write`
2. Debugging                   : `make start-debugging`

For further instructions, see mcu-debug/README.md
