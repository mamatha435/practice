//einto_eint1_irq_test.c
#include "types.h"
#include<lpc21xx.h>
#define EINT0_INPUT_PIN 0x0000000C     //(1<<2)//po.1
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16

#define EINT1_INPUT_PIN 0x000000C0     //(1<<6)//po.3
#define EINT1_VIC_CHNO 15
#define EINT1_STATUS_LED 17

void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
u32 gcount;
int main()
{
	//cfg EINT0,EINT1 pins
	PINSEL0&=((u32)~3<<2)|((u32)~3<<6);
	PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;
	
	VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO;
	
	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
	VICVectAddr0=(u32)eint0_isr;
	
	VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;
	VICVectAddr1=(u32)eint1_isr;
	
	EXTMODE=((1<<1)|(1<<0));//edge sensitive
	IODIR1=1<<EINT0_STATUS_LED|1<<EINT1_STATUS_LED;
	while(1)
	{
		gcount++;
	}
}
void eint0_isr(void) __irq
{
	IOPIN1^=1<<EINT0_STATUS_LED;
	EXTINT=1<<0;
	VICVectAddr=0;
}
void eint1_isr(void) __irq
{
	IOPIN1^=1<<EINT1_STATUS_LED;
	EXTINT=1<<1;
	VICVectAddr=0;
}
/*eint_debug.ini*/
/*DEFINE BUTTON "TGL_EINT_PINS","Toggle EINT Pins (1,3)"
FUN void Toggle_EINTPins(unsigned pin1,unsigned pins2)
{
	PORT0^=((1<<pin1)|(1<<pin2));
}*/
/*
//interrupt.c
#include <lpc214x.h>
#include "interrupt.h"

extern void eint0_isr(void);
extern void eint1_isr(void);

void InitInterrupts(void)
{
    // P0.1 = EINT0
    PINSEL0 &= ~(3<<2);
    PINSEL0 |=  (1<<2);

    // P0.3 = EINT1
    PINSEL0 &= ~(3<<6);
    PINSEL0 |=  (1<<6);

    EXTMODE  = 0x03;     // Edge sensitive
    EXTPOLAR = 0x00;     // Falling edge

    EXTINT = 0x03;

    VICIntEnable = (1<<14) | (1<<15);

    VICVectCntl0 = (1<<5) | 14;
    VICVectAddr0 = (u32)eint0_isr;

    VICVectCntl1 = (1<<5) | 15;
    VICVectAddr1 = (u32)eint1_isr;
}*/
