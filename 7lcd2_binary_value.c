//7. Write an ECP to display the binary value for A-Z, a-z & 0-9 on LCD screen with
//respect to 5 seconds.For example,1st line: A 2nd line: 01000001  After 5 secs 1st line: B 2nd line: 01000010 and so on ....
#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"

void displayBinary(char c)
{
    CmdLCD(CLEAR_LCD);

    CmdLCD(GOTO_LINE1_POS0);
    CharLCD(c);

    CmdLCD(GOTO_LINE2_POS0);
    BinLCD(c,8);   // display 8-bit binary

    delay_s(5);
}

int main()
{
    char c;

    InitLCD();

    // A-Z
    for(c = 'A'; c <= 'Z'; c++)
        displayBinary(c);

    // a-z
    for(c = 'a'; c <= 'z'; c++)
        displayBinary(c);

    // 0-9
    for(c = '0'; c <= '9'; c++)
        displayBinary(c);

    while(1);
}
