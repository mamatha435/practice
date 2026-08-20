//main.c
#include <lpc21xx.h>
#include "types.h"
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"
#include "rtc_main.h"
#include "eint.h"
#include "medicine.h"
#include "buzzer.h"
#include "kpm.h"

#define SW1       (1<<3)  // Assuming Switch-1 is on P0.3
//#define SW2 (1<<1)  // Switch-2 is connected to P0.1

extern volatile u8 alarm_flag;

int main(void)
{
   s32 hour, min, sec, date, month, year;
   // Timer variables 
    static u32 alert_start_time = 0;
    static u8 timer_running = 0;
	
    // Initialize peripherals
    RTC_Init();        
    InitLCD(); 
    EINT_Init();      
	  InitKPM();
    IODIR0 |= BUZZER;  
  //  IODIR0 &= ~SW1;    // Ensure SW1 is input
	
    // Initial RTC Setup (11th March 2026)
    SetRTCTimeInfo(16, 50, 0);
    SetRTCDateInfo(13, 3, 2026);
    SetRTCDay(FRI);
	
	  StrLCD("MEDICINE project ");
     delay_ms(1000);
	      DisplayRTCTime(hour, min, sec);
				delay_ms(1000);
        DisplayRTCDate(date, month, year);
        delay_ms(100);

    while (1)
    {
			// --- Continuous Operation: Priority Check for Switch-1 --
        // 1. Menu Trigger (Always active)
        if (!(IOPIN0 & SW1)) 
        {
          // The system pauses monitoring to allow updates
            System_Menu(); 
            // Once the user finishes and exits the menu, 
            // the system immediately resumes monitoring with new data.
        }

        // 2. Read and Display RTC (Digital Clock Mode)
        GetRTCTimeInfo(&hour, &min, &sec);
        GetRTCDateInfo(&date, &month, &year);
        
        DisplayRTCTime(hour, min, sec);
        DisplayRTCDate(date, month, year);

        // 3. Conditional Alert Checking (Clock-Only Mode)
        // Only run check and buzzer logic if at least one medicine is set
        if(medicine_count > 0) 
        {
            CheckMedicineTimings(hour, min, sec);
            if (alarm_flag)
            {   
               // A. Initialize 1-minute window
                if (!timer_running) 
								{
                     alert_start_time = 0; // Reset your local counter
                     timer_running = 1;
                }
                // B. Display Message
                 CmdLCD(GOTO_LINE2_POS0);
                 StrLCD("Take Medicine Now");
                // C. Periodic Buzzer (Toggle every 200ms based on loop speed)
               PulseBuzzer();
               // D. 1-Minute Timeout Check
              // If 200ms delay is used, 300 iterations = 60 seconds
              alert_start_time++;
              if (alert_start_time >= 300) 
							{ 
                   alarm_flag = 0; // Auto-stop after 1 minute
               }
	          }
                    // Acknowledgment (Check if EINT0/Switch pressed)
                   // If the user acknowledges, the ISR for EINT0 should set alarm_flag = 0
                    //  Cleanup when alarm is not active
            else
            {
							 timer_running = 0;
               IOCLR0 = BUZZER;
							 CmdLCD(GOTO_LINE2_POS0);
               StrLCD("                ");
            }
        }
     else
            {
                // --- REQUIREMENT: Immediate Stop & Normal Monitoring ---
                // This block runs as soon as alarm_flag is set to 0 
                // (Either by Switch-2 Interrupt OR the Timeout above)
                //timer_running = 0;
							  alarm_flag = 0;
                IOCLR0 = BUZZER;
              //  CmdLCD(GOTO_LINE2_POS0);
                //StrLCD("                "); // Returns to normal RTC view
            }

        delay_ms(200); 
    }
		
}
