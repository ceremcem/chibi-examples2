#include "hal.h"
#include "io.h"
#include "spi_helpers.h"

// master spi configuration 
SPIConfig test_spicfg = {
    circular: false,
    end_cb: NULL,
    ssport: GPIOA,

    // refer to "Bit definition for SPI_CR1 register" section of MCU header file
    cr1: (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_MSTR | SPI_CR1_BIDIOE), 
    cr2: (SPI_DW_8BIT)
};

void init_io(void){
    palSetPadMode(GPIOA, GPIOA_DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);
}
