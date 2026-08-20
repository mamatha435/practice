//9. Write an ECP to remove extra spaces in a given string and display the final result on LCD.Note: Connect two switches. Based on first switch press, 
//take “ An Apple a day” as input and do the operation;Based on second switch press, take “ vector stu !”as input and do the operation. 
//In both cases print input and output on lcd screen.Output: When Switch1 is pressed, display “ An Apple a day” on the 1st line of LCD and when the
//switch1 is released display “An Apple a day” on the 2nd line of LCD.When Switch2 is pressed, display “ vector stu !” on the 1st line of LCD and when the
//switch2 is released display“vector stu !” on the 2nd line of LCD.If none of the switch is pressed,display “waiting for input”on the 1st line of LCD.

#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"
#include "defines.h"

#define SW1 14
#define SW2 15

// Function to remove extra spaces in a string
void removeSpace(char *s)
{
    int i = 0, j = 0;

    // Skip leading spaces
    while(s[i] == ' ') i++;

    for(; s[i]; i++)
    {
        // Copy only if not double space
        if(!(s[i] == ' ' && s[i+1] == ' '))
            s[j++] = s[i];
    }

    s[j] = 0; // Null-terminate
}

int main()
{
    char s1[] = "  An Apple a day";
    char s2[] = "  vector stu !";

    InitLCD();

    // Configure switch pins as input
    CLRBIT(IODIR0, SW1);
    CLRBIT(IODIR0, SW2);

    while(1)
    {
        // Switch 1 pressed
        if(RBIT(IOPIN0, SW1) == 0)
        {
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD(s1);          // Display input

            while(RBIT(IOPIN0, SW1) == 0); // Wait until release

            removeSpace(s1);     // Remove extra spaces

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD(s1);          // Display output
        }
        // Switch 2 pressed
        else if(RBIT(IOPIN0, SW2) == 0)
        {
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD(s2);          // Display input

            while(RBIT(IOPIN0, SW2) == 0); // Wait until release

            removeSpace(s2);     // Remove extra spaces

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD(s2);          // Display output
        }
        // No switch pressed
        else
        {
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("waiting for input ");
        }
    }
}
