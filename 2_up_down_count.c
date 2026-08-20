//2. Write an ECP to Show up counting from 0 to 9 on seg1 and then after show down counting 9 to 0 on seg2 @ of 1sec (approximately).
// Show UP 0-9 on seg1 and DOWN 9-0 on seg2 @1sec
// Show UP 0-9 on SEG1 and DOWN 9-0 on SEG2 @ 1 second
#include<LPC21XX.H>
#define SEG1 (1<<8)        // P1.8 enable
#define SEG2 (1<<9)        // P1.9 enable
#define SEG_DATA (0xFF<<8) // P0.8–P0.15 data lines
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
    int i;

    IO0DIR |= SEG_DATA;      // make P0.8–P0.15 output
    IO1DIR |= SEG1 | SEG2;   // enable pins output

    while(1)
    {
        // ===== UP COUNT ON SEG1 =====
        IO1SET = SEG1;       // enable seg1
        IO1CLR = SEG2;       // disable seg2

        for(i = 0; i <= 9; i++)
        {
            // update only segment bits safely
            IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[i] << 8);
            delay_ms(1000);
        }

        // ===== DOWN COUNT ON SEG2 =====
        IO1SET = SEG2;       // enable seg2
        IO1CLR = SEG1;       // disable seg1

        for(i = 9; i >= 0; i--)
        {
            IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[i] << 8);
            delay_ms(1000);
        }
    }
}

