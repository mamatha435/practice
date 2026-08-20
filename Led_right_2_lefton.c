////2. Write an ECP to display below mentioned patterns on 8-led’s (4-active high led’s and4-active low led’s)
//b. Turn ON one by one led from right to left at the rate of 1 second

#include <lpc21xx.h>
#define AH_MASK  0x0F      // P0.0–P0.3 Active HIGH
#define AL_MASK  0xF0      // P0.4–P0.7 Active LOW

void delay_1s(void)
{
    unsigned int i,j;
    for(i=0;i<1000;i++)
        for(j=0;j<6000;j++);
}

/* Display on mixed LEDs */
void LED_Display(unsigned char data)
{
    /* Active HIGH LEDs */
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
        for(i=0;i<8;i++)
        {
            LED_Display(1<<i);
            delay_1s();
        }
    }
}
