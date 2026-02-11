/*     1) While configuring EINT0 as FIQ , we cannot use VICVectAddrx register as there is no slot for the FIQ. 
       2) Also there is a default jump address for the FIQ ISR to execute that is defined in Startup.c file.
       3) We should change the ISR definition's keyword as fiq and remove the "VICVectAddr=0" as it is meaningless.         */

#include <LPC21xx.h>
#define LED 1<<17 

void EINT0_FIQ(void) __fiq 
{
	EXTINT = 0x01;
	IOSET0 = LED;
	IOCLR0 = LED;
	//VICVectAddr = 0;
}
int main()
{
	int count =0;
	IODIR0 = LED;
	PINSEL1 = 0x01;
	VICIntSelect = 1<<14;
	EXTMODE = 0x00;
	EXTPOLAR = 0x00;
	VICIntEnable =1<<14;
	while (1)
	{
		count++;
	}
}
// Code replaced in Startup.c
/*EXPORT FIQ_Handler
IMPORT EINT0_FIQ
FIQ_Handler     B       EINT0_FIQ
*/ 
