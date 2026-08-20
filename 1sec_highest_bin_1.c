//1. Write an ECP to find the second highest digit in a given integer and display its binary equivalent on 8-LEDS (4-Active High LEDS& 4-Active Low LEDS).
#include <lpc21xx.h>
#define AH_MASK 0x0F      // P0.0–P0.3 Active HIGH
#define AL_MASK 0xF0      // P0.4–P0.7 Active LOW
void LED_Display(unsigned char data)
{ /* Active HIGH LEDs */
    IOCLR0 = AH_MASK;
    IOSET0 = data & AH_MASK;
    IOSET0 = AL_MASK;
    IOCLR0 = data & AL_MASK;
}
int main()
{
    unsigned int num = 278;   // Given integer int digit, highest = -1, second_highest = -1;
   IODIR0  = 0x000000FF;      // P0.0–P0.7 as output
    /* Find highest & second highest digit */
    while(num > 0)
    {
        digit = num % 10;
        if(digit > highest)
        {
            second_highest = highest;
            highest = digit;
        }
        else if(digit > second_highest && digit < highest)
        {
            second_highest = digit;
        }
        num = num / 10;
    }
    /* Display second highest digit in binary */
    LED_Display(second_highest);
    while(1);
}
