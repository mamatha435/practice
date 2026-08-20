//einto_eint1_irq_test.c
#include "types.h"
#include<lpc21xx.h>
#define EINT0_INPUT_PIN 0x0000000C     //(1<<2)//po.1
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16

#define EINT1_INPUT_PIN 0x000000C0     //(1<<6)//po.3
#define EINT1_VIC_CHNO 15
#define EINT1_STATUS_LED 17

#define EINT2_INPUT_PIN 0x0000C000     //(1<<6)//po.3
#define EINT2_VIC_CHNO 16
#define EINT2_STATUS_LED 18
void eint0_fiq_isr(void) __irq;
void eint1_virq_isr(void) __irq;
void eint2_nvirq_isr(void) __irq;
u32 gcount;
int main()
{
	//cfg EINT0,EINT1 pins
	PINSEL0&=((u32)~3<<14)|((u32)~3<<6)|((u32)3<<2);
	PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN|EINT2_INPUT_PIN;
	
	VICIntSelect=1<<EINT0_VIC_CHNO;
	VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO|1<<EINT2_VIC_CHNO;;
	VICVectCntl0=(1<<5)|EINT1_VIC_CHNO;
	VICVectAddr0=(u32)eint1_virq_isr;
	
	EXTMODE=((1<<2)|(1<<1));//edge sensitive
	IODIR1=1<<EINT0_STATUS_LED|1<<EINT1_STATUS_LED|1<<EINT2_STATUS_LED;
	while(1)
	{
		gcount++;
	}
}
void eint0_fiq_isr(void) __irq
{
	IOPIN1^=1<<EINT0_STATUS_LED;
	EXTINT=1<<0;
}
void eint1_virq_isr(void) __irq
{
	IOPIN1^=1<<EINT1_STATUS_LED;
	EXTINT=1<<1;
	VICVectAddr=0;
}
void eint2_nvirq_isr(void) __irq
{
	IOPIN1^=1<<EINT2_STATUS_LED;
	EXTINT=1<<2;
	VICVectAddr=0;
}
/*eint_debug.ini*/
/*DEFINE BUTTON "TGL_EINT_PINS","Toggle EINT Pins (1,3)"
FUN void Toggle_EINTPins(unsigned pin1,unsigned pins2)
{
	PORT0^=((1<<pin1)|(1<<pin2));
}*/
