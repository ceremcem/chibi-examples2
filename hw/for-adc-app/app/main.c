#include "main.h"

int main(void) {
    halInit();
    chSysInit();
    init_io();
    adcStart(&ADCD1, NULL);
    
    adcStartConversion(&ADCD1, &adcgrpcfg1, samples_buf1, ADC_BUF_DEPTH);
    // ---------------- APP CODE STARTS HERE -------------------------

}
void adcReadCallback1(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
    (void) adcp;
    (void) n;
    for (uint8_t i = 0; i < ADC_CH_NUM; i++){
        // do something with buffer[i]
    }
}
