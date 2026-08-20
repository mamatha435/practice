#include "types.h"
#include "lcd.h"
#include "kpm.h"
#include "rtc_main.c"
#include "delay.h"

#define BUZZER (1<<10)     // P0.10
#define LED    (1<<16)     // P1.16

#define MAX_MED 5         // Maximum 5 medicine timings

u8 med_hour[MAX_MED];
u8 med_min[MAX_MED];
u8 med_count = 0;

u8 config_mode = 0;
u8 alarm_active = 0;
u32 alarm_timer = 0;

/*---------------- EINT0 : Enter Configuration Mode ---------------*/
void eint0_isr(void) __irq
{
    config_mode = 1;
    EXTINT = 1<<0;
    VICVectAddr = 0;
}

/*---------------- EINT1 : Acknowledge Alarm -----------------------*/
void eint1_isr(void) __irq
{
    alarm_active = 0;
    IOCLR0 = BUZZER;
    IOCLR1 = LED;
    EXTINT = 1<<1;
    VICVectAddr = 0;
}

/*---------------- Setup Interrupts ----------------*/
void InitInterrupts(void)
{
    /* P0.1 = EINT0 */
    PINSEL0 &= ~(3<<2);
    PINSEL0 |=  (1<<2);

    /* P0.3 = EINT1 */
    PINSEL0 &= ~(3<<6);
    PINSEL0 |=  (1<<6);

    EXTMODE  = 0x03;   // Edge sensitive
    EXTPOLAR = 0x00;   // Falling edge

    EXTINT = 0x03;

    VICIntEnable = (1<<14) | (1<<15);

    VICVectCntl0 = (1<<5)|14;
    VICVectAddr0 = (u32)eint0_isr;

    VICVectCntl1 = (1<<5)|15;
    VICVectAddr1 = (u32)eint1_isr;
}

/*---------------- Configure Medicine Schedule ----------------*/
void ConfigureMedicine(void)
{
    u8 i;

    CmdLCD(0x01);
    StrLCD("No. of Meds:");
    med_count = ReadNum();

    if(med_count > MAX_MED)
        med_count = MAX_MED;

    for(i=0;i<med_count;i++)
    {
        CmdLCD(0x01);
        StrLCD("Med ");
        CharLCD('1'+i);
        StrLCD(" Hour:");
        med_hour[i] = ReadNum();

        CmdLCD(0x01);
        StrLCD("Minute:");
        med_min[i] = ReadNum();
    }

    CmdLCD(0x01);
    StrLCD("Saved!");
    delay_ms(1000);

    config_mode = 0;
}

/*---------------- Alarm Check ----------------*/
void CheckAlarm(void)
{
    u8 i;

    for(i=0;i<med_count;i++)
    {
        if((HOUR == med_hour[i]) && (MIN == med_min[i]))
        {
            alarm_active = 1;
            alarm_timer = 0;
        }
    }
}

/*---------------- MAIN ----------------*/
int main()
{
    InitLCD();
    InitKPM();
    RTC_Init();
    InitInterrupts();
     
  	IODIR0 |= BUZZER;
    IODIR1 |= LED;
   
    while(1)
    {
        /* -------- Enter Configuration Mode -------- */
        if(config_mode)
        {   u8 choice;
            CmdLCD(0x01);
            StrLCD("1.Edit RTC");
            CmdLCD(0xC0);
            StrLCD("2.Set Medicine");
      
            choice = KeyScan();

            if(choice=='1')
            {
                CmdLCD(0x01);
                StrLCD("Set Hour:");
                HOUR = ReadNum();

                CmdLCD(0x01);
                StrLCD("Set Minute:");
                MIN = ReadNum();
            }
            else if(choice=='2')
            {
                ConfigureMedicine();
            }

            config_mode = 0;
        }

        /* -------- Clock Only Mode -------- */
        CmdLCD(0x80);
        StrLCD("Time:");
        CharLCD(HOUR);
        CharLCD(':');
        CharLCD(MIN);
        CharLCD(':');
        CharLCD(SEC);

        /* -------- Alarm Monitoring -------- */
        if(med_count > 0)
            CheckAlarm();

        /* -------- Alarm Active -------- */
        if(alarm_active)
        {
            CmdLCD(0xC0);
            StrLCD("Take Medicine!");

            IOSET0 = BUZZER;
            IOSET1 = LED;

            delay_ms(500);

            IOCLR0 = BUZZER;
            IOCLR1 = LED;

            delay_ms(500);

            alarm_timer++;

            if(alarm_timer >= 120)   // ~1 minute
            {
                alarm_active = 0;
            }
        }

        delay_ms(200);
    }
	}
