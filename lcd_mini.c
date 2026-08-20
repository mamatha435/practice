//LCD.c
#include<lpc21xx.h>    
#include "LCD_defines.h" 
#include "types.h"       
#include "defines.h"   
#include "delay.h"       

/* Core function to send a byte to the LCD hardware */
void WriteLCD(u8 data)
{
    SCLRBIT(IOCLR0,RW);    // Set RW=0 (Select Write operation)
    WBYTE(IOPIN0,LCD_DATA,data); // Place the 8-bit data/command onto P0.8-P0.15
    SSETBIT(IOSET0,EN);    // Set Enable high (Start the pulse)
    delay_us(1);           // Hold pulse for a brief moment
    SCLRBIT(IOCLR0,EN);    // Set Enable low (Falling edge latches data into LCD)
    delay_ms(2);           // Wait for LCD to process the instruction internally
}

/* Sends a command byte (like clear screen or move cursor) */
void CmdLCD(u8 cmd)
{
    SCLRBIT(IOCLR0,RS);    // Set RS=0 (Select Command Register)
    WriteLCD(cmd);         // Call Write function to send the command
}

/* Sends an ASCII character to be displayed on the screen */
void CharLCD(u8 ascii)
{
    SSETBIT(IOSET0,RS);    // Set RS=1 (Select Data Register)
    WriteLCD(ascii);       // Call Write function to send the character data
}

/* Initializes the LCD hardware into 8-bit mode */
void InitLCD(void)
{
    WBYTE(IODIR0,LCD_DATA,255); // Configure P0.8 to P0.15 as Output pins for Data
    SETBIT(IODIR0,RS);    // Configure RS pin (P0.16) as Output
    SETBIT(IODIR0,RW);    // Configure RW pin (P0.17) as Output
    SETBIT(IODIR0,EN);    // Configure EN pin (P0.18) as Output
    
    delay_ms(15);         // Wait for LCD power-up stabilization
    CmdLCD(MODE_8BIT_1LINE); // Force 8-bit mode (Initialization sequence part 1)
    delay_ms(5);          // Wait
    CmdLCD(MODE_8BIT_1LINE); // Force 8-bit mode (Initialization sequence part 2)
    delay_us(100);        // Wait
    CmdLCD(MODE_8BIT_1LINE); // Force 8-bit mode (Initialization sequence part 3)
    
    CmdLCD(MODE_8BIT_2LINE); // Set to 8-bit mode, 2-line display, 5x7 font
    CmdLCD(DISP_ON_CUR_ON);  // Turn display ON and show cursor
    CmdLCD(CLEAR_LCD);       // Clear any random garbage from screen
    CmdLCD(SHIFT_CUR_RIGHT); // Set cursor to move right after each character
}

/* Displays a string (null-terminated) on the LCD */
void StrLCD(s8* p)
{
    while(*p)             // Loop until the end of the string ('\0')
        CharLCD(*p++);    // Send current character and move to next memory address
}

/* Converts an unsigned 32-bit integer to a string and displays it */
void U32LCD(u32 n)
{
    u8 a[10], i=0;        // Buffer to store digits (max 10 digits for u32)
    if(n==0)
    {
        CharLCD('0');     // If number is 0, just print '0'
        return;
    }
    while(n)              // Extract digits from right to left
    {
        a[i++] = n%10 + 48; // Get remainder (last digit) and convert to ASCII ('0'=48)
        n/=10;            // Remove the last digit
    }
    while(i)              // Print digits in correct order (reverse of extraction)
        CharLCD(a[--i]);
}

/* Displays a signed integer (handles negative sign) 
void S32LCD(s32 n)
{
    if(n<0)               // If number is negative
    {
        CharLCD('-');     // Print minus sign
        n = -n;           // Convert to positive for U32LCD function
    }
    U32LCD(n);            // Use the unsigned function to print the digits
}*/
