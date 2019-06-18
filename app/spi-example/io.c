#include "hal.h"
#include "io.h"


/**/
// master spi configuration 
SPIConfig test_spicfg = {
    circular: false,
    end_cb: NULL,
    ssport: GPIOA,
    //ssline: ???, // depends on SPI_SELECT_MODE_LINE

    // refer to "Bit definition for SPI_CR1 register" section of MCU header file
    cr1: (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_MSTR | SPI_CR1_BIDIOE), 
    cr2: (SPI_CR2_DATASIZE_8BIT)
};

/** /
const SPIConfig test_spicfg = {
  false,
  NULL,
  GPIOA,
  4, //GPIOA_SPI1NSS,
  SPI_CR1_BR_2 | SPI_CR1_BR_1,
  0
};
/**/

void init_io(void){
    palSetPadMode(GPIOA, GPIOA_DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);
}
