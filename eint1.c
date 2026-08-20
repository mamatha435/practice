//eint1.c
#include <lpc21xx.h>
#define EINT0_INPUT_PIN 0x0000000C
#define EINT0_VIC_CHN0 14
#define EINT0_STATUS_LED 16
#define EINT1_INPUT_PIN 0x000000C0
#define EINT1_VIC_CHN0 15
#define EINT1_STATUS_LED 17
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
unsigned int gcount=0;
void delay_ms(unsigned int ms)
{
   for(ms*=12000;ms>0;ms--);
}
int main()
{
	PINSEL0&=~(3<<2)|(3<<6);
	PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;
	VICIntEnable=1<<EINT0_VIC_CHN0|1<<EINT1_VIC_CHN0;
	VICVectCntl0=(1<<5)|(EINT0_VIC_CHN0);
	VICVectAddr0=(unsigned int)eint0_isr;
	VICVectCntl1=(1<<5)|(EINT1_VIC_CHN0);
	VICVectAddr1=(unsigned int)eint1_isr;
	EXTMODE=1<<1|1<<0;
	IODIR0|=1<<EINT0_STATUS_LED|1<<EINT1_STATUS_LED;
  while(1)
	{
		gcount++;
	}
}
void eint0_isr(void) __irq
{
	IOSET0 = 1<<EINT0_STATUS_LED;
delay_ms(100);
IOCLR0 = 1<<EINT0_STATUS_LED;
	
	EXTINT=1<<0;
		VICVectAddr=0;
}
void eint1_isr(void) __irq
{
	IOSET0 = 1<<EINT1_STATUS_LED;
delay_ms(100);
IOCLR0 = 1<<EINT1_STATUS_LED;
	
	EXTINT=1<<1;
		VICVectAddr=0;
}