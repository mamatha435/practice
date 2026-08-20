//5.Write an ECP to print the binary equivalent of product of the digits for the given integer on LEDS(4-Active High LEDS& 4-Active Low LEDS)
//Note:if the product is >255, Switch on alternate LEDS.
#include <lpc21xx.h>
#define AH_MASK 0x0F     // Active HIGH LEDs (P0.0–P0.3)
#define AL_MASK 0xF0     // Active LOW LEDs  (P0.4–P0.7)
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
    unsigned int num = 2399,digit,product = 1;
    PINSEL0 = 0x00000000;     // GPIO
    IODIR0  = 0x000000FF;     // P0.0–P0.7 as output
    /* Calculate product of digits */
    while(num > 0)
    {
        digit = num % 10;
        product = product * digit;
        num = num / 10;
    }
    if(product <= 255)  LED_Display(product);     // Display binary equivalent
    else                LED_Display(0x55);        // Alternate LEDs ON (01010101)
    while(1);
}
