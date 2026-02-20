#include <LPC21xx.h>

void UART_config(void);
unsigned char UART_Rx(void);

void UART_config(void)
{
	PINSEL0 = 0x50000;
	U1LCR = 0x83;
	U1DLL = 97;
	U1DLM = 0;
	U1LCR = 0x03;
}

unsigned char UART_Rx(void)
{
	while((U1LSR&1)==0);
	return U1RBR;
}
