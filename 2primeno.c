//2. Write an ECP to display binary equivalent of prime numbers within the range of 0-50 @ 5 seconds. (Note: Use IsPrime() function)
#include <lpc21xx.h>
void delay_s(unsigned int s)
{
        s*=12000000;
	while(s--);
}
int IsPrime(int num)
{
    int i;
    if(num < 2) return 0;
    for(i = 2; i <= num / 2; i++)
    {
        if(num % i == 0)   return 0;
    }
    return 1;
}
int main()
{
    int num;
    PINSEL0 = 0x00000000;   // Configure Port0 as GPIO
    IODIR0  = 0x000000FF;   // P0.0–P0.7 as output (LEDs)
    while(1)
    {
        for(num = 0; num <= 50; num++)
        {
            if(IsPrime(num))
            {
                IOCLR0 = 0xFF;   // Clear previous value
                IOSET0 = num;    // Display binary equivalent
                delay_s(5);      // 5-second delay
            }
        }
    }
}


/*
#include <lpc21xx.h>
#define AH_MASK 0x0F     // P0.0–P0.3 Active HIGH LEDs
#define AL_MASK 0xF0     // P0.4–P0.7 Active LOW LEDs
void delay_s(unsigned int sec)
{
    unsigned int i, j;
    for(i = 0; i < sec; i++)
        for(j = 0; j < 12000000; j++);
}
int IsPrime(int num)
{
    int i;
    if(num < 2)
        return 0;

    for(i = 2; i <= num/2; i++)
    {
        if(num % i == 0)
            return 0;
    }
    return 1;
}
void LED_Display(unsigned char data)
{
    IOCLR0 = AH_MASK;
    IOSET0 = data & AH_MASK;

    IOSET0 = AL_MASK;
    IOCLR0 = data & AL_MASK;
}
int main()
{
    int num;
    PINSEL0 = 0x00000000;     // GPIO
    IODIR0  = 0x000000FF;     // P0.0–P0.7 output
    while(1)
    {
        for(num = 0; num <= 50; num++)
        {
            if(IsPrime(num))
            {
                LED_Display(num);
                delay_s(5);  // display for 5 seconds
            }
        }
    }
}
*/
