//13half_diamond.c

#include <LPC21xx.h>
#include "types.h"
#include "uart.h"

int main()
{
    int i, j;
    int n = 3;   // peak height
    int stars;

    Init_UART0();

    for(i = 1; i <= 2*n - 1; i++)
    {
        // decide number of stars
        if(i <= n)
            stars = i;
        else
            stars = 2*n - i;

        // print stars
        for(j = 1; j <= stars; j++)
        {
            U0_TxByte('*');
        }

        U0_TxByte('\r');
        U0_TxByte('\n');
    }

    while(1);
}
/*

*
**
***
**
*

*/

