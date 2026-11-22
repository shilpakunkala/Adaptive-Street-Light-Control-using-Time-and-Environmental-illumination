
/*
  File Name : delay.c
  Description : Provides software delay function to generate delays in microseconds,milliseconds and seconds.
 */

#include "types.h"

/*
  Function Name : delay_us()
  Description   : Generates a delay in microseconds.
  Parameter     : dlyUS - Delay duration in microseconds.
 
  Assumption    : The processor clock is 12 MHz.
 */
void delay_us(u32 dlyUS)
{
    // Generate an approximate delay using a software loop.
    for(dlyUS *= 12; dlyUS > 0; dlyUS--);
}

/*
 * Function Name : delay_ms()
 * Description   : Generates a delay in milliseconds.
 * Parameter     : dlyMS - Delay duration in milliseconds.
 */
void delay_ms(u32 dlyMS)
{
    // Convert milliseconds into loop iterations.
    for(dlyMS *= 12000; dlyMS > 0; dlyMS--);
}

/*
 * Function Name : delay_s()
 * Description   : Generates a delay in seconds.
 * Parameter     : dlyS - Delay duration in seconds.
 */
void delay_s(u32 dlyS)
{
    // Convert seconds into loop iterations.
    for(dlyS *= 12000000; dlyS > 0; dlyS--);
}
