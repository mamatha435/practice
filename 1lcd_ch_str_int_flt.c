//1. Write an ECP to develop the driver for 16*2 alphanumeric LCD.
//a) To display a character
//b) To display a string 
//c) To display an integer 
//d) To display float number up to three decimal places.
//e) To display any custom character.
#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "types.h"
u8 myChar[8] = {0x0A,0x15,0x11,0x11,0x0A,0x04,0x00,0x00};
int main()
{
    InitLCD();
    // a) display character
    CharLCD('A');
    // b) display string
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("vector");
    delay_s(3);
    // c) display integer
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("      ");
    CmdLCD(GOTO_LINE2_POS0);
    U32LCD(12345);
    delay_s(3);
    // signed integer
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("      ");
    CmdLCD(GOTO_LINE2_POS0);
    S32LCD(-12345);
    delay_s(3);
    // d) float
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("       ");
    CmdLCD(GOTO_LINE2_POS0);
    F32LCD(123.46,3);
    delay_s(3);
    // e) custom character
    BuildCGRAM(myChar,0);
    CmdLCD(GOTO_LINE2_POS0);
    CharLCD(0);
    while(1);
}
