static const ADCConfig adccfg = {.dummy = 0}; // dummy variable with compiler warning suppression enabled

static  ADCConversionGroup adccg = {
   // this 3 fields are common for all MCUs
      // set to TRUE if need circular buffer, set FALSE otherwise
      circular : FALSE,
      // number of channels
      num_channels : ADC_CH_COUNT,
      // callback function when conversion ends
      end_cb : NULL, // to be set in app
      //callback function when error appears
      error_cb : NULL,
      //look to datasheet for information about the registers
      // CR1 register content
      cr1 : 0,
      // CR2 register content
      cr2 : ADC_CR2_SWSTART | ADC_CR2_EXTTRIG | (7 << 17),//means single conversion mode
      // SMRP1 register content
      smpr1 : 0,
      // SMRP2 register content
      smpr2 : ((0b111)<<12)|((0b111)<<15)| ((0b111)<<18)|((0b111)<<21), /* sampling time */
      // SQR1 register content
      sqr1 : ((ADC_CH_COUNT - 1) << 20),
      // SQR2 register content
      sqr2 : 0,
      // SQR3 register content. We must select 1 channel
      // For example 6th channel
      // if we want to select more than 1 channel then simply
      // shift and logical-OR the values.
      // example: (ch 15 & ch 10) : (15 | (10 << 5))
      sqr3 : 4 | (5 << 5) | (6 << 10) | (7 << 15) /*register channels*/
};

 GPTConfig timer_config = {
  frequency:    80000U,
  callback:     NULL,  // to be set in app
  cr2:          0,
  dier:         0U
};
