//i2c_eeprom.c
#include "delay.h"
#include "types.h"
#include "i2c.h"
void i2c_eeprom_write(u8 slaveAddr,
	                    u8 wBuffAddr,
                      u8 dat)
{
 //Issue Start Condition to begin this frame
 i2c_start();
 //Issue 7bit SA+W Option
 i2c_write(slaveAddr<<1);
 //Issue Buffer Address for Writing
 i2c_write(wBuffAddr);  
 //Issue Data for That Write Buffer
 i2c_write(dat); 
 //Issue Stop Condition to end this frame
 i2c_stop();
 //Delay Period between Consecutive Writes
 delay_ms(10);
}

u8 i2c_eeprom_read(u8 slaveAddr,u8 rBuffAddr)
{
 u8 dat;
 //Issue Start Condition
	i2c_start();
  //Issue SA + W Option
	i2c_write(slaveAddr<<1);
  //Issue Address of Buffer to be Read
  i2c_write(rBuffAddr);
  //Issue re-start condition
	i2c_restart();
  //Issue SA + R Option
	i2c_write((slaveAddr<<1)|1);
  //Give Not of Ack After Reading only/last Byte
  dat=i2c_nack();
  //Issue stop condition
	i2c_stop();
  //return read byte
  return dat;
}


void i2c_eeprom_page_write(u8 slaveAddr,
                           u8 wBuffStartAddr,
                           s8 *p,
                           u8 nBytes)
{
  u8 i;
  i2c_start();
  i2c_write(slaveAddr<<1); 
  i2c_write(wBuffStartAddr); 
  for(i=0;i<nBytes;i++)
  {
   i2c_write(p[i]); 
  }
  i2c_stop();
  delay_ms(10);
}


void i2c_eeprom_seq_read(u8 slaveAddr,
                         u8 rBuffStartAddr,
                         s8 *p,
                         u8 nBytes)
{
  u8 i;
  i2c_start();
  i2c_write(slaveAddr<<1); 
  i2c_write(rBuffStartAddr); 
  i2c_restart();
  i2c_write(slaveAddr<<1|1);
  for(i=0;i<nBytes-1;i++)
  {
   p[i]=i2c_mack();
  }
  p[i]=i2c_nack();
	p[i+1]='\0';
  i2c_stop();
}

