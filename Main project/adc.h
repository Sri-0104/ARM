#include <LPC21xx.h>

void adc_init()
{
	PINSEL1|=0x400000;
	ADCR |= 0x1;	  // to select ADC channel 0 input
	ADCR |= (1<<10);  //to divide pclk(15mhz)by 4 to make it as less than 4.5mhz for adc
	ADCR |=	(1<<21); //to make adc operational
}
int adc_read()
{
    ADCR |= (1 << 24);          // Start conversion
    while (!(ADDR & (1UL<<31)));  // Wait till DONE = 1
    return ((ADDR >> 6) & 0x3FF);   // Extract 10-bit result
}
