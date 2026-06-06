#include <LPC21xx.h>

#define LCD_D 0xf<<14
#define RS 1<<10
#define E  1<<11

void LCD_init(void);
void LCD_cmd(unsigned int);
void delayms(unsigned int);
void LCD_data(unsigned char);
void LCD_str(unsigned char*);

void delayms(unsigned int ms)
{
	T0PR = 15000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
void LCD_init()
{
	IODIR0 = LCD_D|RS|E;
	LCD_cmd(0x01);
	LCD_cmd(0x02);
	LCD_cmd(0x0C);
	LCD_cmd(0x28);
}

void LCD_cmd(unsigned int cmd)
{
	IOCLR0 = LCD_D;
	IOCLR0 = RS;
	IOSET0 = (cmd&0xf0)<<10;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;

	IOCLR0 = LCD_D;
	IOSET0 = (cmd&0x0f)<<14;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;
}

void LCD_data(unsigned char d)
{
	IOCLR0 = LCD_D;
	IOSET0 = RS;
	IOSET0 = (d&0xf0)<<10;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;

	IOCLR0 = LCD_D;
	IOSET0 = (d&0x0f)<<14;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;
}

void LCD_str(unsigned char* s)
{
	while(*s)
	{
		LCD_data(*s++);
		delayms(20);
	}
}
