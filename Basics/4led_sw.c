#include <LPC21xx.h>
#define AL_LED1 1<<4
#define AL_LED2 1<<5
#define AL_LED3 1<<6
#define AL_LED4 1<<7
#define AL_SW1 8 
#define AL_SW2 9
#define AL_SW3 10
#define AL_SW4 11
int main()
{
	IODIR0 = 0xf0;
	while(1)
	{
		if(((IOPIN0>>8)&1)==0)
			IOCLR0=AL_LED1;
		else
			IOSET0=AL_LED1;
		if(((IOPIN0>>9)&1)==0)
			IOCLR0=AL_LED2;
		else
			IOSET0=AL_LED2;
		if(((IOPIN0>>10)&1)==0)
			IOCLR0=AL_LED3;
		else
			IOSET0=AL_LED3;
		if(((IOPIN0>>11)&1)==0)
			IOCLR0=AL_LED4;
		else
			IOSET0=AL_LED4;
		/*else if(((AL_SW3>>10)&1)==0)
		IOCLR0=AL_LED3;
		else if(((AL_SW4>>11)&1)==0)
		IOCLR0=AL_LED4;
		else
			IOSET0=0xF0;*/
	}
}

