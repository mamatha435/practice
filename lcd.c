//LCD.c
#include<lpc21xx.h>
#include "LCD_defines.h"
#include "types.h"
#include "defines.h"
#include "delay.h"
void WriteLCD(u8 data)
{
	SCLRBIT(IOCLR0,RW);//RW=0, write operation
	WBYTE(IOPIN0,LCD_DATA,data);
	SSETBIT(IOSET0,EN);//EN=1
	delay_us(1);
	SCLRBIT(IOCLR0,EN);//EN=0
	delay_ms(2);//internal process
}
void CmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,RS);//RS=0, command reg selected
	WriteLCD(cmd);
}
void CharLCD(u8 ascii)
{
	SSETBIT(IOSET0,RS);//RS=1, data reg selected
	WriteLCD(ascii);
}
void InitLCD(void)
{
	WBYTE(IODIR0,LCD_DATA,255); //P0.8 to P0.15 as outputs
	SETBIT(IODIR0,RS);//p0.16 as output
	SETBIT(IODIR0,RW);//p0.17 as output
	SETBIT(IODIR0,EN);//p0.18 as output
	
	delay_ms(15);
	CmdLCD(MODE_8BIT_1LINE);
	delay_ms(5);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DISP_ON_CUR_ON);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
void StrLCD(s8* p)
{
    while(*p)
        CharLCD(*p++);
}

void U32LCD(u32 n)
{
    u8 a[10], i=0;
    if(n==0)
    {
        CharLCD('0');  return;
    }
    while(n)
    {
        a[i++] = n%10 + 48;
        n/=10;
    }
    while(i)
        CharLCD(a[--i]);
}
void S32LCD(s32 n)
{
    if(n<0)
    {
        CharLCD('-');
        n = -n;
    }

    U32LCD(n);
}
void F32LCD(f32 fnum, u8 nDP)
{
    s32 i = fnum;
    f32 f = fnum - i;
    S32LCD(i);
    CharLCD('.');
    while(nDP--)
    {
        f = f * 10;
        CharLCD(((u32)f)%10 + 48);
    }
}
void BuildCGRAM(u8* p, u8 nb)
{
    u8 i;
    CmdLCD(0x40 + nb*8);
    for(i=0;i<8;i++)
        CharLCD(p[i]);
    CmdLCD(GOTO_LINE1_POS0);
}
void HEXLCD(u32 n)
{
    u8 a[8], i=0, t;
    if(n==0)
    {
        CharLCD('0');   return;
    }
    while(n)
    {
        t = n % 16;
        if(t < 10)
            a[i++] = t + 48;
        else
            a[i++] = t + 55;   // A–F
        n /= 16;
    }
    while(i)
        CharLCD(a[--i]);
}
void BinLCD(u32 n, u8 nbd)
{
    s8 i;
    for(i = nbd-1; i >0; i--)
    {
        if((n >> i) & 1)
            CharLCD('1');
        else
            CharLCD('0');
    }
}

