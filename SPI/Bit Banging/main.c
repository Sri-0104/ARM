#include <LPC21xx.h>
#include <math.h>

#define CLK  1<<4
#define MOSI 1<<5
#define MISO 1<<6
#define CS   1<<7

int main()
{
	int i=11;
	short int val=0;
	IODIR0 = MOSI|CLK|CS;
	IOSET0 = CS;
	while(1)
	{
	IOCLR0 = CS;
	//start 
	IOCLR0 = CLK;
	IOSET0 = MOSI;
	IOSET0 = CLK;
	//Single ended transfer
	IOCLR0 = CLK;
	IOSET0 = MOSI;
	IOSET0 = CLK;
	// D2 -> dont care bit in MCP3204
	IOCLR0 = CLK;
	IOSET0 = CLK;
	// D1,D0 = 00 for selecting Mode0 or 11 for Mode3
	IOCLR0 = CLK;
	IOCLR0 = MOSI;
	IOSET0 = CLK;

	IOCLR0 = CLK;
	IOCLR0 = MOSI;
	IOSET0 = CLK;
	// Wait for one clock cycle to sample and hold period.
	IOCLR0 = CLK;
	IOSET0 = CLK;
	// Wait for clock cycle to ignore the null bit
	IOCLR0 = CLK;
	IOSET0 = CLK;
	// Read 12 bits-> 12 clock cycles which is MSB first to LSB last
	while(i>=0)
	{
		IOCLR0 = CLK;
		if((IOPIN0>>MISO)&1)
			val=val+(pow(2,i));
		--i;
		IOSET0 = CLK;	
	}
	// Make CS as HIGH to stop communication
	IOSET0 = CS;
	}
}
