# Description 

This repository contains the basic ChibiOS examples that uses [`chibi-project`][1] as its development environment. 

Refer to `app/*/README.md` for application specific descriptions. 

[1]: https://github.com/ceremcem/chibi-project

# Hardware

Refer to `config.mk` for selected target hardware.


# Pinout

Refer to `HARDWARE/board.{h,c}` and `APP/io.{h,c}` for pinout settings.


# Development

```
git clone --recursive https://github.com/ceremcem/chibi-examples2
cd chibi-examples2
# either:
# -------
make write    # to flash only, or
make debug    # to start debugging with GDB command line client.

# TIP: in GDB prompt, use the "cheatsheet" command.
```

> NOTICE: Refer to `app/*/README.md` if exists.

For further debugging related instructions, see [mcu-debug/README.md](https://github.com/aktos-io/mcu-debug).


# Test Log

* 13.06.2019 on f030f4