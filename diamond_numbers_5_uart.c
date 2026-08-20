//16diamond_numbers_5_uart.c

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

// Function to print required diamond pattern
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

        // Descending numbers from 5
        for(j = 5; j >= 5 - i + 1; j--)
        {
            U0_TxByte(j + '0');
        }

        // Ascending numbers
        for(j = 5 - i + 2; j <= 5; j++)
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

        // Descending numbers from 5
        for(j = 5; j >= 5 - i + 1; j--)
        {
            U0_TxByte(j + '0');
        }

        // Ascending numbers
        for(j = 5 - i + 2; j <= 5; j++)
        {
            U0_TxByte(j + '0');
        }

        U0_TxString("\r\n");
    }
}

int main()
{
    Init_UART0();   // UART0 at 19200 baud

    U0_TxString("\r\nDiamond Pattern With Numbers:\r\n");

    PrintDiamondNumbers();

    while(1);
}
/*
Diamond Pattern With Numbers:

    5
   545
  54345
 5432345
543212345
 5432345
  54345
   545
    5
//diamond_numbers_alt.c

#include <LPC21xx.h>
#include "types.h"
#include "uart.h"

void U0_TxString(s8 *p)
{
    while(*p)
    {
        U0_TxByte(*p);
        p++;
    }
}

void PrintDiamondNumbers(void)
{
    s32 row, col;
    s32 n = 5;          // size
    s32 total = 2*n-1;  // total rows

    for(row = 1; row <= total; row++)
    {
        // Determine number count for this row
        s32 count;

        if(row <= n)
            count = row;
        else
            count = total - row + 1;

        // Print spaces
        for(col = 1; col <= n - count; col++)
        {
            U0_TxByte(' ');
        }

        // Print numbers
        for(col = 1; col <= 2*count-1; col++)
        {
            s32 num;

            if(col <= count)
                num = n - col + 1;
            else
                num = n - (2*count - col) + 1;

            U0_TxByte(num + '0');
        }

        U0_TxString("\r\n");
    }
}

int main()
{
    Init_UART0();   // 19200 baud

    U0_TxString("\r\nDiamond Pattern With Numbers:\r\n");

    PrintDiamondNumbers();

    while(1);
}
*/
