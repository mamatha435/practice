//7. Write an ECP to display the switch press count on two multiplexed seven segment display. (Note: if switch is pressed, need to display the updated count value after switch is released)
// Display switch press count on two multiplexed 7-seg (00–99)
// Update count only AFTER switch release

#include <LPC21XX.H>

#define SEG1 (1<<8)   // P1.8
#define SEG2 (1<<9)   // P1.9
#define SW1  0        // P0.0

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
    unsigned int count = 0, tens, units;

    IO0DIR = 0xFF;        // P0.0–P0.7 ? segment data
    IO0DIR &= ~(1<<SW1);  // P0.0 ? input (switch)

    IO1DIR |= SEG1 | SEG2;   // control pins output
while(1)
{
    // ===== SWITCH HANDLING WITHOUT BLOCKING =====
    if(!(IOPIN0 & (1<<SW1)))      // pressed
    {
        delay_ms(20);             // debounce

        if(!(IOPIN0 & (1<<SW1)))  // still pressed
        {
            // wait for release BUT keep multiplex
            while(!(IOPIN0 & (1<<SW1)))
            {
                // keep showing display
                tens  = count / 10;
                units = count % 10;

                IO0SET = SEG1;
                IO0CLR = SEG2;
                IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[tens] << 8);
                delay_ms(1);

                IO0SET = SEG2;
                IO0CLR = SEG1;
                IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[units] << 8);
                delay_ms(1);
            }
            count++;              // increment AFTER release

            if(count > 99)
                count = 0;
        }
    }
    // ===== NORMAL MULTIPLEX =====
    tens  = count / 10;
    units = count % 10;

    IO0SET = SEG1;
    IO0CLR = SEG2;
    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[tens] << 8);
    delay_ms(1);

    IO0SET = SEG2;
    IO0CLR = SEG1;
    IOPIN0 = (IOPIN0 & ~SEG_DATA) | (segLUT[units] << 8);
    delay_ms(1);
}

}
