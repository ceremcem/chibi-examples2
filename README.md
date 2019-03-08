Hardware:
---------
See [./Hardware](./Hardware) for target hardware.

BOARD INFO:
-----------
Pinout: see cfg-xx/board.c/h and app/io.h for pinouts


Usage
-----------

```
git clone --recursive https://github.com/ceremcem/chibi-examples2
cd chibi-examples2
# either:
make write # to flash only, or
make start-debugging # to start debugging with GDB command line client.

# TIP: in GDB prompt, use the "cheatsheet" command.
```

For further instructions, see [mcu-debug/README.md](./mcu-debug/README.md).
