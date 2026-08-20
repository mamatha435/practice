//i2c.c
#include <lpc21xx.h>
#include "i2c_defines.h"
#include "types.h"

void i2c_init(void)
{
	PINSEL0&=(u32)~15<<(SCL*2);
	PINSEL0=SCL_PIN_FUNC|SDA_PIN_FUNC;
	I2SCLL=LOADVAL;
	I2SCLH=LOADVAL;
	I2CONSET=1<<I2EN_BIT;	
}

void i2c_start(void)
{
  //issue start condition
  I2CONSET=1<<STA_BIT;
  //wait for SI bit status
  while(((I2CONSET>>SI_BIT)&1)==0);
  // clear start condition
	I2CONCLR=1<<STAC_BIT;
}

void i2c_stop(void)
{
  // issue stop condition
	I2CONSET=1<<STO_BIT;
  //clear SI bit status
  I2CONCLR=1<<SIC_BIT;
  //stop bit will clear automatically
}

void i2c_restart(void)
{
  //start condition
	I2CONSET=1<<STA_BIT;
  //clear SIC_BIT to initiate re-start
	I2CONCLR=1<<SIC_BIT;
  //wait for SI bit status
	while(((I2CONSET>>SI_BIT)&1)==0);
  //clear start condition
	I2CONCLR=1<<STAC_BIT;
}

void i2c_write(u8 dat)
{
 //put data into I2DAT
 I2DAT=dat;
 //clear SIC_BIT to initiate serialization out
 I2CONCLR=1<<SIC_BIT;
 //wait for SI bit status
 while(((I2CONSET>>SI_BIT)&1)==0);
}

u8 i2c_nack(void)
{
 //Assert Not of Ack
 //I2CONSET=0<<AA_BIT;
 //Clear SIC bit initiates serializaion in
 I2CONCLR=1<<SIC_BIT;
 //wait for byte reception
 while(((I2CONSET>>SI_BIT)&1)==0);
 //read received byte;
 return I2DAT; 
}

u8 i2c_mack(void)
{
 //Assert Ack
 I2CONSET=1<<AA_BIT;
 //Clear SI bit
 I2CONCLR=1<<SIC_BIT;
 //Wait for SI Bit
 while(((I2CONSET>>SI_BIT)&1)==0);
 //Clear Assert Ack
 I2CONCLR=1<<AAC_BIT;
 //read read byte
 return I2DAT;
}
