#include <LPC21xx.h>

void delay(unsigned int ms)
{
	T0PR= 15000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void ESP_cmd(char*cmd,unsigned int ms)
{
	uart_str(cmd);
	delay(ms);
}
