//6. Write an ECP to fulfill the below mentioned operations.      1. Initially all leds should be off.
//2. Display even numbers on 8 leds with respect to 1 second if sw1 is pressed. Continue this process until sw2 is pressed.
//3. Display odd numbers on 8 leds with respect to 1 second if sw2 is pressed.Continue this process until sw1 is pressed.
//Note: if number is >255 then roll over to 0 and repeat the operation.
#include <lpc21xx.h>
#define SW1 16
#define SW2 17
void delay_ms(unsigned int ms)
{
    ms *= 12000;
    while(ms--);
}
int main()
{
    unsigned char num = 0;
    /* LEDs as output (P0.0–P0.7) */
    IODIR0 |= 0xFF;
    /* Switches as input */
    IODIR0 &= ~((1<<SW1) | (1<<SW2));
    /*1.Initially all LEDs OFF */
    IOCLR0 = 0xFF;
    while(1)
    {
        /* EVEN numbers when SW1 is pressed */
        while(!(IOPIN0 & (1<<SW1)))
        {
            IOCLR0 = 0xFF;
            IOSET0 = num & 0xFE;   // force even
            delay_ms(1000);
            num += 2;
            if(num > 255)//Roll Over Logic
                num = 0;

            if(!(IOPIN0 & (1<<SW2)))
                break;
        }
        /* ODD numbers when SW2 is pressed */
        while(!(IOPIN0 & (1<<SW2))) //used to continue operation until other switch is pressed
        {
            IOCLR0 = 0xFF;
            IOSET0 = num | 0x01;   // force odd
            delay_ms(1000);
            num += 2;
            if(num > 255)//Roll Over Logic
                num = 1;
            if(!(IOPIN0 & (1<<SW1)))
                break;
        }
    }
}

