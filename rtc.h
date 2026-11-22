
// Header file containing function declarations for RTC time and date management

#include "types.h"

void RTC_Init(void);                                      // Initializes the RTC peripheral and configures its clock

void SetRTCTimeInfo(u32 hour,u32 minute,u32 second);       // Sets the RTC hour, minute and second values

void GetRTCTimeInfo(s32 *hour,s32 *minute,s32 *second);    // Reads the current hour, minute and second values

void DisplayRTCTime(u32 hour,u32 minute,u32 second);       // Displays the current time on the LCD in HH:MM:SS format

void SetRTCDateInfo(u32 date,u32 month,u32 year);          // Sets the RTC date, month and year values

void GetRTCDateInfo(s32 *date,s32 *month,s32 *year);      // Reads the current date, month and year values

void DisplayRTCDate(u32 date,u32 month,u32 year);          // Displays the date on the LCD in DD/MM/YYYY format

void SetRTCDay(u32 dow);                                  // Sets the day of the week in the RTC

void GetRTCDay(s32 *dow);                                 // Reads the current day of the week

void DisplayRTCDay(u32 day);                              // Displays the abbreviated day name on the LCD
