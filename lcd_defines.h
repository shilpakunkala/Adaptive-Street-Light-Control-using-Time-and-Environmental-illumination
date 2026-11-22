//lcd_defines.h
// Header file containing HD44780 LCD commands and LPC2129 pin configurations

// HD44780 LCD command definitions

#define CLEAR_LCD            0x01  // Clears the LCD display and returns cursor to home
#define RET_CUR_HOME         0x02  // Returns cursor to the first position
#define SHIFT_CUR_RIGHT      0x06  // Moves cursor automatically to the right after writing data
#define SHIFT_CUR_LEFT       0x07  // Moves cursor automatically to the left after writing data
#define DSP_OFF              0x08  // Turns OFF the LCD display
#define DSP_ON_CUR_OFF       0x0C  // Turns ON display and turns OFF cursor
#define DSP_ON_CUR_ON        0x0E  // Turns ON display and cursor
#define DSP_ON_CUR_BLINK     0x0F  // Turns ON display with blinking cursor
#define SHIFT_DISP_LEFT      0x10  // Shifts the entire display to the left
#define SHIFT_DISP_RIGHT     0x14  // Shifts the entire display to the right
#define MODE_8BIT_1LINE      0x30  // Configures LCD for 8-bit mode and one line
#define MODE_4BIT_1LINE      0x20  // Configures LCD for 4-bit mode and one line
#define MODE_8BIT_2LINE      0x38  // Configures LCD for 8-bit mode and two lines
#define MODE_4BIT_2LINE      0x28  // Configures LCD for 4-bit mode and two lines
#define GOTO_LINE1_POS0      0x80  // Sets cursor to the first position of line 1
#define GOTO_LINE2_POS0      0xC0  // Sets cursor to the first position of line 2
#define GOTO_LINE3_POS0      0x94  // Sets cursor to the first position of line 3
#define GOTO_LINE4_POS0      0xD4  // Sets cursor to the first position of line 4
#define GOTO_CGRAM_START     0x40  // Selects the starting address of CGRAM

// LCD connection pin definitions

#define LCD_DATA 8   // LCD data pins D0-D7 connected to P0.8-P0.15
#define LCD_RS   16  // Register Select pin connected to P0.16
#define LCD_RW   17  // Read/Write pin connected to P0.17
#define LCD_EN   18  // Enable pin connected to P0.18
