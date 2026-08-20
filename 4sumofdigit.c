//4. Write an ECP to print the binary equivalent of sum of the digits for the given integer on LEDS (4-Active High LEDS& 4-Active Low LEDS).
#include <lpc21xx.h>
#define AH_MASK 0x0F    // P0.0–P0.3 Active HIGH LEDs
#define AL_MASK 0xF0    // P0.4–P0.7 Active LOW LEDs
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
    unsigned int num = 2789,digit, sum = 0;
    PINSEL0 = 0x00000000;      // Configure Port0 as GPIO
    IODIR0  = 0x000000FF;      // P0.0–P0.7 as output
    /* Calculate sum of digits */
    while(num > 0)
    {
        digit = num % 10;
        sum = sum + digit;
        num = num / 10;
    }
    /* Display binary equivalent of sum */
    LED_Display(sum);
    while(1);
}
