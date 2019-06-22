# Description 

The application "basic" does:

* Blink (generate square wave) on GPIOA_DIR_OUT
* Write the inverse boolean state of GPIOA_TEST_INPUT to GPIOA_TEST_OUTPUT (via polling)
* Write the inverse boolean state of GPIOA_TEST_INPUT_2 to GPIOA_TEST_OUTPUT_2 (via callbacks)
* Generate PWM output on TIM1_CH3 pin with a ramp frequency on startup

The application "spi-example" does:

* If `MOSI` and `MISO` short circuited (loopback mode):
    * Send `01`, `12`, ..., `90` strings via SPI_MOSI pin
    * Receive `01`, `12`, ... `90` via SPI_MISO pin
* Else
    * Send `A0`, `A1`, ..., `A9` strings via SPI_MOSI pin


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