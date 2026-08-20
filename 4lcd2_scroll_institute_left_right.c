//4. Write a program to display the message “VECTOR” on the first Line and “Institute”on the second line of a 2x16 LCD. 
//Then make “Institute” scroll from right to left on second line of LCD screen.

#include "lcd.h"
#include <stdlib.h>
#include "delay.h"
#include "lcd_defines.h"
int main()
{
    char s[]="Institute    ",t;
    int i;

    InitLCD();

    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("VECTOR");

    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD(s);
        delay_s(1);

        t=s[0];
        for(i=0;s[i];i++)
            s[i]=s[i+1];
        s[i-1]=t;
    }
}

