#include <LPC21xx.h>
//#include "msdelay.h"
void delay(unsigned int);
int main()
{
	IODIR0 = 0xff;
	while(1)
	{
		IOCLR0 = 0xff;
		delayms(500);
		IOSET0 = 0xff;
		delayms(500);
	}
}
/*void delay(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}*/




