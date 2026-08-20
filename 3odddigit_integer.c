//3. Write an ECP to print the binary equivalent of odd digits in a given integer on 8 LEDS @ 5 seconds.
#include <lpc21xx.h>
void delay_s(unsigned int s)
{
        s*=12000000;
	while(s--);
}
int main()
{
    unsigned int num = 2789,digit;;   // Given integer
    PINSEL0 = 0x00000000;      // Configure Port0 as GPIO
    IODIR0  = 0x000000FF;      // P0.0–P0.7 as output (LEDs)
    while(num > 0)
    {
        digit = num % 10;      // Extract digit
        if(digit % 2 == 1)     // Check if digit is odd
        {
            IOCLR0 = 0xFF;     // Clear LEDs
            IOSET0 = digit;    // Display binary equivalent
            delay_s(5);        // 5-second delay
        }
        num = num / 10;        // Remove last digit
    }
    while(1);
}
