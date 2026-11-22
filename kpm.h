//kpm.h
// Header file containing function declarations for 4x4 matrix keypad interfacing

#include "types.h"

void InitKPM(void);          // Initializes keypad GPIO pins for row and column scanning
u8 ColScan(void);             // Checks whether any keypad column is active (key pressed)
u8 RowCheck(void);            // Identifies the row corresponding to the pressed key
u8 ColCheck(void);             // Identifies the column corresponding to the pressed key
u8 KeyScan(void);              // Detects the pressed key and returns its corresponding character
u32 ReadNum(void);             // Reads a multi-digit number from the keypad until '=' is pressed
void ReadNum2(u32 *,u8 *);     // Reads numeric input and returns the entered value and key status through pointers
