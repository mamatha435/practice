//3. PART1: Implement up and down counter. Use two switches and 8 leds (4-active high leds and 4-active low leds) as mentioned: sw1 for incrementing count,
//sw2 for decrementcount and display updated count on leds. Note: if count value is 0, at this time if sw2 pressed it should display 0 only on leds and if
//count value is 255 then if sw1 pressed it should display 255 only on leds
#include <lpc21xx.h>
#define AH 0x0F     // P0.0–P0.3 Active HIGH LEDs
#define AL 0xF0    // P0.4–P0.7 Active LOW LEDs
#define SW1 16    // Increment switch
#define SW2 17    // Decrement switch
//delay
void delay_ms(unsigned int ms)
{
   ms*=12000;
	while(ms--);
}
void LED_Display(unsigned char data)
{       /* Active HIGH LEDs */
    IOCLR0 = AH;
    IOSET0 = data & AH;
         /* Active LOW LEDs */
    IOSET0 = AL;
    IOCLR0 = data & AL;
}
int main()
{
    unsigned char count = 0;
	    PINSEL0 = 0x00;      //  MUST: GPIO mode
    IODIR0 |= 0xFF;   // P0.0–P0.7 LEDs OUTPUT
    IODIR0 &= ~((1<<SW1)|(1<<SW2));//clears the direction bits of P0.16 and P0.17, 
	                                    //configuring them as input pins for switches without affecting other pins.
     LED_Display(count);     // Display initial value (0)
    while(1)
    {     /* Increment */
        if(!(IOPIN0 & (1<<SW1)) && count < 255)
        {
            count++;
            LED_Display(count);
            delay_ms(3);
            while(!(IOPIN0 & (1<<SW1)));//To wait until the switch is released To avoid multiple increments for one press
        }
 /* Decrement */
        if(!(IOPIN0 & (1<<SW2)) && count > 0)
        {
            count--;
            LED_Display(count);
            delay_ms(3);
            while(!(IOPIN0 & (1<<SW2)));   // wait release
        }
    }
}
