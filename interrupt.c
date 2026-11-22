//interupt.c
// Interrupt driver implementation for handling External Interrupt 0 (EINT0) using LPC2129

#include <LPC21xx.h>
#include "types.h"

// Define the VIC interrupt channel number assigned to EINT0
#define EINT0_CHNO 14

// Global flag used to indicate that an external interrupt has occurred
volatile u32 request=0;

// EINT0 Interrupt Service Routine (ISR)
void eint0_isr(void)__irq
{
    // Set the request flag when EINT0 interrupt occurs
    request=1;

    // Clear the EINT0 interrupt flag to acknowledge the interrupt
    EXTINT=1<<0;

    // Inform the VIC that interrupt servicing is completed
    VICVectAddr=0;
}

// Function to configure and enable External Interrupt 0
void eint0_enable(void)
{
    // Select EINT0 function on pin P0.1
    PINSEL0 &= ~(3<<2);
    PINSEL0 |=  (3<<2);

    // Configure EINT0 as an IRQ interrupt
    VICIntSelect &= ~(1<<EINT0_CHNO);

    // Assign the EINT0 ISR address to VIC vector slot 0
    VICVectAddr0=(u32)eint0_isr;

    // Enable vector slot 0 and assign EINT0 interrupt channel
    VICVectCntl0=(1<<5)|EINT0_CHNO;

    // Configure EINT0 for edge-triggered interrupt operation
    EXTMODE |= (1<<0);

    // Configure EINT0 to trigger on a falling edge
    EXTPOLAR &= ~(1<<0);

    // Clear any previously pending EINT0 interrupt
    EXTINT=1<<0;

    // Enable EINT0 interrupt in the VIC
    VICIntEnable |= (1<<EINT0_CHNO);
}
