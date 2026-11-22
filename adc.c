//adc.c
// ADC driver implementation for reading analog signals using LPC2129

#include "types.h"
#include <LPC21xx.h>
#include "adc_defines.h"
#include "delay.h"

void Init_ADC(void)
{
    // Configure P0.27 to P0.30 pins for ADC channel functions
    PINSEL1&=~(0xFF<<((27-16)*2));

    // Select ADC functions for AIN0, AIN1, AIN2 and AIN3
    PINSEL1|=AIN0_FUNC|
             AIN1_FUNC|
             AIN2_FUNC|
             AIN3_FUNC;

    // Enable ADC peripheral and configure ADC clock divider
    ADCR|=(1<<PDN_BIT)|(CLKDIV_VAL<<CLKDIV_BITS);
}

void Read_ADC(u8 chNo,u16 *dVal,f32 *eAR)
{
    // Clear previous ADC channel selection and conversion settings
    ADCR&=0xFFFFFF00;

    // Select the required ADC channel and start conversion
    ADCR|=(1<<ADC_CONV_START_BIT)|(1<<chNo);

    // Wait for the ADC conversion to complete
    delay_us(3);

    // Check the DONE bit until conversion is completed
    while(((ADDR>>DONE_BIT)&1)==0);

    // Stop ADC conversion
    ADCR&=~(1<<ADC_CONV_START_BIT);

    // Extract the 10-bit digital conversion result
    *dVal=((ADDR>>DIGITAL_DATA_BITS)&1023);

    // Convert the digital value into equivalent analog voltage
    *eAR=*dVal*(3.3/1023);
}
