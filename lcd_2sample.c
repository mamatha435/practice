//1. Write an ECP to take 20 numbers randomly in an array & find prime numbers in list of numbers to display on LCD.Note:must use rand()function
#include "lcd.h"
#include <stdlib.h>
#include "delay.h"
#include "lcd_defines.h"
int isPrime(int n)
{
    int i;
    if(n<2) return 0;

    for(i=2;i<n;i++)
        if(n%i==0)
            return 0;
    return 1;
}

int main()
{
    int a[20], i;

    InitLCD();

    for(i=0;i<20;i++)
        a[i] = rand()%100;

    CmdLCD(CLEAR_LCD);
    StrLCD("Prime Nos:");

    for(i=0;i<20;i++)
    {
        if(isPrime(a[i]))
        {
            CmdLCD(GOTO_LINE2_POS0);
            S32LCD(a[i]);
            delay_s(2);
        }
    }
    while(1);
}
