#include "lcd.h"

unsigned char cussym[]={0x17,0x14,0x14,0x1f,0x05,0x05,0x1d,0x00,0x0e,0x0a,0x1b,0x11,0x11,0x11,0x1f,0x00};
void cgram_write(void);

int main()
{
	LCD_init();
	cgram_write();
	//LCD_cmd(0x80);
	while(1)
	{	//LCD_cmd(0x80);
		LCD_data(0);
		delayms(100);
		//LCD_cmd(0x80);
		LCD_data(1);
		delayms(100);
	}
}

void cgram_write()
{
	char i;
	LCD_cmd(0x40);
	for(i=0;i<16;i++)
	LCD_data(cussym[i]);
}

