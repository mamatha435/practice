//kpm.c
#include "types.h"
#include "defines.h"
#include <lpc21xx.h>
#include "kpm_defines.h"
#include "lcd.h"
#include "delay.h"

// Look-Up Table (LUT) mapping the physical 4x4 grid to characters
u8 kpmLUT[4][4]={{'1','2','3','/'},
									{'4','5','6','*'},
									{'7','8','9','-'},
									{'C','0','=','+'}};
/* Initialize Keypad Pins */
void InitKPM(void)
{
    // Configure Row pins as Output (WNIBBLE writes 1111 to the row pins in IODIR1)
    WNIBBLE(IODIR1,ROW0,15);
}

/* Check if any key in any column is pressed */
u32 ColScan(void)
{
    // Reads column pins; if value < 15, it means at least one bit is 0 (key pressed)
    return((RNIBBLE(IOPIN1,COL0)<15)?0:1);
}

/* Identify which Row (0-3) contains the pressed key */
u32 RowCheck(void)
{
    u32 rno;
    for(rno=0; rno<4; rno++)
    {
        // Ground only one row at a time (e.g., Row 0 = 1110, Row 1 = 1101)
        WNIBBLE(IOPIN1,ROW0,~(1<<rno));
        
        // If ColScan detects a 0 while this specific row is grounded, this is our row
        if(ColScan()==0)
        {
            break;
        }
    }
    // Reset all rows to ground (default state)
    WNIBBLE(IOPIN1,ROW0,0x0);
    return rno; // Return the row index (0, 1, 2, or 3)
}

/* Identify which Column (0-3) contains the pressed key */
u32 ColCheck(void)
{
    u32 cno;
    for(cno=0; cno<4; cno++)
    {
        // Check each column bit individually to find which one is 0 (pulled low)
        if(RBIT(IOPIN1,(COL0+cno))==0)
        {
            break;
        }
    }
    return cno; // Return the column index (0, 1, 2, or 3)
}

/* Main function to wait for a key and return its character value */
u32 KeyScan(void)
{
    u32 rno,cno,keyv;

    // Wait in a loop until a button is physically pressed (ColScan returns 0)
    while(ColScan());

    // Execute scanning logic to find coordinates
    rno=RowCheck();
    cno=ColCheck();

    // Map the coordinates to the character in the LUT
    keyv=kpmLUT[rno][cno];

    // Wait in a loop until the user releases the button (Debounce/Single-press logic)
    while(!ColScan());
    
    return keyv;
}

/* Read a multi-digit number until '=' is pressed */
u32 ReadNum(void)
{
    u8 key;
    u32 sum=0;
    while(1)
    {
        key=KeyScan();
        // If key is a digit 0-9
        if(key>='0'&&key<='9')
        {
            CharLCD(key);            // Show digit on LCD
            sum=(sum*10)+(key-'0'); // Shift previous digits left and add new one
        }
        else if(key=='=')            // '=' acts as the 'Enter' key
        {
            break;
        }
    }
    return sum;
}

/* Read a specific number of digits (useful for Years or HH:MM) */
u32 ReadNDigitInput(u8 max_digits)
{
    u8 key;
    u8 digits[5]; // Local buffer for digits
    u8 count = 0;

    while(1)
    {
        key = KeyScan();
        
        // Handle Numeric Input
        if(key >= '0' && key <= '9')
        {
            if(count < max_digits)
            {
                digits[count++] = key; // Store character in array
                CharLCD(key);          // Echo to LCD
            }
        }
        // Handle Backspace (Mapped to 'C' on keypad)
        else if(key == 'C' || key == 'c') 
        {
            if(count > 0)
            {
                count--;
                CmdLCD(0x10);   // Move cursor left
                CharLCD(' ');   // Overwrite with blank space
                CmdLCD(0x10);   // Move cursor left again to stay in position
            }
        }
        // Handle Enter (Mapped to '=')
        else if(key == '=')
        {
            if(count > 0)
            {
                u32 val = 0;
                u8 i;
                // Convert stored character array into a single integer
                for(i=0;i<count;i++)
                {
                    val = val*10 + (digits[i]-'0');
                }
                return val; // Return the final numerical value
            }
        }
    }
}
