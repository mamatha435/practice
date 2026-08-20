#include <lpc21xx.h>
#include "types.h"

#define EINT0_VIC_CHNO   14
#define BUZZER           (1<<25)   // P0.25

// The alarm_flag is used to communicate between the interrupt and the main loop.
// volatile ensures the compiler doesn't optimize this variable away.
volatile u8 alarm_flag = 0;

// ------------------- EINT1 ISR (Switch-2) -------------------
// Requirement 5: User Acknowledgment Using Switch-2    EINT0 ISR (Switch-2 on P0.1)
// This function stops the buzzer and clears the alarm flag immediately.

void EINT0_isr(void) __irq 
{
    alarm_flag = 0;    // Immediately stop the logic in main.c
    IOCLR0 = BUZZER;   // Requirement: Stop buzzer immediately
	  EXTINT = (1<<0);    // Clear the interrupt flag
    VICVectAddr = 0;   // Acknowledge Interrupt
}

// ------------------- Initialize Interrupts -------------------
// EINT_Init
// Function: Configures P0.1 as an External Interrupt (EINT0).

void EINT_Init(void)
{
   /* 1. Pin Selection */
    // Configures P0.1 to act as EINT0. 
    // PINSEL0 Bits 3:2 are set to 11 for EINT0 on most LPC2148 boards.
	  PINSEL0 &= ~(3 << 2); // Clear bits 3:2
    PINSEL0 |=  (3 << 2);   // Set bits 3:2 to '11' (decimal 3)

    /* 2. Trigger Configuration */
    EXTMODE  |= (1 << 0);    // Set EINT0 to Edge Sensitive
    EXTPOLAR |= (1 << 0);   // Set EINT0 to Falling Edge (Switch Press);Set to '1' for Rising Edge (Active High)

    /* 3. VIC Configuration for EINT1 */
    // Enable EINT1 interrupt channel
    VICIntEnable |= (1 << EINT0_VIC_CHNO);
      VICIntSelect &= ~(1 << 14);    // Set EINT0 to IRQ mode (not FIQ)
    // Assign ISR to a Vector Slot (using slot 1)
    // 0x20 is the enable bit for the slot + channel number
    VICVectCntl0 = 0x20 | EINT0_VIC_CHNO; 
    VICVectAddr0 = (u32)EINT0_isr;
    
    // Clear any existing interrupt flags
    EXTINT = (1 << 0); 
}
