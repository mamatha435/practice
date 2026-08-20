//3. Write an ECP to rotate a string on LCD (From right to left)
#include "lcd.h"
#include "string.h"
#include "LCD_defines.h"
void delay_s(unsigned char s)
{
	s*=1200000;
	while(s--);
}
int main()
{
    char s[]="VECTOR INSTITUTE   ",t;
    int i;

    InitLCD();

    while(1)
    {
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD(s);

        delay_s(1);

        // rotate left
        t=s[0];
        for(i=0;s[i];i++)
            s[i]=s[i+1];

        s[i-1]=t;
    }
}


/*#include "lcd.h"
#include "string.h"
#include "delay.h"

int main(){
    char msg[] = "HELLO VECTOR  ";
	char first;
	unsigned int i;
    int len = strlen(msg);
    InitLCD();
    LCD_SetCursor(0,0);

    while(1){
        LCD_String(msg);
        delay_ms(500);
        // Shift string left by 1
        first = msg[0];
        for(i=0;i<len-1;i++)
            msg[i] = msg[i+1];
        msg[len-1] = first;
        LCD_SetCursor(0,0);
    }
}
*/
