//10.Write an ECP to develop any simple game on LCD by using customised characters.Note:if required you can take any input devices(switch, keypad)support
#include<lpc21xx.h>
#include "lcd.h"
#include <stdlib.h>
#include "delay.h"
#include "lcd_defines.h"
#include "defines.h"
u8 ball[8]={0x00,0x0E,0x11,0x11,0x0E,0x00,0x00,0x00};
int main()
{
    int pos=0, dir=1;

    InitLCD();
    BuildCGRAM(ball,8);

    while(1)
    {
        CmdLCD(0x80+pos);
        CharLCD(0);

        delay_ms(300);

        CmdLCD(0x80+pos);
        CharLCD(' ');

        pos+=dir;

        if(pos==15) dir=-1;
        if(pos==0)  dir=1;
    }
}
