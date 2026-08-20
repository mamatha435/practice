//LM35_test.c
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "lm35.h"

int main()
{
    s32 t;
    InitLCD();
    StrLCD("LM35 TEST");
    while(1)
    {
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("                ");   // Clear line
        CmdLCD(GOTO_LINE1_POS0);
			  U32LCD(Read_LM35);
			  CmdLCD(GOTO_LINE2_POS0);
        t= Read_LM35_NP();
        S32LCD(t);     // Display float value
        StrLCD(" degC");
        delay_ms(100);
    }
}
