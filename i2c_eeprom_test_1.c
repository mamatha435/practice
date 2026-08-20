//i2c_eeprom_test_1.c
#include "I2C.h"
#include "I2C_EEPROM.h"
#include <lpc21xx.h>
#define Sled 16
#define Fled 17
u8 dat __attribute__((at(0x40000000)));

int main()
{

	PINSEL0 |= 0x00000050;   // P0.2 SDA, P0.3 SCL
	IODIR1|=(1<<Sled)|(1<<Fled);
	i2c_init();
	i2c_eeprom_write(0x50,0x00,'*');
	dat=i2c_eeprom_read(0x50,0x00);
	//i2c_eeprom_write(0xA0,0x00,'*');
//  dat = i2c_eeprom_read(0xA0,0x00);
	if(dat=='*')
	{
		IOSET1=1<<Sled;
	}
	else
	{
		IOSET1=1<<Fled;
	}
	while(1);
}
