//einto_test.c
#include "types.h"
#include "delay.h"
#include<lpc21xx.h>
#define EINT0_INPUT_PIN 0x0000000C     //(1<<2)//po.1
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
void eint0_isr(void) __irq;
u32 gcount;
int main()
{
	//cfg EINT0,EINT1 pins
	PINSEL0&=((u32)~3<<2);
	PINSEL0|=EINT0_INPUT_PIN;
	
	VICIntEnable=1<<EINT0_VIC_CHNO;
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	VICVectAddr0=(u32)eint0_isr;
	EXTMODE=1<<0;//edge sensitive
	IODIR1=1<<EINT0_STATUS_LED;
	while(1)
	{
		gcount++;
	}
}
void eint0_isr(void) __irq
{
	IOPIN1^=1<<EINT0_STATUS_LED;
	delay_ms(100);
	EXTINT=1<<0;
	VICVectAddr=0;
}


