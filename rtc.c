//rtc.c
// RTC driver implementation for time and date management using LPC2129

#include "LCD.h"
#include <lpc21xx.h>
#include "lcd_defines.h"

// Oscillator and processor clock configuration
#define FOSC 12000000                 // External oscillator frequency (12 MHz)
#define CCLK (5*FOSC)                 // CPU clock frequency (60 MHz)
#define PCLK (CCLK/4)                 // Peripheral clock frequency (15 MHz)

// RTC prescaler values for generating a 1 Hz clock
#define PREINT_VAL ((int)(PCLK/32768)-1) // Integer part of RTC prescaler
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768)) // Fractional part of RTC prescaler

// RTC control register bit definitions
#define RTC_ENABLE (1<<0)             // Enables the RTC peripheral
#define RTC_RESET (1<<1)              // Resets the RTC counters

#define RTC_CLKSRC (1<<4)              // Selects external RTC clock source

#define CPU_LPC2148                  // Selects LPC2148 RTC configuration

// Lookup table containing abbreviated names of the days of the week
char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

void RTC_Init(void)
{
    // Disable and reset the RTC before initialization if required
    // CCR=RTC_RESET;

    #ifndef CPU_LPC2148
    // Configure integer and fractional prescaler values for RTC clock generation
    PREINT=PREINT_VAL;
    PREFRAC=PREFRAC_VAL;

    // Enable the internal RTC clock configuration for LPC2129
    CCR=RTC_ENABLE;
    #else

    // Enable the RTC using the external clock source for LPC2148
    CCR=RTC_ENABLE | RTC_CLKSRC;
    #endif
}

void SetRTCTimeInfo(u32 hour,u32 minute,u32 second)
{
    // Set the RTC hour, minute and second registers
    HOUR=hour;
    MIN=minute;
    SEC=second;
}

void GetRTCTimeInfo(s32 *hour,s32 *minute,s32 *second)
{
    // Read RTC hour, minute and second values through pointers
    *hour=HOUR;
    *minute=MIN;
    *second=SEC;
}

void DisplayRTCTime(u32 hour,u32 minute,u32 second)
{
    // Move LCD cursor to the beginning of the first line
    CmdLCD(GOTO_LINE1_POS0);

    // Display hour in HH format
    CharLCD(hour/10+48);
    CharLCD(hour%10+48);
    CharLCD(':');

    // Display minutes in MM format
    CharLCD(minute/10+48);
    CharLCD(minute%10+48);
    CharLCD(':');

    // Display seconds in SS format
    CharLCD(second/10+48);
    CharLCD(second%10+48);
}

void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
    // Set the RTC date, month and year registers
    DOM=date;
    MONTH=month;
    YEAR=year;
}

void GetRTCDateInfo(s32 *date,s32 *month,s32 *year)
{
    // Read RTC date, month and year values through pointers
    *date=DOM;
    *month=MONTH;
    *year=YEAR;
}

void DisplayRTCDate(u32 date,u32 month,u32 year)
{
    // Move LCD cursor to the beginning of the second line
    CmdLCD(GOTO_LINE2_POS0);

    // Display date in DD/MM/YYYY format
    CharLCD(date/10+48);
    CharLCD(date%10+48);
    CharLCD('/');

    // Display month in MM format
    CharLCD(month/10+48);
    CharLCD(month%10+48);
    CharLCD('/');

    // Display the complete year
    U32LCD(year);
}

void SetRTCDay(u32 dow)
{
    // Set the day of the week in the RTC register
    DOW=dow;
}

void GetRTCDay(s32 *dow)
{
    // Read the current day of the week through a pointer
    *dow=DOW;
}

void DisplayRTCDay(u32 day)
{
    // Move LCD cursor to the day display position on the first line
    CmdLCD(GOTO_LINE1_POS0+10);

    // Display the day name if the day index is between 0 and 6
    if(day<7)
        StrLCD(week[day]);
}
