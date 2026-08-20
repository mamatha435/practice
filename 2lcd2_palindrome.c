//2. Write an ECP to take ten 3-digit numbers randomly in an array and find palindrome numbers in the list of numbers 
//to display on LCD.Note: must use rand() function
#include "lcd.h"
#include <stdlib.h>
#include "delay.h"
#include "lcd_defines.h"

int isPal(int n)
{
    int r=0,t=n;

    while(t)
    {
        r = r*10 + t%10;
        t/=10;
    }
    return r==n;
}

int main()
{
    int a[10], i;

    InitLCD();

    for(i=0;i<10;i++)
        a[i] = 100 + rand()%900;   // 3 digit

    StrLCD("Palindromes:");

    for(i=0;i<10;i++)
    {
        if(isPal(a[i]))
        {
            CmdLCD(GOTO_LINE2_POS0);
            S32LCD(a[i]);
            delay_s(2);
        }
    }
    while(1);
}
