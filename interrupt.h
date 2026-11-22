//interrupt.h
// Header file containing declarations for External Interrupt 0 (EINT0)

#include "types.h"

extern volatile u32 request;  // Declares the global interrupt request flag defined in interrupt.c

void eint0_enable(void);      // Configures and enables External Interrupt 0 (EINT0)
