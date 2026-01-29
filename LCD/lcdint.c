#include "lcd.h"
void LCD_int(int);
void LCD_float(float);
int main()
{
	LCD_init();
	LCD_cmd(0x80);
	LCD_int(0);
	LCD_cmd(0x88);
	LCD_int(-14);
	LCD_cmd(0xc0);
	LCD_int(4567);
	LCD_cmd(0xc7);
	LCD_float(44.37);
}
void LCD_float(float fl)
{
	int num=fl;
	LCD_int(num);
	LCD_data('.');
	num=(fl-num)*100;
	LCD_int(num);
}

void LCD_int(int n)
{
	if(n==0)
		LCD_data('0');
	else
	{
		int i=0;
		int a[5];
		if(n<0)
		{LCD_data('-');
			n=-n;}
		while(n!=0)
		{
			a[i]=n%10;
			n=n/10;
			i++;
		}
			for(i=i-1;i>=0;i--)
			LCD_data(a[i]+48);
		
	}
		
}
