//2. Write an ECP to display below mentioned patterns on 8-led’s (4-active high led’s and4-active low led’s)
//a. Turn ON one by one led from left to right at the rate of 1 second
//left to right shift led on
#include <lpc21xx.h>
#define AH_MASK  0x0F     // Active HIGH LEDs
#define AL_MASK  0xF0     // Active LOW LEDs
void delay_1s(void)
{
    unsigned int i, j;  for(i = 0; i < 1000; i++) for(j = 0; j < 6000; j++);
}
void LED_Display(unsigned char data)
{ /* Active HIGH LEDs */
    IOCLR0 = AH_MASK;
    IOSET0 = data & AH_MASK;
    /* Active LOW LEDs */
    IOSET0 = AL_MASK;
    IOCLR0 = data & AL_MASK;
}
int main(void)
{
    unsigned char data; int i;
    /* P0.0 – P0.7 as OUTPUT */
    IODIR0 |= 0xFF;
    while(1)
    {
        /* From LED7 to LED0 (Left ? Right) */
        data = 0x80;   // Start with LED7

        for(i = 0; i < 8; i++)
        {
            LED_Display(data);
            delay_1s();
            data >>= 1;   // Shift right
        }
    }
}
