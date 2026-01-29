
#include <LPC21xx.h>
void delay_ms(int ms)
{
	unsigned int i;
	for(;ms>=0;ms--)
	for(i=0;i<12000;i++);
}
int main()
{
	unsigned int i=0;
	PINSEL0 = 0;
	IODIR0  = 0x00000001;
	while(i++<10)
	{
		IOSET0  = 0x00000001;
		delay_ms(50);
		IOCLR0  = 0x00000001;
		delay_ms(50);
	}
}
