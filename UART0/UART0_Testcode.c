/* Write an ECP to test whether the UAR0 is working properly or not in LPC2129*/

#include <LPC21xx.h>
void UART_config(void);
unsigned char UART_Rx(void);
void UART_Tx(unsigned char);

int main()
{
	unsigned char rxbyte;
	PINSEL0=0x05;
	UART_config();
	while(1)
	{
		rxbyte = UART_Rx();
		UART_Tx(rxbyte);
	}		
	
}
void UART_config()
{
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}
unsigned char UART_Rx(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART_Tx(unsigned char Txbyte)
{
	U0THR = Txbyte;
	while(((U0LSR>>5)&1)==0);
}
