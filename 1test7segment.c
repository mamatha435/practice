//1. Write an ECP to test seven segment display (all segments) is working or not.
#include<LPC21XX.H>
#define SEG1 (1<<8)
void delay_ms(unsigned int s)
{
    s *= 12000;
    while(s--);
}
int main()
{
    IO0DIR = 0xFF;
    IO1DIR |= SEG1;
    IO1SET = SEG1;   // enable CA display
    while(1)
    {
        IO0CLR = 0xFF;   // All ON
        delay_ms(1000);
        IO0SET = 0xFF;   // All OFF
        delay_ms(1000);
    }
}
