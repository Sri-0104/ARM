#include <LPC21xx.h>
#include <string.h>

void uart_init()
{
	PINSEL0|= 0x5;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}

void uart_tx(unsigned char c)
{
 	U0THR=c;
	while(((U0LSR>>5)&1)==0);
}

void uart_str(char*str)
{
	while(*str)
	{
		uart_tx(*str++);
	}
}

unsigned char uart_rx()
{
	while(((U0LSR>>0)&1)==0);
	return U0RBR;
}

 int ESP_waitfor(char* str)
 {
 	char buf[50];
	int i=0;
	char ch;
	while(1)
	{
		if(U0LSR&0x01)
		{
		    ch = U0RBR;
			buf[i++]=ch;

			if(strstr(buf,str))
			return 1;
		}
	}
 }
