//2. Write a program to display the message “VECTOR” on the first Line and “Institute” on the second line of a 2x16 LCD. 
//Then make “Institute” flash at the rate of 1sec for 5 times, then clear the LCD screen
#include "lcd.h"
#include "delay.h"
#include "LCD_defines.h"
int main()
{
    int i;
    InitLCD();
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("VECTOR");
    for(i=0;i<5;i++)
    {
        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("Institute");
        delay_s(1);

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("         ");
        delay_s(1);
    }
    CmdLCD(CLEAR_LCD);
    while(1);
}


/*#include "lcd.h"
#include "delay.h"

int main(){
	unsigned int i;
    InitLCD();
    LCD_SetCursor(0,0);
    LCD_String("VECTOR");      // Line 1
    LCD_SetCursor(1,0);
    for(i=0;i<5;i++){
        LCD_String("Institute");   // Show
        delay_ms(1000);
        LCD_SetCursor(1,0);
        LCD_String("         ");   // Clear line
        delay_ms(1000);
    }
    LCD_Clear();
    while(1);
}
*/
