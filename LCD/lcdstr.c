#include "lcd.h"
void LCD_str(char*);

int main()
{
	LCD_init();
	LCD_cmd(0x80);
	LCD_str("Advanced Embedded Systems");
}

void LCD_str(char *s)
{int i=0;
	while(*s)
	{
		LCD_data(*s++);
		i++;
		if(i==16)
			LCD_cmd(0xc0);
	}
}

