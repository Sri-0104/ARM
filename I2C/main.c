#include <LPC21xx.h>
#include "i2cinit.h"
#include "delay.h"
#include <string.h>

#define gLED 1<<16 //P1.16
#define rLED 1<<17 //P1.17

void i2c_eeprom_write(u8,u8,u8);
u8 i2c_eeprom_read(u8,u8);
void i2c_eeprom_page_write(u8,u8,u8*,u8);
void i2c_eeprom_seq_read(u8,u8,char*,u8);

int main()
{
	//u8 ch;
	char*p;
	//u8*p;
	IODIR1=gLED|rLED;
	i2c_init();	

	/*i2c_eeprom_write(0x50,0x00,'A');  // random byte write
	ch = i2c_eeprom_read(0X50,0x00);  // random byte read

    if(ch=='A')
		 IOPIN1=gLED;	
	else
		 IOPIN1=rLED;
	while(1);*/

	i2c_eeprom_page_write(0x50,0x00,"Vectors",7);// pagewrite
	i2c_eeprom_seq_read(0x50,0x00,p,7);			 // sequential read

	if(strcmp(p,"Vectors")==0)
		 IOPIN1=gLED;	
	else
		 IOPIN1=rLED;
	while(1);
}

void i2c_eeprom_write(u8 slaveAddr,u8 wBuffAddr,u8 dat)

{
    i2c_start();	
    i2c_write(slaveAddr<<1); //slaveAddr + w
	i2c_write(wBuffAddr);    //wBuffAddr
	i2c_write(dat);    //data
	i2c_stop();
	delay_ms(10);
}

u8 i2c_eeprom_read(u8 slaveAddr,u8 rBuffAddr)

{
	u8 dat;
	i2c_start();	
    i2c_write(slaveAddr<<1); //slaveAddr + w
	i2c_write(rBuffAddr);    //rBuffAddr
	i2c_restart();	
	i2c_write(slaveAddr<<1|1); //slaveAddr + r  
    dat=i2c_nack();	
	i2c_stop();
	return dat;
}

void i2c_eeprom_page_write(u8 slaveAddr,u8 wBuffStartAddr,u8 *p,u8 nBytes)
{
  u8 i;
  i2c_start();	
  i2c_write(slaveAddr<<1);    //slaveAddr + w
	i2c_write(wBuffStartAddr);  //wBuffStartAddr
	for(i=0;i<nBytes;i++)
	{
	   i2c_write(p[i]);             //wBuffAddr
	}
	i2c_stop();
	delay_ms(10);
}

void i2c_eeprom_seq_read(u8 slaveAddr,u8 rBuffStartAddr,char *p,u8 nBytes)
{
	u8 i;
	i2c_start();	
    i2c_write(slaveAddr<<1); //slaveAddr + w
	i2c_write(rBuffStartAddr);    //rBuffAddr
	i2c_restart();	
	i2c_write(slaveAddr<<1|1); //slaveAddr + r
	for(i=0;i<nBytes-1;i++)
	{
    p[i]=i2c_masterack();	
	}
	p[i]=i2c_nack();
	i2c_stop();
}
