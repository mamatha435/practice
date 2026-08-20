//6. Write an ECP to print the binary equivalent of power of 2 numbers with in the range of 0-255 @ 5 seconds.
#include <lpc21xx.h>
void delay_s(unsigned int sec)
{
    sec = sec * 12000000;
    while(sec--);
}/*
int main()
{
    unsigned char num = 1;
    IODIR0 = 0xFF;        // P0.0–P0.7 as output (LEDs)
    while(1)
    {
        IOCLR0 = 0xFF;    // Clear previous value
        IOSET0 = num;    // Display binary value
        delay_s(5);      // 5 seconds delay
        num = num << 1;  // Next power of 2
			//num = num * 2;   
        if(num > 255)
            num = 1;     // Roll over
    }
}*/
int main()
{
    unsigned char i, j, power;
    IODIR0 = 0xFF;      // P0.0–P0.7 as output (LEDs)
    while(1)
    {
        for(i = 0; i < 8; i++)   // 2^0 to 2^7
        {
            power = 1;
            // Calculate 2^i dynamically
            for(j = 0; j < i; j++)
                power = power * 2;
            IOCLR0 = 0xFF;     // Clear previous LED value
            IOSET0 = power;    // Display binary on LEDs
            delay_s(5);        // 5-second delay
        }
    }
}
