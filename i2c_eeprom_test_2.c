//i2c_eeprom_test_2.c
#include "I2C.h"
#include "I2C_EEPROM.h"
#include <lpc21xx.h>
#include <string.h>
#define Sled 16
#define Fled 17
char rbuff[11] __attribute__((at(0x40000000)));

int main()
{
  char wbuff[]="0123456789";
	IODIR1|=(1<<Sled)|(1<<Fled);
	i2c_init();

	i2c_eeprom_page_write(0x50,0x20,wbuff,10);
	i2c_eeprom_seq_read(0x50,0x20,rbuff,10);
	if(strcmp(rbuff,wbuff)==0)
	{
		IOSET1=1<<Sled;
	}
	else
	{
		IOSET1=1<<Fled;
	}
	while(1);
}
