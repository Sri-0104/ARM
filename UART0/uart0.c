/*Write an ECP to display a string thru UART0 in LPC2129*/

#include <LPC21xx.h>
void uart0_config(void)
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}
void uart0_tx(unsigned char txbyte)
{
	U0THR = txbyte;
	while(((U0LSR>>5)&1)==0);
}
void uart0_name(char* s)
{
	while(*s)
	{uart0_tx(*s++);}
}
int main()
{
	uart0_config();
	uart0_name("Srisuryaprakash");	
}
