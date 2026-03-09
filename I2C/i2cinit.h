#include <LPC21xx.h>

#define SCL 0x10
#define SDA 0x40

#define Cclk 60000000
#define Pclk Cclk/4
#define I2C_speed 100000
#define LOADVAL ((Cclk/I2C_speed)/2)

#define  AA_BIT   2
#define  SI_BIT   3
#define  STO_BIT  4
#define  STA_BIT  5
#define  I2EN_BIT 6

typedef unsigned char u8;
typedef signed   char s8;
typedef unsigned short u16;
typedef signed   short s16;
typedef unsigned int  u32;
typedef signed   int  s32;
typedef float  f32;
typedef double f64;


void i2c_init()
{
	 PINSEL0 = 	SCL|SDA; //configured p0.2 and p0.3 as SCL and SDA pins
	 I2SCLL =	LOADVAL;
	 I2SCLH =   LOADVAL;
	 I2CONSET = 1<<I2EN_BIT;
}

void i2c_start()
{
	I2CONSET = 1<<STA_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 1<<STA_BIT;
}

void i2c_stop(void)

{
	// issue stop condition
	I2CONSET=1<<STO_BIT;
   // clr SI bit status	
	I2CONCLR = 1<<SI_BIT;
   //stop will cleared automatically	
}

void i2c_restart(void)
{
	// start condition
	I2CONSET=1<<STA_BIT;
	//clr SI_BIT
	I2CONCLR=1<<SI_BIT;
	//wait for SI bit status
	while(((I2CONSET>>SI_BIT)&1)==0);
	// clear start condition
	I2CONCLR=1<<STA_BIT;
}

void i2c_write(u8 dat)
{
	//put data into I2DAT
	I2DAT=dat;	
	//clr SI_BIT
	I2CONCLR = 1<<SI_BIT;
	//wait for SI bit status
	while(((I2CONSET>>SI_BIT)&1)==0);	
}

u8 i2c_nack(void)
{	
	I2CONSET = 0x00; //Assert Not of Ack
    I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}

u8 i2c_masterack(void)
{	
	I2CONSET = 0x04; //Assert Ack
    I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 0x04; //Clear Assert Ack
 	return I2DAT;
}

