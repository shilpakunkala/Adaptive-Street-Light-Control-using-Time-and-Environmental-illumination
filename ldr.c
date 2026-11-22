//lcd.c
// LDR sensor driver implementation using ADC for measuring light intensity

#include <LPC21xx.h>
#include "adc.h"
#include "types.h"
#include <math.h>

// Global variables to store ADC digital value and equivalent analog voltage
u16 dval;
f32 eAR;

// Initialize LDR sensor by configuring the ADC peripheral
void Init_LDR(void)
{
    // Initialize ADC for reading the LDR analog output
    Init_ADC();
}

void Read_LDR(u16 *tadc,f32 *tvolt,f32 *tresis,f32 *tlux)
{
    // Read ADC channel 1 and obtain digital value and equivalent voltage
    Read_ADC(1, &dval, &eAR);

    // Store the ADC digital value and voltage in the output parameters
    *tadc = dval;
    *tvolt = eAR;

    // Calculate LDR resistance using the voltage divider formula
    *tresis = (10000.0f * (*tvolt)) / (3.3f - (*tvolt));

    // Calculate light intensity only when the resistance is positive
    if(*tresis > 0)
    {
        // Estimate light intensity in lux using the LDR characteristics
        *tlux = 10.0f * pow((12000.0f / (*tresis)), (1.0f / 0.7f));
    }
    else
    {
        // Set light intensity to zero when resistance is invalid
        *tlux = 0;
    }
}
