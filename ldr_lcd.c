#include <LPC21xx.h>       // Includes LPC21xx microcontroller register definitions
#include "ldr.h"          // Includes LDR function declarations
#include "adc.h"           // Includes ADC function declarations
#include "lcd.h"           // Includes LCD function declarations
#include "lcd_defines.h"   // Includes LCD command and pin definitions
#include "delay.h"         // Includes delay function declarations
#include "types.h"         // Includes user-defined data type definitions

extern u16 tadc;           // Accesses the ADC digital value defined in another source file
extern f32 tvolt;         // Accesses the voltage calculated from the ADC value
extern f32 tresis,tlux;   // Accesses the calculated LDR resistance and light intensity


// Reads the LDR sensor values and displays the calculated light intensity
void Display_LDR(void)
{
    Read_LDR(&tadc,&tvolt,&tresis,&tlux); // Reads ADC value, voltage, resistance, and lux

    CmdLCD(GOTO_LINE2_POS0);              // Moves the LCD cursor to the beginning of the second line
    StrLCD("Lux:");                       // Displays the light intensity label

    U32LCD((u32)tlux);                    // Converts the lux value to an integer and displays it

    StrLCD("       ");                   // Clears any remaining characters from the previous display
}
