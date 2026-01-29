/*#include "lcd.h"

void LCD_str(char*);

int main()
{
	char i;
	//LCD_init();
	//LCD_cmd(0x80);
	while(1)
	{	//LCD_cmd(0x80);
	for(i=0;i<16;i++)
		{	
			LCD_init();
			LCD_cmd(0x80+i);
			LCD_str("Embedded");
			delayms(500);
			//delayms(300);
		}
	}
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
*/

#include "lcd.h"

#define LCD_WIDTH 16

void LCD_str(char *);

int main()
{
    char pos;
    char text[] = "SrisuryaprakashMJ";      // 8 chars
    char buf[17];
    int i, j;

    LCD_init();

    while(1)
    {
        for(pos = 0; pos < LCD_WIDTH; pos++)
        {
            /* Step 1: fill buffer with spaces */
            for(i = 0; i < LCD_WIDTH; i++)
                buf[i] = ' ';
            buf[16] = '\0';

            /* Step 2: place string with wrap */
            for(i = 0; text[i] != '\0'; i++)
            {
                j = pos + i;
                if(j >= LCD_WIDTH)
                    j = j - LCD_WIDTH;

                buf[j] = text[i];
            }

            /* Step 3: display */
            LCD_cmd(0x80);
            LCD_str(buf);

            delayms(500);
        }
    }
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

