#include <lpc21xx.h>
#define EINT0_INPUT_PIN 0x0000000c
#define EINT0_VIC_CHN0 14
#define EINT0_STATUS_LED 16
void eint0_isr(void) __irq;
unsigned int gcount=0;
void delay_ms(unsigned int ms)
{
   for(ms*=12000;ms>0;ms--);
}
int main()
{
	PINSEL0&=~(3<<2);
	PINSEL0|=EINT0_INPUT_PIN;
	VICIntEnable=1<<EINT0_VIC_CHN0;
	VICVectCntl0=(1<<5)|(EINT0_VIC_CHN0);
	VICVectAddr0=(unsigned int)eint0_isr;
	EXTMODE=1<<0;
	IODIR0|=1<<EINT0_STATUS_LED;
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
