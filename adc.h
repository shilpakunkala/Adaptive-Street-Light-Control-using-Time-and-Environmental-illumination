//adc.c
// Header file for ADC (Analog-to-Digital Converter) interfacing functions

#include "types.h"

void Init_ADC(void);  // Initializes the ADC peripheral and configures ADC settings

void Read_ADC(u8 chNo,u16 *dVal,f32 *eAR);  // Reads the analog input from the specified ADC channel and returns the digital value and equivalent analog reading
