#include <LPC21xx.h>

#define F 1<<16
#define B 1<<17
#define R 1<<18
#define L 1<<19

void motor_config(void)
{
	IODIR1 = F|B|R|L;
}
void forward(unsigned char f)
{
	IOSET1 = F;
	IOCLR1 = B|R|L;
}
