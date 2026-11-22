// Working of Adaptive Street Light Control System

#include <LPC21xx.h>       // Includes LPC21xx microcontroller register definitions
#include "types.h"         // Includes user-defined data type definitions
#include "adc.h"           // Includes ADC function declarations
#include "lcd.h"           // Includes LCD function declarations
#include "KPM.h"           // Includes keypad function declarations
#include "RTC.h"           // Includes RTC function declarations
#include "switching.h"     // Includes RTC and device editing functions
#include "lcd_defines.h"   // Includes LCD command definitions
#include "delay.h"         // Includes delay function declarations
#include "interrupt.h"     // Includes external interrupt declarations
#include "ldr.h"          // Includes LDR sensor function declarations
#include "ldr_lcd.h"       // Includes LDR display function declarations

#define LED 23             // Defines P0.23 as the streetlight LED control pin
#define LUX_THRESHOLD 300  // Defines the minimum light intensity threshold

s32 hour,min,sec;          // Stores the current RTC time
s32 date,month,year,day;   // Stores the current RTC date and day

u32 on_hr,on_min,off_hr,off_min; // Stores the configured streetlight ON and OFF timings
u32 cur_time;              // Declares a variable for storing the current time
s32 ontime;                // Stores the configured streetlight ON time
s32 offtime;               // Stores the configured streetlight OFF time

u8 choice;                 // Stores the user's menu selection

u16 tadc;                  // Stores the digital value received from the ADC
f32 tvolt,tresis,tlux;     // Stores the LDR voltage, resistance, and calculated light intensity

// Main function: Controls the overall working of the adaptive streetlight system
int main(void)
{
    IODIR0 |= (1<<LED);    // Configures P0.23 as an output pin

    IOSET0 = (1<<LED);     // Initially switches OFF the active-low LED

    InitLCD();             // Initializes the LCD
    StrLCD("LCD DISPLAY:"); // Displays the startup message
    delay_ms(200);         // Waits for 200 milliseconds
    CmdLCD(CLEAR_LCD);     // Clears the LCD

    InitKPM();             // Initializes the keypad

    RTC_Init();            // Initializes the internal RTC
    Init_LDR();            // Initializes the LDR sensor and ADC

    /*
       Set initial RTC values only for initial testing.
       After setting the time once, comment these lines.
    */

    //SetRTCTimeInfo(19,11,50);    // Sets the initial RTC time
    //SetRTCDateInfo(16,11,2026);  // Sets the initial RTC date
    //SetRTCDay(1);                // Sets the initial day of the week

    eint0_enable();        // Enables the external interrupt EINT0

    CmdLCD(CLEAR_LCD);     // Clears the LCD before entering the main loop

    while(1)               // Continuously executes the streetlight control system
    {
        if(request==1)     // Checks whether the external interrupt has occurred
        {
            request=0;     // Clears the interrupt request flag
            Main_Menu();   // Opens the main menu for RTC and device configuration
            CmdLCD(CLEAR_LCD); // Clears the LCD after returning from the menu
        }

        /* First display RTC time and date */

        Display_Time();    // Reads and displays the current RTC time and date
        delay_ms(1000);    // Waits for one second

        /* Read LDR and control LED */

        Read_LDR(&tadc,&tvolt,&tresis,&tlux); // Reads the LDR sensor and calculates light intensity

        // Checks the configured operating time and ambient light intensity
        if(((hour>=on_hr && min>=on_min)||(hour>=off_hr && min<off_min)) &&
           (tlux<LUX_THRESHOLD))
        {
            IOCLR0 = (1<<LED); // Switches ON the active-low streetlight LED
        }
        else
        {
            IOSET0 = (1<<LED); // Switches OFF the active-low streetlight LED
        }

        /* Display LUX and LED status */

        CmdLCD(CLEAR_LCD);  // Clears the LCD before displaying sensor information

        CmdLCD(GOTO_LINE1_POS0); // Moves the cursor to the first LCD line
        StrLCD("LDR:");          // Displays the LDR label
        U32LCD((u32)tlux);       // Displays the calculated light intensity

        CmdLCD(GOTO_LINE2_POS0); // Moves the cursor to the second LCD line
        StrLCD("LED:");          // Displays the streetlight status label

        // Checks the operating time and light intensity to display the LED status
        if(((hour>=on_hr && min>=on_min)||(hour>=off_hr && min<off_min)) &&
           (tlux<LUX_THRESHOLD))
        {
            StrLCD("ON");        // Displays that the streetlight is ON
        }
        else
        {
            StrLCD("OFF");       // Displays that the streetlight is OFF
        }

        delay_ms(1000);          // Waits for one second before the next iteration
    }
}