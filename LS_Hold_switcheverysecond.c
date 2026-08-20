//5. PART2: Implement up and down counter. Use two AL switches and 8 leds (4-active high leds and 4-active low leds) as mentioned:As long as sw1 
//is pressed increment the count value with respect to 1 sec As long as sw2 is pressed decrement count value with respect to 1 sec And display updated 
//count on leds.If both switches are pressed at a time, don’t do any operation on count. Note:if count value is 0, at this time if sw2 pressed it 
//should display 0 only on leds and if count value is 255 then if sw1 pressed it should display 255 only on leds.
#include <lpc21xx.h>
#define SW1 16   // Switch 1 for UP
#define SW2 17   // Switch 2 for DOWN
void delay_ms(unsigned int ms)
{
    ms *= 12000;   // Approx 1ms per loop
    while(ms--);
}
int main()
{
    unsigned char count = 0;
    /* Configure LEDs as output (P0.0 - P0.7) */
    IODIR0 |= 0xFF;
    /* Configure switches as input */
    IODIR0 &= ~((1<<SW1) | (1<<SW2));
    /* Initially all LEDs OFF */
    IOCLR0 = 0xFF;
    while(1)
    {
        /* SW1 pressed ? count UP */
        if(!(IOPIN0 & (1<<SW1)) && (IOPIN0 & (1<<SW2)))
        {
            if(count < 255) count++;       // increment with limit
            IOCLR0 = 0xFF;                 // clear previous LED pattern
            IOSET0 = count;                // display new count
            delay_ms(100);                // 1-second delay
        }
        /* SW2 pressed ? count DOWN */
        else if(!(IOPIN0 & (1<<SW2)) && (IOPIN0 & (1<<SW1)))
        {
            if(count > 0) count--;         // decrement with limit
            IOCLR0 = 0xFF;                 // clear previous LED pattern
            IOSET0 = count;                // display new count
            delay_ms(100);                // 1-second delay
        }
    }
}
