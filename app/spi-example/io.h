#define GPIOA_DIR_OUT           0

/*
Using SPI1: 
      PA6: MISO
      PA5: CLK
      PA7: MOSI

 How to configure SPI port:
 1. Enable SPI in halconf
 2. Assign an SPI peripheral by STM32_SPI_USE_SPIx in mcuconf.h
 3. See board.h for declaration.

 SPI Parameters:
   (see also: https://www.playembedded.org/blog/stm32-spi-chibios/)
   * Clock polarity (CPOL)
   * Clock phase (CPHA)
   * Data Size 
   * MSB first or LSB first (default MSB first)


*/

#define SPI_CR2_DATASIZE_8BIT         SPI_CR2_DS_0
#define SPI_CR2_DATASIZE_16BIT        SPI_CR2_DS_1 
#define SPI_CR2_DATASIZE_24BIT        (SPI_CR2_DS_0 \
                                            | SPI_CR2_DS_1 \
                                            )


#define MOSI_MISO_CONNECTED TRUE
