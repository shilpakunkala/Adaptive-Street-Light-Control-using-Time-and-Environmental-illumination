//adc_defines.h
// Header file containing ADC clock settings, register bit positions and pin configurations

// Processor clock frequency configuration
#define FOSC 12000000                 // External oscillator frequency (12 MHz)
#define CCLK (FOSC*5)                 // CPU clock frequency (60 MHz)
#define PCLK (CCLK/4)                 // Peripheral clock frequency (15 MHz)
#define ADC_CLK 3000000               // Required ADC clock frequency (3 MHz)

// Bit positions and values for ADC Control Register (ADCR)
#define CLKDIV_BITS        8          // Starting bit position of ADC clock divider (bits 8-15)
#define PDN_BIT            21         // Power-down bit to enable ADC operation
#define ADC_CONV_START_BIT 24         // Bit position used to start ADC conversion
#define CLKDIV_VAL ((PCLK/ADC_CLK)-1) // Calculates the ADC clock divider value

// Bit positions for ADC Data Register (ADDR)
#define DIGITAL_DATA_BITS  6          // Starting bit position of the 10-bit conversion result
#define DONE_BIT           31         // Conversion completion status bit

// Pin function selection values for ADC channels
#define AIN0_FUNC 0x00400000          // Configures P0.27 as ADC channel AIN0
#define AIN1_FUNC 0x01000000          // Configures P0.28 as ADC channel AIN1
#define AIN2_FUNC 0x04000000          // Configures P0.29 as ADC channel AIN2
#define AIN3_FUNC 0x10000000          // Configures P0.30 as ADC channel AIN3
