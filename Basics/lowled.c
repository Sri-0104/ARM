#include <lpc21xx.h>

void delay(int d)
{
	int i;
	for(;d>0;d--)
	{
		for(i=12000;i>0;i--);
	}
}
int main()
{
	IODIR0=(1<<13)|(1<<7);
		IOCLR0=(1<<13)|(1<<7);
		delay(2000);
		IOSET0=(1<<13)|(1<<7);
		delay(200);
	
}

