//4. Write an ECP to Show up counting from 00 to 99 on two multiplexed seven segments @ of 1sec (approximately).
#// Up counting 00 to 99 on two MULTIPLEXED 7-segments @ ~1 sec
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
    unsigned int tens, units, k;

    IO0DIR |= SEG_DATA;     // data lines output
    IO1DIR |= SEG1 | SEG2;  // enable pins

    while(1)
    {
        for(tens = 0; tens <= 9; tens++)
        {
            for(units = 0; units <= 9; units++)
            {
                // ---- display same number for ~1 sec ----
                for(k = 0; k < 100; k++)     // 100 × 10ms ˜ 1 sec
                {
                    // --- SEG1 : tens digit ---
                    IO1SET = SEG1;
                    IO1CLR = SEG2;

                    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[tens] << 8);
                    delay_ms(5);

                    // --- SEG2 : units digit ---
                    IO1SET = SEG2;
                    IO1CLR = SEG1;

                    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[units] << 8);
                    delay_ms(5);
                }
            }
        }
    }
}
