#include <LPC21xx.h>
#include "lcd.h"

int temp,i,j;
unsigned char buf[20];
void UART0_ISR(void)  __irq
{
	i=0;
	temp = U0IIR;
	if(temp == 0x04)
	{
		  buf[i]= U0RBR;
			U0THR = buf[i];
		if(buf[i]!=10)
			i++;
		else
		{for(j=0;j<i;j++)
				LCD_data(buf[j]);
		 i=0;
		}
	}
	VICVectAddr = 0;	
}
void UART0_config()
{
	PINSEL0 = 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}

void UART0_int_config()
{
	VICIntSelect = 0;
	VICVectCntl0 = 0x20|6;
	VICVectAddr0 = (unsigned long)UART0_ISR;
	U0IER = (1<<0)|(1<<1);
	VICIntEnable = 1<<6;
}
int main()
{
	IODIR0 = 1<<17;
	LCD_init();
	LCD_cmd(0x80);
	UART0_config();
	UART0_int_config();
	while(1)
	{
		if(((IOPIN0>>14)&1)==0)
				IOCLR0 = 1<<17;
		else
			  IOSET0 = 1<<17;
	}
}
