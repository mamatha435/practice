//1. Create a display on 8 LED’s (4-active high and 4-active low) using 4 active low switches connected to port0 (0.16-0.19) in the pattern explained:
//a. First all LEDs should be OFF.
//b) if 1st switch is pressed, LED 0 and LED 7 (P0.0 and P0.7) should be ON
//c) if 2nd switch is pressed, LED 1 and LED 6 (P0.1 and P0.6) should be ON
//d) if 3rd switch is pressed, LED 2 and LED 5 (P0.2 and P0.5) should be ON
//e) if 4th switch is pressed, LED 3 and LED 4 (P0.3 and P0.4) should be ON
#include <lpc21xx.h>
#define AH 0x0F   // P0.0 - P0.3 Lower 4 LEDs (Active HIGH)
#define AL 0xF0   // P0.4 - P0.7  Upper 4 LEDs (Active LOW)
#define SW1 16
#define SW2 17
#define SW3 18
#define SW4 19
void delay_ms(unsigned int ms)
{
   ms*=12000;
	while(ms--);
}
/* Function to display a byte on LEDs (4 active-high, 4 active-low) */
void LED_Display(unsigned char data)
{
    /* Lower 4 LEDs (Active HIGH) */
    IOCLR0 = AH;          // Turn off lower LEDs
    IOSET0 = data & AH;   // Turn ON LEDs corresponding to 1s in lower 4 bits

    /* Upper 4 LEDs (Active LOW) */
    IOSET0 = AL;          // Turn off upper LEDs (set high = OFF)
    IOCLR0 = data & AL;   // Turn ON LEDs corresponding to 1s in upper 4 bits
}
int main()
{
    /* Configure LEDs as output */
    IODIR0 |= 0xFF;            // P0.0 - P0.7 ? output

    /* Configure switches as input */
    IODIR0 &= ~((1<<SW1) | (1<<SW2) | (1<<SW3) | (1<<SW4));

    while(1)
    {
        LED_Display(0x00);  // Initially all LEDs OFF

        /* Check switches (active low) */
        if(!(IOPIN0 & (1<<SW1)))
            LED_Display((1<<0) | (1<<7));  // LED0 + LED7

        else if(!(IOPIN0 & (1<<SW2)))
            LED_Display((1<<1) | (1<<6));  // LED1 + LED6

        else if(!(IOPIN0 & (1<<SW3)))
            LED_Display((1<<2) | (1<<5));  // LED2 + LED5

        else if(!(IOPIN0 & (1<<SW4)))
            LED_Display((1<<3) | (1<<4));  // LED3 + LED4

        delay_ms(5);  // Small delay for switch debounce
    }
}
