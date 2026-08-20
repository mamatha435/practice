//4. Write an ECP display the basic time (HH:MM:SS) on LCD. Note: don’t use RTC registers
#include "lcd.h"
#include "delay.h"
#include "LCD_defines.h"
int main()
{
    int h=0,m=0,s=0;

    InitLCD();

    while(1)
    {
        CmdLCD(GOTO_LINE1_POS0);

        S32LCD(h); CharLCD(':');
        S32LCD(m); CharLCD(':');
        S32LCD(s);

        delay_s(1);

        s++;
        if(s==60){ s=0; m++; }
        if(m==60){ m=0; h++; }
        if(h==24) h=0;
    }
}

/*int main(){
    u8 hh=0, mm=0, ss=0;
    char time_str[9];
    InitLCD();

    while(1){
        sprintf(time_str,"%02d:%02d:%02d",hh,mm,ss);
        LCD_SetCursor(0,0);
        LCD_String(time_str);
        delay_ms(1000);
        ss++;
        if(ss>=60){ ss=0; mm++; }
        if(mm>=60){ mm=0; hh++; }
        if(hh>=24){ hh=0; }
    }
}*/
