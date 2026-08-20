//6increasing_number_triangle.c

#include <LPC21xx.h>
#include "types.h"
#include "uart.h"

int main()
{
    int i, j;
    int n = 4;  // number of rows

    Init_UART0();

    for(i = 1; i <= n; i++) // rows
    {
        for(j = 1; j <= i; j++) // print numbers 1 to i
        {
            U0_TxByte('0' + j);
        }

        U0_TxByte('\r');
        U0_TxByte('\n'); // next row
    }

    while(1);
}
/*
1
12
123
1234

*/
