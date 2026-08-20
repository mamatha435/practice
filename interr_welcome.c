#include<lpc21xx.h>
#include "lcd.h"
#include "LCD_defines.h"
#include "delay.h"
#define EINT0_INPUT_PIN 0x0000000C     //(1<<2)//po.1
#define EINT0_VIC_CHNO 14
#define EINT0_STATUS_LED 16
// Interrupt Service Routine for EINT0
void eint0_isr(void) __irq
{
	  IOPIN1^=1<<EINT0_STATUS_LED;
    // Move cursor to 2nd line
    CmdLCD(0xC0);
    // Display message on 2nd line
    StrLCD("Interrupt Fired");
    delay_ms(1000);   // wait 1 second
    // Clear only 2nd line (print spaces)
    CmdLCD(0xC0);//2nd line
    StrLCD("                "); // 16 spaces
    // Clear interrupt flag
    EXTINT = 1 << 0;
    // End of interrupt
    VICVectAddr = 0;
}
int main()
{
	InitLCD();
	 // Display WELCOME on 1st line
  CmdLCD(GOTO_LINE1_POS0);//0x80
	StrLCD(" WELCOME ");
    // Configure P0.1 as EINT0  
    	PINSEL0&=((u32)~3<<2);
	    PINSEL0|=EINT0_INPUT_PIN;
    // Enable EINT0 in VIC
   // VICIntSelect = 0;
	  VICIntEnable = 1 << EINT0_VIC_CHNO;
    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)eint0_isr;
    VICIntEnable = 1 << EINT0_VIC_CHNO;	
	IODIR1=1<<EINT0_STATUS_LED;
	  // Configure interrupt as falling edge triggered
    EXTMODE = 1 << 0;
    EXTPOLAR = 0 << 0;

    while(1);		
}
