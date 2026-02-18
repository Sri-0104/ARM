#include <LPC21xx.h>

void UART_ISR(void) __irq
{
	U0THR = 'A';
	VICVectAddr = 0;
}
void UART_config()
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}
void UART_interrupt()
{
	VICIntSelect = 0;
	VICVectCntl0 = 0x20|6;
  VICVectAddr0 = (unsigned long)UART_ISR;
  VICIntEnable = 1<<6;
  U0IER = 1<<1;	
}
int main()
{
	IODIR0 = 1<<17;
	UART_config();
	UART_interrupt();
	U0THR = 'A';
	while(1)
	{
		if(((IOPIN0>>14)&1)==0)
			IOCLR0 = 1<<17;
		else
			IOSET0 = 1<<17;
	}
}
