# Description 

This application does:

* If `MOSI` and `MISO` short circuited (loopback mode):
    * Send `01`, `12`, ..., `90` strings via SPI_MOSI pin
    * Receive `01`, `12`, ... `90` via SPI_MISO pin
* Else
    * Send `A0`, `A1`, ..., `A9` strings via SPI_MOSI pin

# Development Environment 

1. Logic Analyzer Connection 
    1. Create an analyzer 
    2. Set "Enable" pin as "None" in analyzer settings

# Pinout

Refer to `$HARDWARE/board.{h,c}` and `io.{h,c}` for pinout settings.
