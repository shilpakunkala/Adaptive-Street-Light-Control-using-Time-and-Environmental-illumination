//ldr.h
#include <LPC21xx.h>          // Includes LPC21xx microcontroller register definitions
#include "types.h"            // Includes user-defined data type definitions

void Init_ADC(void);          // Initializes the ADC peripheral
void Read_ADC(u8 chNo, u16 *dVal, f32 *eAR);  // Reads ADC value and calculates the corresponding voltage
void Read_LDR(u16 *tadc, f32 *tvolt, f32 *tresis, f32 *tlux); // Reads LDR data and calculates voltage, resistance, and light intensity