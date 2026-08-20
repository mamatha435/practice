//3. Write an ECP to display numbers 0-9 on two segments @ 1sec in the below given format. Even numbers on segment 1 and odd numbers on segment2
// Even on SEG1 , Odd on SEG2 @1sec
// Display 0-9 : EVEN on SEG1, ODD on SEG2 @1sec
#include<LPC21XX.H>

#define SEG1 (1<<8)         // P1.8 enable
#define SEG2 (1<<9)         // P1.9 enable
#define SEG_DATA (0xFF<<8)  // P0.8–P0.15 data

unsigned char segLUT[10] = {
0xC0,0xF9,0xA4,0xB0,0x99,
0x92,0x82,0xF8,0x80,0x90};

void delay_ms(unsigned int s)
{
    s *= 12000;
    while(s--);
}

int main()
{
    unsigned int i;

    IO0DIR |= SEG_DATA;     // segment data output
    IO1DIR |= SEG1 | SEG2;  // enable pins output

    while(1)
    {
        for(i = 0; i <= 9; i++)
        {
            // Load digit safely on P0.8–P0.15
            IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[i] << 8);

            // ----- SINGLE STATEMENT -----//IO1PIN = (i % 2 == 0) ? SEG1 : SEG2;
            IO1PIN = (i & 1) ? SEG2 : SEG1;

            delay_ms(1000);
        }
    }
}
