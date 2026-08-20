//3. Write an ECP to check whether given string is palindrome or not and display result on LCD.
#include "lcd.h"
#include <stdlib.h>
#include "delay.h"
#include "lcd_defines.h"

int isStrPal(char *s)
{
    int i,l;

    for(l=0;s[l];l++);

    for(i=0;i<l/2;i++)
        if(s[i]!=s[l-1-i])
            return 0;
    return 1;
}

int main()
{
    char s[]="madam";

    InitLCD();

    StrLCD(s);

    CmdLCD(GOTO_LINE2_POS0);

    if(isStrPal(s))
        StrLCD("Palindrome");
    else
        StrLCD("Not Palindrome");

    while(1);
}
