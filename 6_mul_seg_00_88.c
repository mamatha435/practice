//6. Display 00 on two multiplexed segments and make it flash for 5 times and then display 88 and make it flash for 5 times then stop.
#include<LPC21XX.H>

#define SEG1 (1<<8)        // P1.8 enable
#define SEG2 (1<<9)        // P1.9 enable
#define SEG_DATA (0xFF<<8) // P0.8–P0.15

unsigned char segLUT[10] = {
0xC0,0xF9,0xA4,0xB0,0x99,
0x92,0x82,0xF8,0x80,0x90};

void delay_ms(unsigned int s)
{
    s *= 12000;
    while(s--);
}

// Display two digits with multiplexing for given time
void showDigits(unsigned char d1, unsigned char d2, unsigned int time_ms)
{
    unsigned int k;

    for(k = 0; k < time_ms/10; k++)
    {
        // ----- SEG1 : safe single line -----
        IO1PIN = (IO1PIN & ~(SEG1|SEG2)) | SEG1;

        IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[d1] << 8);
        delay_ms(5);

        // ----- SEG2 : safe single line -----
        IO1PIN = (IO1PIN & ~(SEG1|SEG2)) | SEG2;

        IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[d2] << 8);
        delay_ms(5);
    }
}

int main()
{
    unsigned int i;

    IO0DIR |= SEG_DATA;     // data pins output
    IO1DIR |= SEG1 | SEG2;  // enable pins output

    // ===== Flash 00 five times =====
    for(i = 0; i < 5; i++)
    {
        showDigits(0,0,500);   // ON
        delay_ms(300);         // OFF gap
    }

    // ===== Flash 88 five times =====
    for(i = 0; i < 5; i++)
    {
        showDigits(8,8,500);
        delay_ms(300);
    }

    while(1);   // STOP
}

