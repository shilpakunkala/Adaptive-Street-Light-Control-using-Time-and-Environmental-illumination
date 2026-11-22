//lcd.h
// Header file for LCD interfacing functions

#include "types.h"

void WriteLCD(u8 byte);              // Sends a data byte to the LCD
void CmdLCD(u8 cmd);                  // Sends a command to the LCD
void InitLCD(void);                  // Initializes the LCD
void CharLCD(u8 asciiVal);            // Displays a single character on the LCD
void StrLCD(s8 *);                    // Displays a string on the LCD
void U32LCD(u32);                     // Displays an unsigned 32-bit integer
void S32LCD(s32);                     // Displays a signed 32-bit integer
void F32LCD(f32,u8 nDP);              // Displays a floating-point number with specified decimal places
void BuildCGRAM(const u8 *p,u8 nBytes); // Creates custom characters in LCD CGRAM
