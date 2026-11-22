//lcd.c
// LCD driver implementation for interfacing 16x2 LCD with LPC2129

#include <LPC21xx.h>
#include "lcd_defines.h"
#include "defines.h"
#include "types.h"
#include "delay.h"

void WriteLCD(u8 byte)
{
    // Select write operation by making RW pin low
    IOCLR0=1<<LCD_RW;

    // Place the data byte on LCD data pins D0 to D7
    WRITEBYTE(IOPIN0,LCD_DATA,byte);

    // Generate enable pulse to latch the data into LCD
    IOSET0=1<<LCD_EN;
    delay_us(1);
    IOCLR0=1<<LCD_EN;

    // Wait for LCD to complete the write operation
    delay_ms(2);
}

void CmdLCD(u8 cmd)
{
    // Select LCD command register by making RS pin low
    IOCLR0=1<<LCD_RS;

    // Send the command to the LCD
    WriteLCD(cmd);
}

void InitLCD(void)
{
    // Configure LCD data, RS, RW and EN pins as GPIO outputs
    IODIR0|=(0xFF<<LCD_DATA)|(1<<LCD_RS)|
            (1<<LCD_RW)|(1<<LCD_EN);

    // Wait for LCD power supply to stabilize
    delay_ms(15);

    // Initialize LCD using the required startup sequence
    CmdLCD(0x30);
    delay_ms(4);
    delay_us(100);
    CmdLCD(0x30);
    delay_us(100);
    CmdLCD(0x30);

    // Configure LCD for 8-bit mode and two-line display
    CmdLCD(MODE_8BIT_2LINE);

    // Turn ON display and turn OFF cursor
    CmdLCD(DSP_ON_CUR_OFF);

    // Clear all characters from the LCD
    CmdLCD(CLEAR_LCD);

    // Set cursor movement direction to right
    CmdLCD(SHIFT_CUR_RIGHT);
}

void CharLCD(u8 asciiVal)
{
    // Select LCD data register by making RS pin high
    IOSET0=1<<LCD_RS;

    // Send the character to the LCD
    WriteLCD(asciiVal);
}

void StrLCD(s8 *s)
{
    // Display each character until the null terminator is reached
    while(*s)
        CharLCD(*s++);
}

void U32LCD(u32 n)
{
    s32 i=0;
    u8 a[10];

    // Handle zero as a special case
    if(n==0)
    {
        CharLCD('0');
    }
    else
    {
        // Extract digits and store them in reverse order
        while(n>0)
        {
            a[i++]=(n%10)+48;
            n/=10;
        }

        // Display the stored digits in correct order
        for(--i;i>=0;i--)
        {
            CharLCD(a[i]);
        }
    }
}

void S32LCD(s32 n)
{
    // Display minus sign if the number is negative
    if(n<0)
    {
        CharLCD('-');
        n=-n;
    }

    // Display the integer part of the number
    U32LCD(n);
}

void F32LCD(f32 fn,u8 nDP)
{
    u32 n,i;

    // Display minus sign for negative floating-point values
    if(fn<0.0)
    {
        CharLCD('-');
        fn=-fn;
    }

    // Extract and display the integer part
    n=fn;
    U32LCD(n);

    // Display decimal point
    CharLCD('.');

    // Extract and display the required decimal digits
    for(i=0;i<nDP;i++)
    {
        fn=(fn-n)*10;
        n=fn;
        CharLCD(n+48);
    }
}

void BuildCGRAM(u8 *p,u8 nBytes)
{
    u32 i;

    // Select CGRAM address to create custom LCD characters
    CmdLCD(GOTO_CGRAM_START);

    // Select write operation and LCD data register
    IOCLR0=1<<LCD_RW;
    IOSET0=1<<LCD_RS;

    // Write custom character pattern bytes into CGRAM
    for(i=0;i<nBytes;i++)
    {
        WriteLCD(p[i]);
    }

    // Return cursor to the beginning of DDRAM
    CmdLCD(GOTO_LINE1_POS0);
}
