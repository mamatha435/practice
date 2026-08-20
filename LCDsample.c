//5. Write an ECP to display the switch press count on LCD.
#include <lpc21xx.h>
#include "lcd.h"
#include "types.h"
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
#define SW 14
int main()
{
    int count = 0;

    InitLCD();

    CLRBIT(IODIR0, SW);   // configure as input

    while(1)
    {
        if(RBIT(IOPIN0, SW) == 0)
        {
            delay_ms(200);     // debounce

            count++;

            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("Count:");

            CmdLCD(GOTO_LINE2_POS0);
            S32LCD(count);

            while(RBIT(IOPIN0, SW) == 0);   // wait for release
        }
    }
}
