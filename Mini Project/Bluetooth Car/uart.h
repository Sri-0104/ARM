#include <LPC21xx.h>

void UART_config(void);
unsigned char UART_Rx(void);

void UART_config(void)
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}

unsigned char UART_Rx(void)
{
	while((U0LSR&0)==0);
	return U0RBR;
}

