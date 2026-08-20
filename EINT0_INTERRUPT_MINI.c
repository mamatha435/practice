//EINT0_INTERRUPT_MINI.C
#include<lpc21xx.h>
#include "delay.h"
#include "types.h"
#include "LCD_DEFINES.h"
#include "LCD.h"
#include "KPM.h"
#include "kpm_defines.h"
#include "eint0_defines_mini.h"
#include "eint0_mini.h"
#include "rtc_mini.h"

extern u8 alert_done; // External flag (used for logic tracking)
extern u8 buzzer;     // External buzzer flag from main file

void InitEINT0()
{
    // Clear bits for P0.1 and P0.3 functions using bitmask
    PINSEL0&=((u32)~3<<2)|((u32)~3<<6); 
    
    // Configure P0.1 as EINT0 and P0.3 as EINT1
    PINSEL0|=EINT0_INPUT|EINT1_INPUT;
    
    // Enable EINT0 and EINT1 in the Vectored Interrupt Controller (VIC)
    VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO;
    
    // Configure VIC Slot 0 for EINT0 and Slot 1 for EINT1 (1<<5 enables the slot)
    VICVectCntl0=((1<<5)|EINT0_VIC_CHNO);
    VICVectCntl1=((1<<5)|EINT1_VIC_CHNO);
    
    // Assign the addresses of the ISR functions to the VIC slots
    VICVectAddr0=(u32) EINT0_ISR ;
    VICVectAddr1=(u32) EINT1_ISR ;
    
    // Set both EINT0 and EINT1 to Edge-Sensitive mode
    EXTMODE=(1<<1)|(1<<0);
    
    // Set the Buzzer pin direction to OUTPUT
    IODIR0|=1<<EINT1_BUZZER;
}

void menu()
{
    u32 keyv; // Variable to store pressed key from keypad
    
    while(1) // Stay in menu until '3' is pressed
    {
        CmdLCD(0X01);               // Clear LCD screen
        CmdLCD(0x80);               // Position cursor at Row 1, Col 1
        StrLCD("1.EDITRTC 3.EXIT"); // Display options
        CmdLCD(0xc0);               // Position cursor at Row 2, Col 1
        StrLCD("2.EDIT MEDICINE "); // Display options
        
        keyv=KeyScan();             // Wait for and capture a key press
        
        switch(keyv)
        {
            case '1': RTC_Menu();         // Go to RTC editing sub-menu
                      break;
            case '2': Medicine_Menu();        // Go to Medicine time editing sub-menu
                      break;
            case '3': CmdLCD(0x01);       // Clear screen before exiting
                      return ;            // Return to the main clock display
        }
    }
}

// ISR for EINT0 (Typically triggered by a "Settings" or "Menu" button)
void EINT0_ISR(void) __irq
{
    menu();           // Enter the configuration menu
    EXTINT=1<<0;      // Clear the EINT0 interrupt flag in hardware
    VICVectAddr=0;    // Acknowledge the interrupt to the VIC
}

// ISR for EINT1 (Typically triggered by a "Medicine Taken" / "Stop Buzzer" button)
void EINT1_ISR(void) __irq
{
    if(buzzer)        // Check if the buzzer is actually active
    {
        IOCLR0 = 1<<EINT1_BUZZER; // Turn OFF the Buzzer pin
        
        CmdLCD(0x01);             // Clear screen
        CmdLCD(0x80);             // Line 1
        StrLCD("MEDICINE");
        CmdLCD(0xC0);             // Line 2
        StrLCD("TAKEN");          // Confirm user action
        
        delay_ms(2000);           // Pause for 2 seconds to show confirmation
        buzzer= 0;                // Reset buzzer flag to 0
    }

    EXTINT=1<<1;      // Clear the EINT1 interrupt flag in hardware
    VICVectAddr=0;    // Acknowledge the interrupt to the VIC
}
