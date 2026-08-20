#include <lpc21xx.h>

#define AH_MASK  0x0F      // P0.0–P0.3 Active HIGH
#define AL_MASK  0xF0      // P0.4–P0.7 Active LOW
void delay_s(unsigned int dlyS)
{
	dlyS*=12000000;
	 while(dlyS--);	
}
void LED_Display(unsigned char data)
{/* Active HIGH LEDs */
    IOCLR0 = AH_MASK;
    IOSET0 = data & AH_MASK;

    /* Active LOW LEDs */
    IOSET0 = AL_MASK;
    IOCLR0 = data & AL_MASK;
}
int main()
{
    int i;
    IODIR0 |= 0xFF;
    while(1)
    {
        for(i=7;i>=0;i--)
        {
            LED_Display(1<<i);
            delay_1s();
        }
    }
}
