//2. Write an ECP to display the below mentioned patterns on hyper terminal with the helpof UART0 with 19200 baud rates.    ******     ****     *** ** *
//1pattern_uart.c
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
// Function to print pattern
void PrintPattern(void)
{
    s32 i, j;

    for(i = 6; i >= 1; i--)
    {
        for(j = 1; j <= i; j++)
        {
            U0_TxByte('*');
        }

        // Move to next line
        U0_TxString("\r\n");
    }
}

int main()
{
    Init_UART0();   // Initialize UART0 at 19200 baud

    U0_TxString("\r\nPattern Output:\r\n");

    PrintPattern();

    while(1);
}
/*
* * * * * *
* * * *
* * *
* *
*

*/
