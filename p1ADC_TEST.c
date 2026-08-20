//p1.c///ADC_TEST.c
#include<lpc21xx.h>
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK  (CCLK/4)
#define ADCCLK 3000000
#define  CLKDIV ((PCLK/ADCCLK)-1)
#define AIN0 0X00400000
#define AIN1 0X01000000
#define AIN2 0X40000000
#define AIN3 0X10000000
#define CLKDIV_BITS 8
#define START_CONV 24
#define DONE_BIT 31
#define DIGITAL_DATA_BITS  6
#define PDN_BIT 21
void delay_ms(unsigned int ms)
{   for(ms*=12000;ms>0;ms--);}
void Init_ADC(unsigned int  chNo)
{
	PINSEL1&=~(255<<24);
	PINSEL1|=chNo<<24;
	ADCR=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
}
void Read_Adc(unsigned char chNo,unsigned short int *dval,float *eAR)
{
  ADCR&=~15;
  ADCR|=(1<<START_CONV)|(1<<chNo);	
	delay_ms(300);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<START_CONV);
	*dval=((ADDR>>DIGITAL_DATA_BITS)&1023);
	*eAR=(*dval*(3.3/1023));
}
	unsigned short int dval;  	float eAR;
int main(){
	  Init_ADC(1);
  while(1)
  {
	Read_Adc(1,&dval,&eAR);
	}
}
