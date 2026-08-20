//6. Write an ECP to display the ASCII table information for A-Z, a-z & 0-9 on LCD screen with respect to 5 seconds.For example,1st line: A D H O
//2nd line: A 65 41 101 After 5 secs  1st line: A D H O Embedded-C Assignments 2nd line: B 66 42 102 and so on ....
#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"
#include "lcd_defines.h"
void displayASCII(char c)
{
    CmdLCD(CLEAR_LCD);

    // Line 1 ? Character
    CmdLCD(GOTO_LINE1_POS0);
    CharLCD(c);

    // Line 2 ? Char, Decimal, Hex, Octal
    CmdLCD(GOTO_LINE2_POS0);
    CharLCD(c);
    CharLCD(' ');
    S32LCD(c);     // Decimal
    CharLCD(' ');
    HEXLCD(c);     // Hex
    CharLCD(' ');
    OCTLCD(c);     // Octal (if available)   
    delay_s(5);
}
int main()
{
    char c;

    InitLCD();

    // A-Z
    for(c = 'A'; c <= 'Z'; c++)
        displayASCII(c);

    // a-z
    for(c = 'a'; c <= 'z'; c++)
        displayASCII(c);

    // 0-9
    for(c = '0'; c <= '9'; c++)
        displayASCII(c);

    while(1);
}

