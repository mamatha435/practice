//p2lcd.c
#include<lpc21xx.h>
#define LCD_DATA 8
#define RS 16
#define EN 18
#define RW 17
#define CLEAR_LCD 0x01
#define DIS_ON 0x0c
#define DIS_OFF 0x08
#define DIS_ON_CUR_ON 0x0E
#define DIS_ON_CUR_BLINK 0x0F
#define MODE_8BIT_LINE1 0x30
#define MODE_8BIT_LINE2 0x38
#define SHIFT_CUR_RIGHT 0x06
#define GOTO_LINE1_POS0 0x80
#define GOTO_LINE2_POS0 0xC0
#define SETBIT(WORD,BITPOS) (WORD|=1<<BITPOS)
#define SSETBIT(WORD,BITPOS) (WORD=1<<BITPOS)
#define CLRBIT(WORD,BITPOS) (WORD&=~(1<<BITPOS))
#define SCLRBIT(WORD,BITPOS) (WORD=1<<BITPOS)
#define WBYTE(WORD,SBITPOS,BYTE) (WORD=(WORD&~(0xFF<<SBITPOS))|(BYTE<<SBITPOS))
void delay_ms(unsigned int ms)
{  for(ms*=12000;ms>0;ms--);}

void delay_us(unsigned int us)
{  for(us*=12;us>0;us--);}

void writeLCD(unsigned char data)
{
	SCLRBIT(IOCLR0,RW);
	WBYTE(IOPIN0,LCD_DATA,data);
	SSETBIT(IOSET0,EN);
	delay_us(1);
	SCLRBIT(IOCLR0,EN);
  delay_us(2);
}
void CmdLCD(unsigned char cmd)
{
	SCLRBIT(IOCLR0,RS);
	writeLCD(cmd);
}

void CharLCD(unsigned char ascii)
{
	SSETBIT(IOSET0,RS);
	writeLCD(ascii);
}
//void StrLCD(signed char *p)
void StrLCD(char *p)
{
	while(*p)
		CharLCD(*p++);
}
void U32LCD(unsigned int n)
{
	unsigned char a[8];signed int i=0;
  if(n==0)  CharLCD('0');
	else{
     while(n)
	   {		
	      a[i++]=n%10+48;
	      n/=10;
	   }
		 for(--i;i>=0;i--)
		      CharLCD(a[i]);
   }
}
void S32LCD(signed int n)
{
	if(n<0)
	{
		CharLCD('-');
    	n=-n;
	}
	U32LCD(n);
}
void F32LCD(float fn, unsigned char ndp)
{
	unsigned int n,i=0;  //signed int n;
  if(fn<0)  CharLCD('-');
	else{
	  n=fn;
    U32LCD(n);
    CharLCD('.');
    for(i=0;i<ndp;i++)
		{
		  fn=(fn-n)*10;
		  n=fn;
		  CharLCD(n+48);
	 }
	}
}
void HEXLCD(unsigned int n)
{
	unsigned char rem,a[8];   signed char i=0;
	if(n==0) CharLCD('0');
  else
	{
		while(n)
		{
		  rem=n%16;
		  (rem<10)?(rem+=48):(rem+=55);
		  a[i++]=rem;
		  n/=16;
		}
		for(--i;i>=0;i--)
		   CharLCD(a[i]);
	}
}
void InitLCD()
{
	WBYTE(IODIR0,LCD_DATA,255);
	SETBIT(IODIR0,RS);
	SETBIT(IODIR0,RW);
	SETBIT(IODIR0,EN);
	delay_ms(15);
	CmdLCD(MODE_8BIT_LINE1);
	delay_ms(5);
	CmdLCD(MODE_8BIT_LINE1);
	delay_us(100);
	CmdLCD(MODE_8BIT_LINE1);
	CmdLCD(MODE_8BIT_LINE2);
	CmdLCD(DIS_ON_CUR_ON);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
}
