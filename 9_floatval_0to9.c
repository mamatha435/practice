//9. Display float values from 0.0 to 9.9 on two multiplexed seven segment display.
// Display float 0.0 ? 9.9 on two 7-seg
// SEG1  integer part
// SEG2  decimal part with DP ON

#include <LPC21XX.H>

#define SEG1 (1<<8)
#define SEG2 (1<<9)

unsigned char segLUT[10] = {
0xC0,0xF9,0xA4,0xB0,0x99,
0x92,0x82,0xF8,0x80,0x90};   // CA

void delay_ms(unsigned int s)
{
    s *= 12000;
    while(s--);
}

int main()
{
    unsigned int i, j;

    IO0DIR = 0xFF;            // data lines
    IO1DIR |= SEG1 | SEG2;    // control pins

    while(1)
    {
        for(i=0;i<=9;i++)
        {
            for(j=0;j<=9;j++)
            {
                //---- show integer part ----
                IO1SET = SEG1;
                IO1CLR = SEG2;

                IO0PIN = segLUT[i];
                delay_ms(5);

                //---- show decimal part with DP ----
                IO1SET = SEG2;
                IO1CLR = SEG1;

                IO0PIN = segLUT[j] & 0x7F;   // DP ON
                delay_ms(5);

                delay_ms(990);   // approx 1 sec per value
            }
        }
    }
}
