#include <LPC21xx.h>
#define LCD_D 0xff<<0
#define RS 1<<8
#define E 1<<9

void delayms(unsigned int);
void LCD_init(void);
void LCD_cmd(unsigned int);
void LCD_data(unsigned int);
void LCD_str(char*);
void LCD_int (int);
void LCD_float(float);

void delayms(unsigned int ms)
{
	T0PR = 15000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
void LCD_init()
{
	LCD_cmd(0x01);
	LCD_cmd(0x02);
	LCD_cmd(0x0C);
	LCD_cmd(0x38);
}
void LCD_cmd(unsigned int cmd)
{
	IOCLR0 = LCD_D;
	IOSET0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;
}
void LCD_data(unsigned int d)
{
	IOCLR0 = LCD_D;
	IOSET0 = d;
	IOSET0 = RS;
	IOSET0 = E;
	delayms(2);
	IOCLR0 = E;
}
void LCD_str(char* s)
{
	while(*s)
		LCD_data(*s++);
}
void LCD_int(int n)
{
	signed int i=0;
	char arr[5];
	if(n==0)
		LCD_data('0');
	else if(n<0)
	{
		LCD_data('-');
		n=-n;
	}	
	while(n)
	{
		arr[i++]=n%10;
		n=n/10;
		//i++;
	}
		for(i=i-1;i>=0;i--)
			LCD_data(arr[i]+48);
}

void LCD_float(float float_num)
{
	int n;
  n	= float_num;
	LCD_int (n);
	LCD_data('.');
	n=(float_num-n)*100;
	LCD_int(n);
}
int main()
{
	IODIR0 = LCD_D|RS|E;
	LCD_init();
	
	while(1)
	{
		LCD_cmd(0x80);
		//LCD_data('A');
		//LCD_str("Surya");
		//LCD_int(-56);
		//LCD_cmd(0x85);
		//LCD_int(0);
		LCD_cmd(0xc0);
		LCD_float(23.55);
	}
}
