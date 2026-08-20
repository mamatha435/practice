//i2c_eeprom.h
#include "types.h"
void i2c_eeprom_write(u8 slaveAddr,
	                    u8 wBuffAddr,
                      u8 dat);
u8 i2c_eeprom_read(u8 slaveAddr,
                   u8 rBuffAddr);
void i2c_eeprom_page_write(u8 slaveAddr,
	                         u8 wBuffStartAddr,
                           s8 *p,
                           u8 nBytes);
void i2c_eeprom_seq_read(u8 slaveAddr,
	                       u8 rBuffStartAddr,
                         s8 *p,
                         u8 nBytes);

