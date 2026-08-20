//8. Implement a 2 digit up and down counter. Use two switches as mentioned: sw1 - incrementing count & sw2 - decrement count. Note: if count value is 0, then if sw2 pressed it should display 00 only and if count value is 99 then if sw1 pressed it should display 99 only.
// 2-digit UP/DOWN counter using two switches
// SW1 ? increment
// SW2 ? decrement
// limit 00 to 99 only

#include <LPC21XX.H>

#define SEG1 (1<<8)
#define SEG2 (1<<9)

#define SW1  0
#define SW2  1

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
    int count = 0, tens, units;

    IO0DIR = 0xFF;                     // P0 ? segment data
    IO0DIR &= ~((1<<SW1)|(1<<SW2));    // switches input

    IO1DIR |= SEG1 | SEG2;             // control pins output

    while(1)
    {
        //---- SW1 : INCREMENT ----
        if(!(IOPIN0 & (1<<SW1)))
        {
            while(!(IOPIN0 & (1<<SW1)));   // wait release

            if(count < 99)
                count++;
        }

        //---- SW2 : DECREMENT ----
        if(!(IOPIN0 & (1<<SW2)))
        {
            while(!(IOPIN0 & (1<<SW2)));   // wait release

            if(count > 0)
                count--;
        }

        tens  = count / 10;
        units = count % 10;

        //---- MULTIPLEX DISPLAY ----

        // tens digit
        IO1SET = SEG1;
        IO1CLR = SEG2;

        IO0PIN = segLUT[tens];
        delay_ms(5);
/*IO1PIN = (IO1PIN & ~(SEG1|SEG2)) | SEG1;
IO0PIN = segLUT[tens];
delay_ms(5);*/

        // units digit
        IO1SET = SEG2;
        IO1CLR = SEG1;

        IO0PIN = segLUT[units];
        delay_ms(5);
    }
}
