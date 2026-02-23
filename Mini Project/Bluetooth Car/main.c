#include <LPC21xx.h>
#include "lcd.h"
#include "uart.h"
#include "motor.h"

int main()
{
		unsigned char rxbyte;
	    char i;
		LCD_init();
		LCD_cmd(0x82);
		LCD_str("Bluetooth Car");
		UART_config();
		motor_config();
	    for(i=0;i<16;i++)
			{
				LCD_cmd(0x80+i);
		    LCD_str("Bluetooth Car");
				LCD_cmd(0x01);
			}
		while(1)
		{
			rxbyte = UART_Rx();
			switch (rxbyte)
			{
				case 'F': forward();break;
				case 'B': backward();break;
				case 'R': right();break;
				case 'L': left();break;
				case 'S': stop();break;
			}
		}
}
