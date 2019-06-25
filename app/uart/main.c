#include "main.h"

static const uint8_t buffer[6] = "hello\n";

static THD_WORKING_AREA(packet_sender_wa, 256);
static THD_FUNCTION(packet_sender, ptr)
{
    (void) ptr;
    while(TRUE) 
    {
      sdWrite(&SD1, buffer, sizeof(buffer)); //send packet over serial bus
      //no need to this wait we hope
      uint8_t rxbuffer[10]; 
      sdReadTimeout(&SD1, rxbuffer, sizeof(rxbuffer), 100); // TODO: what is the TIMEOUT unit?
      sdWrite(&SD1, rxbuffer, sizeof(rxbuffer));   
      chThdSleepMilliseconds(800);
    }
}

int main(void) {
  halInit();
  chSysInit();
  init_io();

  sdStart(&SD1, &usartConfig);

  chThdCreateStatic(packet_sender_wa, sizeof(packet_sender_wa), NORMALPRIO, packet_sender, NULL);

  while (true) {
    chThdSleepMilliseconds(1000); //// debugger
  }
}
