//multiplex_7_seg_00_to_99.c
#include<lpc21xx.h>
#include "types.h"
#include "delay.h"
#define CA7SEG 8 //p0.8 to p0.15
#define SEG1 16 //p0.16
#define SEG2 17 //p0.17
u8 segLUT[10]={0xC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

int main()
{
	s32 i,dly;
	IODIR0|=255<<CA7SEG|1<<SEG1|1<<SEG2;
	for(i=0; i<100; i++)
	{
		for(dly=100; dly>0; dly--)
		{
		IOPIN0=(IOPIN0&~(255<<CA7SEG))|(segLUT[i/10]<<CA7SEG);
		IOSET0=1<<SEG1;// seg1 ON
		delay_ms(1);
		IOCLR0=1<<SEG1;//seg1 OFF
		IOPIN0=(IOPIN0&~(255<<CA7SEG))|(segLUT[i%10]<<CA7SEG);
		IOSET0=1<<SEG2;//seg2 ON
		delay_ms(1);
		IOCLR0=1<<SEG2;// seg2 OFF 
		}
	}
	while(1);
}
