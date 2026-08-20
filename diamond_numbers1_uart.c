//15diamond_numbers1_uart.c
#include <LPC21xx.h>
#include "types.h"
#include "uart.h"
// Function to send string
void U0_TxString(s8 *p)
{
    while(*p)
    {
        U0_TxByte(*p);
        p++;
    }
}

// Function to print diamond numbers
void PrintDiamondNumbers(void)
{
    s32 i, j;

    // Upper half
    for(i = 1; i <= 5; i++)
    {
        // Spaces
        for(j = 1; j <= 5 - i; j++)
        {
            U0_TxByte(' ');
        }

        // Ascending numbers
        for(j = 1; j <= i; j++)
        {
            U0_TxByte(j + '0');
        }

        // Descending numbers
        for(j = i - 1; j >= 1; j--)
        {
            U0_TxByte(j + '0');
        }

        U0_TxString("\r\n");
    }

    // Lower half
    for(i = 4; i >= 1; i--)
    {
        // Spaces
        for(j = 1; j <= 5 - i; j++)
        {
            U0_TxByte(' ');
        }

        // Ascending numbers
        for(j = 1; j <= i; j++)
        {
            U0_TxByte(j + '0');
        }

        // Descending numbers
        for(j = i - 1; j >= 1; j--)
        {
            U0_TxByte(j + '0');
        }

        U0_TxString("\r\n");
    }
}

int main()
{
    Init_UART0();   // UART0 initialized at 19200 baud

    U0_TxString("\r\nDiamond Pattern With Numbers:\r\n");

    PrintDiamondNumbers();

    while(1);
}
/*
    1
   121
  12321
 1234321
123454321
 1234321
  12321
   121
    1
*/
