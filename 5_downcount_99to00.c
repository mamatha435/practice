//5. Write an ECP to Show down counting from 99 to 00 on two multiplexed seven segments @ of 1sec (approximately).
// Down counting 99 to 00 on multiplexed 7-segments @ ~1 sec
#include<LPC21XX.H>

#define SEG1 (1<<8)        // P1.8
#define SEG2 (1<<9)        // P1.9
#define SEG_DATA (0xFF<<8) // P0.8–P0.15

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
    int tens, units, k;

    IO0DIR |= SEG_DATA;
    IO1DIR |= SEG1 | SEG2;

    while(1)
    {
        for(tens = 9; tens >= 0; tens--)
        {
            for(units = 9; units >= 0; units--)
            {
                // Hold each number ~1 sec
                for(k = 0; k < 100; k++)
                {
                    // ---- SEG1 : tens ----
                    IO1SET = SEG1;
                    IO1CLR = SEG2;

                    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[tens] << 8);
                    delay_ms(5);

                    // ---- SEG2 : units ----
                    IO1SET = SEG2;
                    IO1CLR = SEG1;

                    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[units] << 8);
                    delay_ms(5);
                }
            }
        }
    }
}

