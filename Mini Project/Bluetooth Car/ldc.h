#include <LPC21xx.h>

#define LCD_D 0xff<<2
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
	LCD_cmd(0x38);
}

void LCD_cmd(unsigned int cmd)
{
	IOCLR0 = LCD_D;
	IOCLR0 = RS;
	IOSET0 = cmd;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;
}

void LCD_data(unsigned char d)
{
	IOCLR0 = LCD_D;
	IOSET0 = RS;
	IOSET0 = d;
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
