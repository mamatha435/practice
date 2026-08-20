//kpm.c

#include <lpc21xx.h>
#include "type.h"
#include "defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"

u32 kpmLUT[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'c','0','=','+'}};
u8 keyv;
#define IN_PUT 0xFFFFFFFF
void InitKPM(void)
{
IODIR1|=15<<row1;
}
u32 ColScan(void)
{
return ((((IOPIN1>>cols1)&15)<15)?0:1); //RNIBBLE(WORD,SBITPOS) ((WORD>>SBITPOS)&15)  (data>>bitposn)&15
}

//keyvalue
u32 KeyScan(void)
{
u32 rno,cno;
///wait for switch press
while(ColScan());//if no cols effected it gives value 1 if any one of the switch pressed the colscan value is zero so terminate the loop then find rn0 and cno
//find rno
rno=RowCheck();
//find the cno
cno=ColCheck();
//get the key value using kpmLUT
keyv=kpmLUT[rno][cno];
//wait for switch release
while(!ColScan());
return keyv;
}

u32 RowCheck(void)
{
u32 rno;
for(rno=0;rno<4;rno++)
{
IOPIN1=(IOPIN1&~(15<<row1))|((~(1<<rno))<<row1);
if(ColScan()==0)
{
break;
}
}
//make rows as default
IOPIN1=(IOPIN1&~(15<<row1))|(0x0<<row1);
return rno;
}

u32 ColCheck(void)
{
u32 cno;
for(cno=0;cno<4;cno++)
{
if(((IOPIN1>>(cols1+cno))&1)==0)//we check one by one
{
break;
}
}
return cno;
}

u32 ReadNum(void)
{
        u8 key;
        u32 sum=0;
        while(1)
        {
                key=KeyScan();
                if(key>='0'&&key<='9')
                {
                        CharLCD(key);
                        sum=(sum*10)+(key-'0');
                }
                else if(key=='=')
                {
                        break;
                }
        }
        return sum;
}
u32 ReadNDigitInput(u8 max_digits)
{
    u8 key;
    u8 digits[5];      // enough for year
    u8 count = 0;

    while(1)
    {
        key = KeyScan();

        if(key >= '0' && key <= '9')
        {
            if(count < max_digits)
            {
                digits[count++] = key;
                CharLCD(key);
            }
        }

        else if(key == 'c')   // Backspace
        {
            if(count > 0)
            {
                count--;

                CmdLCD(0x10);   // cursor left
                CharLCD(' ');
                CmdLCD(0x10);
            }
        }

        else if(key == '=')   // Enter
        {
            if(count > 0)
            {
                u32 val = 0;
                u8 i;

                for(i=0;i<count;i++)
                {
                    val = val*10 + (digits[i]-'0');
                }

                return val;
            }
        }
                        /*      else if(key == '+') //nothing to take
                                {
                                                                        return IN_PUT;
                                }*/
    }
}


u32 Read2Digit(void)
{
        u32 d1,d2;
        d1=KeyScan();
         CharLCD(d1);
        d2=KeyScan();
         CharLCD(d2);
        return (d1-'0')*10+(d2-'0');
}