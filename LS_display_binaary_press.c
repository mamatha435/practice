//2. Write an ECP to display binary equivalent of switch press count on 8-leds (4-active high leds and 4-active low leds)
#include <lpc21xx.h>
#define AH_MASK  0x0F     // P0.0–P0.3  Active HIGH LEDs
#define AL_MASK  0xF0     // P0.4–P0.7  Active LOW LEDs
#define SW1 16            // Switch at P0.16 (Active LOW)
// Display 8-bit data on mixed LEDs 
void LED_Display(unsigned char data)
{
    // Active HIGH LEDs */
    IOCLR0 = AH_MASK;
    IOSET0 = data & AH_MASK;

    // Active LOW LEDs */
    IOSET0 = AL_MASK;
    IOCLR0 = data & AL_MASK;
}
int main()
{
    unsigned char count = 0;
    IODIR0 |= 0xFF; // LED pins as output
    IODIR0 &= ~(1 << SW1);  // Switch pin as input 
    LED_Display(0x00);// Initially all LEDs OFF 
    while(1)
    {
        // If switch pressed 
        if(!(IOPIN0 & (1 << SW1)))
        {
            count++;                // Increment press count
            LED_Display(count);     // Show binary value
            while(!(IOPIN0 & (1 << SW1)));  // Wait until switch released 
        }
    }
}
