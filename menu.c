#include <LPC21xx.h>       // Includes LPC21xx microcontroller register definitions
#include "types.h"         // Includes user-defined data type definitions
#include "adc.h"           // Includes ADC function declarations
#include "lcd.h"           // Includes LCD function declarations
#include "KPM.h"           // Includes keypad function declarations
#include "RTC.h"           // Includes RTC function declarations
#include "switching.h"     // Includes RTC and device editing function declarations
#include "lcd_defines.h"   // Includes LCD command definitions
#include "delay.h"         // Includes delay function declarations
#include "interrupt.h"     // Includes external interrupt declarations
#include "ldr.h"          // Includes LDR display and threshold function declarations

extern s32 ontime;         // Accesses the streetlight ON time defined in another source file
extern s32 offtime;        // Accesses the streetlight OFF time defined in another source file
extern u8 choice;          // Accesses the variable that stores the selected menu option
extern s32 hour,min,sec;   // Accesses RTC hour, minute, and second variables
extern s32 date,month,year,day; // Accesses RTC date, month, year, and day variables

// Reads and displays the current RTC time, date, and day
void Display_Time(void)
{
    GetRTCTimeInfo(&hour,&min,&sec);       // Reads the current hour, minute, and second
    GetRTCDateInfo(&date,&month,&year);    // Reads the current date, month, and year
    GetRTCDay(&day);                       // Reads the current day of the week

    DisplayRTCTime(hour,min,sec);          // Displays the RTC time on the LCD
    DisplayRTCDay(day);                    // Displays the day of the week on the LCD
    DisplayRTCDate(date,month,year);       // Displays the RTC date on the LCD
}

// Displays the main menu and handles the user's selection
void Main_Menu(void)
{
    while(1)                               // Repeats the menu until the user selects an option
    {
        CmdLCD(CLEAR_LCD);                 // Clears the LCD
        CmdLCD(GOTO_LINE1_POS0);           // Moves the cursor to the first line
        StrLCD("1.RTC 2.DEVICE");          // Displays RTC and device configuration options

        CmdLCD(GOTO_LINE2_POS0);           // Moves the cursor to the second line
        StrLCD("3.EXIT");                  // Displays the exit option

        choice=KeyScan();                  // Reads the user's menu selection

        while(ColScan()==0);               // Waits until the pressed key is released

        switch(choice)                     // Checks the selected menu option
        {
            case '1':
                Edit_RTC();                // Opens the RTC editing menu
                return;                    // Returns from the main menu

            case '2':
                Edit_Device(&ontime,&offtime); // Opens the streetlight timing configuration menu
                return;                    // Returns from the main menu

            case '3':
                return;                    // Exits the main menu

            default:
                CmdLCD(CLEAR_LCD);         // Clears the LCD
                StrLCD("Invalid Choice");  // Displays an error message for an invalid selection
                delay_s(1);                // Waits for one second
                break;                     // Restarts the menu loop
        }
    }
   
    
}