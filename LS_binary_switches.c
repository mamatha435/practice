//4. Write an ECP to print the binary equivalent of switch press count within 500 milliseconds. Note: Time slice should start after the first switch press
#include <lpc21xx.h>
#define SW1 16   // Switch at P0.16 (active LOW)
void delay_ms(unsigned int ms)
{
     ms*=1200;
     while(ms--);
}
int main()
{
    unsigned char count = 0;
    unsigned int time = 0;
    IODIR0 |= 0xFF;           // P0.0–P0.7 LEDs as output
    IODIR0 &= ~(1 << SW1); //Switch as input
    IOCLR0 = 0xFF;        //Initially all LEDs OFF 
    while(IOPIN0 & (1 << SW1));    // WAIT FOR FIRST SWITCH PRESS
    while(time < 500)    //500 ms COUNT WINDOW
    {
        if(!(IOPIN0 & (1 << SW1)))
        {
            count++;              // count press
            delay_ms(20);         // debounce
            while(!(IOPIN0 & (1 << SW1))); // wait release
        }
        delay_ms(1);
        time++;
    }
    /* ---- DISPLAY BINARY COUNT ---- */
    IOCLR0 = 0xFF;
    IOSET0 = count;   // binary output on LEDs
    while(1);
}
