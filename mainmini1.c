// mainmini1.C 
#include "types.h"            
#include <lpc21xx.h>        
#include "delay.h"          
#include "LCD_DEFINES.h"    
#include "LCD.h"           
#include "kpm.h"           
#include "kpm_defines.h"   
#include "eint0_mini.h"    
#include "rtc_mini.h"        
#include "eint0_defines_mini.h" 

// Global variables for Time, Date, and Day
s32 hour, minute, second, date, month, year, day;

// Arrays to store 3 different medicine alarm times (Hours, Minutes, Seconds)
s32 mh[3] = {0,0,0}; 
s32 mm[3] = {0,0,0}; 
s32 ms[3] = {0,0,0}; 

u8 mc = 0;       // Flag to check if medicine schedule is set (1 = Active)
u8 buzzer = 0;   // Flag to track if the buzzer is currently sounding
u32 prev_sec = 0; // Stores the previous second value to detect changes
u32 scount = 0;   // Counter to track elapsed seconds while buzzer is on

int main()
{
    u32 i; // Loop variable for checking medicine slots

    // --- Initialization Section ---
    InitRTC();                        // Initialize the internal Real-Time Clock hardware
    SetRTCTimeInfo(10,45,9);         // Set starting time to 10:45:09
    SetRTCDateInfo(20,03,2026);      // Set starting date to 20th March 2026
    SetRTCDay(1);                    // Set day of the week (e.g., Monday)
    
    InitLCD();                       // Configure LCD pins as output and initialize controller
    InitKPM();                       // Initialize Keypad Matrix GPIO pins
    InitEINT0();                     // Initialize External Interrupt 0 (likely for snooze/stop)

    CmdLCD(0x01);                    // Clear the LCD screen

    // --- Main Program Loop ---
    while(1)
    {
        // Read current Time, Date, and Day from the RTC registers
        GetRTCTimeInfo(&hour, &minute, &second);
        GetRTCDateInfo(&date, &month, &year);
        GetRTCDay(&day);

        /* Detect every new second change */
        if(second != prev_sec)
        {
           prev_sec = second;        // Update the previous second tracker
           if(buzzer)                // If the buzzer is active...
           {
             scount++;               // Increment the "seconds passed" counter
           }
        }

        /* Show RTC only when buzzer is not active */
        if(buzzer == 0)
        {
           DisplayRTCTime(hour, minute, second); // Update time on LCD
           DisplayRTCDate(date, month, year);    // Update date on LCD
           DisplayRTCDay(day);                   // Update day on LCD
        }

        /* -------- BUZZER TIMEOUT CHECK (1 Minute Limit) -------- */
        // If buzzer is on and user hasn't stopped it for 60 seconds
        if(buzzer && scount >= 60)
        {
            IOCLR0 = 1 << EINT1_BUZZER; // Turn OFF the Buzzer (P0.x clear)

            CmdLCD(0x01);               // Clear screen
            CmdLCD(0x80);               // Move cursor to Row 1
            StrLCD(" MEDICINE ");      // Display alert
            CmdLCD(0xC0);               // Move cursor to Row 2
            StrLCD(" NOT TAKEN ");     // Display failure message
            delay_ms(2000);             // Keep message on screen for 2 seconds

            buzzer = 0;                 // Reset buzzer flag
            scount = 0;                 // Reset the second counter
        }

        /* -------- MEDICINE TIME CHECK -------- */
        // If medicine reminder mode (mc) is enabled
        if(mc == 1)
        {
            // Loop through all 3 medicine time slots
            for(i = 0; i < 3; i++)
            {
                // Compare current time with the programmed medicine times
                if(hour == mh[i] && minute == mm[i] && second == ms[i] && buzzer == 0)
                {
                    CmdLCD(0x01);            // Clear screen
                    CmdLCD(0x80);            // Move cursor to Row 1
                    StrLCD("Take Medicine"); // Display reminder message
                    
                    IOSET0 = 1 << EINT1_BUZZER; // Turn ON the Buzzer (P0.x set)
                    buzzer = 1;              // Set buzzer flag to true
                    scount = 0;              // Start counting seconds for the timeout
                }
            }
        }
    } 
}
