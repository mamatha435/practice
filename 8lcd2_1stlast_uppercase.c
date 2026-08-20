//8. Write an ECP to convert first and last character of each word in to upper case and display the final result on LCD.Note: Connect two switches.
//Based on first switch press, take “vector india” as input and do the operation; Based on second switch press, take “vector Hyderabad” as input and 
//do the operation. In both cases print input and output on lcd screen.Output:When Switch1 is pressed, display “vector india” on the 1st line of LCD 
//and when the switch1 is released display “VectoR IndiA” on the 2nd line of LCD.When Switch2 is pressed, display “vector hyderabad” on the 1st line
//of LCD and when the switch2 is released display“VectoR HyderabaD” on the 2ndline of LCD.If none of the switch is pressed,display “waiting for input”
//on the 1st line of LCD
#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"
#include "defines.h"

#define SW1 14
#define SW2 15

void FLupper(char *s)
{
    int i;

    // First character of string
    if(s[0] >= 'a' && s[0] <= 'z')
        s[0] -= 32;

    for(i = 1; s[i]; i++)
    {
        // First letter after space
        if(s[i-1] == ' ' && s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;

        // Last letter before space
        if(s[i+1] == ' ' && s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    }

    // Last character of string
    i--;
    if(s[i] >= 'a' && s[i] <= 'z')
        s[i] -= 32;
}

int main()
{
    char s1[] = "vector india";
    char s2[] = "vector hyderabad";

    InitLCD();

    CLRBIT(IODIR0, SW1);
    CLRBIT(IODIR0, SW2);

    while(1)
    {
        CmdLCD(CLEAR_LCD);

        if(RBIT(IOPIN0, SW1) == 0)
        {
            StrLCD("vector india");

            while(RBIT(IOPIN0, SW1) == 0);

            CmdLCD(GOTO_LINE2_POS0);
            FLupper(s1);
            StrLCD(s1);
        }

        else if(RBIT(IOPIN0, SW2) == 0)
        {
            StrLCD("vector hyderabad");

            while(RBIT(IOPIN0, SW2) == 0);

            CmdLCD(GOTO_LINE2_POS0);
            FLupper(s2);
            StrLCD(s2);
        }

        else
        {
            StrLCD("waiting for input");
        }
    }
}
