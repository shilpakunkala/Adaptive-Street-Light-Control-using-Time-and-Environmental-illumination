//switching.c

#include "types.h"       // Includes user-defined data type definitions
#include "rtc.h"         // Includes RTC function declarations
#include "KPM.h"         // Includes keypad function declarations
#include "LCD.h"         // Includes LCD function declarations
#include <lpc21xx.h>     // Includes LPC21xx microcontroller register definitions

s8 ch;                   // Stores the key pressed on the keypad

extern u32 hour,min,sec,date,month,year,day; // Accesses RTC variables defined in another source file

// Allows the user to modify RTC time and date settings using the keypad
void Edit_RTC(void)
{
        CmdLCD(0x01);                  // Clears the LCD
        CmdLCD(0x80);                  // Moves the cursor to the first line
        StrLCD("1.H2.M3.S4.Dt");       // Displays RTC editing options
        CmdLCD(0xC0);                  // Moves the cursor to the second line
        StrLCD("5.Mon6.Y7.Dy8.E");     // Displays remaining options

        ch=KeyScan();                  // Reads the user's menu selection

        if(ch=='1'){
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0x80);         // Moves the cursor to the first line
                 StrLCD("Enter hour"); // Asks the user to enter the hour
                 hour=ReadNum();       // Reads the hour entered through the keypad
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0xC0);         // Moves the cursor to the second line
                 U32LCD(hour);         // Displays the entered hour

                 if(hour<24)           // Checks whether the hour is within the valid range
                     HOUR=hour;        // Updates the RTC hour register
        }
        else if(ch=='2'){
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0x80);         // Moves the cursor to the first line
                 StrLCD("Enter min");  // Asks the user to enter the minutes
                 min=ReadNum();       // Reads the entered minutes
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0xC0);         // Moves the cursor to the second line
                 U32LCD(min);         // Displays the entered minutes

                 if(min<60)            // Checks whether the minutes are valid
                        MIN=min;       // Updates the RTC minute register
        }
        else if(ch=='3'){
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0x80);         // Moves the cursor to the first line
                 StrLCD("Enter sec");  // Asks the user to enter the seconds
                 sec=ReadNum();       // Reads the entered seconds
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0xC0);         // Moves the cursor to the second line
                 U32LCD(sec);         // Displays the entered seconds

                 if(sec<60)            // Checks whether the seconds are valid
                        SEC=sec;       // Updates the RTC second register
        }
        else if(ch=='4'){
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0x80);         // Moves the cursor to the first line
                 StrLCD("Enter date"); // Asks the user to enter the date
                 date=ReadNum();      // Reads the entered date
                 CmdLCD(0x01);         // Clears the LCD
                 CmdLCD(0xC0);         // Moves the cursor to the second line
                 U32LCD(date);        // Displays the entered date

                 if(date<=31 && date!=0) // Checks whether the date is within the basic valid range
                        DOM=date;        // Updates the RTC date register
        }
        else if(ch=='5'){
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0x80);           // Moves the cursor to the first line
                 StrLCD("Enter month");  // Asks the user to enter the month
                 month=ReadNum();       // Reads the entered month
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0xC0);           // Moves the cursor to the second line
                 U32LCD(month);         // Displays the entered month

                 if(month<13 && month!=0) // Checks whether the month is between 1 and 12
                        MONTH=month;      // Updates the RTC month register
        }
        else if(ch=='6'){
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0x80);           // Moves the cursor to the first line
                 StrLCD("Enter year");   // Asks the user to enter the year
                 year=ReadNum();        // Reads the entered year
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0xC0);           // Moves the cursor to the second line
                 U32LCD(year);          // Displays the entered year
                 YEAR=year;             // Updates the RTC year register
        }
        else if(ch=='7'){
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0x80);           // Moves the cursor to the first line
                 StrLCD("Enter day");    // Asks the user to enter the day of the week
                 day=KeyScan();         // Reads the day selection from the keypad
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0xC0);           // Moves the cursor to the second line
                 U32LCD(day);           // Displays the entered day

                 if(DOW<7)              // Checks whether the current day register is in range
                        DOW=day;         // Updates the RTC day-of-week register
        }
        else{
                 CmdLCD(0x01);           // Clears the LCD
                 CmdLCD(0x80);           // Moves the cursor to the first line
                 StrLCD("Return to main"); // Displays the return message
                 return;                 // Exits the RTC editing function
        }
}

// Accesses the device ON and OFF time variables defined in another source file
extern u32 on_hr,on_min,off_hr,off_min;

// Allows the user to configure the streetlight ON and OFF timings
void Edit_Device(s32 *ontime,s32 *offtime)
{
         CmdLCD(0x01);                  // Clears the LCD
         CmdLCD(0x80);                  // Moves the cursor to the first line
         StrLCD("1.Ontime 3.Exit");     // Displays the ON-time and exit options
         CmdLCD(0xC0);                  // Moves the cursor to the second line
         StrLCD("2.Offtime");           // Displays the OFF-time option

         ch=KeyScan();                  // Reads the user's menu selection

         if(ch=='1')
         {
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0x80);           // Moves the cursor to the first line
                StrLCD("On_Hr");        // Asks the user to enter the ON hour
                on_hr=ReadNum();        // Reads the ON hour
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0xC0);           // Moves the cursor to the second line
                U32LCD(on_hr);          // Displays the ON hour
                delay_ms(100);          // Adds a short delay

                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0x80);           // Moves the cursor to the first line
                StrLCD("On_Min");       // Asks the user to enter the ON minutes
                on_min=ReadNum();       // Reads the ON minutes
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0xC0);           // Moves the cursor to the second line
                U32LCD(on_min);         // Displays the ON minutes
                delay_ms(100);          // Adds a short delay
         }
         else if(ch=='2'){
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0x80);           // Moves the cursor to the first line
                StrLCD("1.Off_Hr");     // Asks the user to enter the OFF hour
                off_hr=ReadNum();       // Reads the OFF hour
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0xC0);           // Moves the cursor to the second line
                U32LCD(off_hr);         // Displays the OFF hour
                delay_ms(100);          // Adds a short delay

                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0x80);           // Moves the cursor to the first line
                StrLCD("Off_Min");      // Asks the user to enter the OFF minutes
                off_min=ReadNum();      // Reads the OFF minutes
                CmdLCD(0x01);           // Clears the LCD
                CmdLCD(0xC0);           // Moves the cursor to the second line
                U32LCD(off_min);        // Displays the OFF minutes
                delay_ms(100);          // Adds a short delay
         }
         else{
              CmdLCD(0x01);             // Clears the LCD
              CmdLCD(0x80);             // Moves the cursor to the first line
              // StrLCD("Return to main"); // Optional return message
              return;                   // Exits the device editing function
         }
}