//kpm.c
// Keypad driver implementation for interfacing a 4x4 matrix keypad with LPC2129

#include <LPC21xx.h>

#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
#include "LCD.h"
#include "lcd_defines.h"

// Lookup table containing characters assigned to each keypad button
u8 kpmLUT[4][4]=
{
    {'7','8','9','/'},
    {'4','5','6','X'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

void InitKPM(void)
{
    // Configure keypad row pins as output
    WRITENIBBLE(IODIR1,ROW0,15);

    // Configure keypad column pins as input
    WRITENIBBLE(IODIR1,COL0,0);

    // Ground all keypad rows initially for key detection
    WRITENIBBLE(IOPIN1,ROW0,0);
}

u8 ColScan(void)
{
    u8 t;

    // Check whether any keypad column is pulled low by a pressed key
    t=(READNIBBLE(IOPIN1,COL0)<15)?0:1;

    return t;
}

u8 RowCheck(void)
{
    u8 r;

    // Activate each row one at a time to identify the pressed key row
    for(r=0;r<4;r++)
    {
        WRITENIBBLE(IOPIN1,ROW0,~(1<<r));

        // Check whether any column becomes low for the selected row
        if(!ColScan())
            break;
    }

    // Ground all rows after completing row detection
    WRITENIBBLE(IOPIN1,ROW0,0);

    return r;
}

u8 ColCheck(void)
{
    u8 c;

    // Scan each column to identify the pressed key column
    for(c=0;c<4;c++)
    {
        if(READBIT(IOPIN1,COL0+c)==0)
            break;
    }

    return c;
}

u8 KeyScan(void)
{
    u8 r,c,keyV;

    // Wait until a key is pressed
    while(ColScan());

    // Identify the row and column of the pressed key
    r=RowCheck();
    c=ColCheck();

    // Check whether the detected row and column are valid
    if(r>=4 || c>=4)
        return 0;

    // Retrieve the corresponding key character from the lookup table
    keyV=kpmLUT[r][c];

    // Wait until the pressed key is released
    while(ColScan()==0);

    return keyV;
}

u32 ReadNum(void)
{
    u32 keyV;
    u32 sum=0;

    // Continuously read keypad input until the user confirms the number
    while(1)
    {
        keyV=KeyScan();

        // Check whether the pressed key is a numeric digit
        if(keyV>='0' && keyV<='9')
        {
            // Build the number by appending the newly entered digit
            sum=(sum*10)+(keyV-'0');

            // Display the entered number on the second LCD line
            CmdLCD(GOTO_LINE2_POS0);
            U32LCD(sum);
        }
        else if(keyV=='C')
        {
            // Reset the entered number when clear key is pressed
            sum=0;

            // Clear the LCD display
            CmdLCD(CLEAR_LCD);
        }
        else if(keyV=='=')
        {
            // Return the entered number when the confirmation key is pressed
            return sum;
        }
    }
}
