#include <LPC21xx.h>
#include "lcd.h"
#include "uart.h"
#include "motor.h"

int main()
{
		unsigned char rxbyte;
		LCD_init();
		LCD_cmd(0x82);
		LCD_str("Bluetooth Car");
		UART_config();
		motor_config();
		while(1)
		{
			rxbyte = UART_Rx();
			switch (rxbyte)
			{
				case 'F':	;
			}
		}
}




