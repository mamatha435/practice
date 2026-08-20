//p6uart.c
#include<lpc21xx.h>
#include "p2lcd.c"

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK  (CCLK/4)
#define BAURD  9600
#define DIVISOR (PCLK/(16*BAURD))

#define DLAB_BIT 7
#define MODE_8BIT 3
#define TEMT_BIT 6
#define DR_BIT 0

#define Tx_INPUT_PIN 0x00000001
#define Rx_INPUT_PIN 0x00000004

#define sLED 16
#define fLED 17
void Init_UART0()
{
	PINSEL0&=~(15<<0);
	PINSEL0|=(Tx_INPUT_PIN)|(Rx_INPUT_PIN);
	U0LCR=(1<<DLAB_BIT)|MODE_8BIT;
	U0DLM=(DIVISOR>>8);
	U0DLL=DIVISOR;
	U0LCR&=~(1<<DLAB_BIT);
}
void U0_TxByte(unsigned char sdat)
{
	U0THR=sdat;
	while(((U0LSR>>TEMT_BIT)&1)==0);
	
}
unsigned char U0_RxByte(void)
{
	while(((U0LSR>>DR_BIT)&1)==0);
	return U0RBR;
}

int main()
{
	IODIR0|=1<<sLED|1<<fLED;
	//unsigned int i;
	Init_UART0();
  while(1)
	{
//	U0_TxByte('A');

	if(U0_RxByte()=='A')
		IOPIN0^=1<<sLED;
	else
		IOPIN0^=1<<fLED;
}
}
