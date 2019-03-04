#include "hal.h"
#include "io.h"

void init_io(void){
      palSetPadMode(GPIOA, DIR_OUT, PAL_MODE_OUTPUT_PUSHPULL);
}
