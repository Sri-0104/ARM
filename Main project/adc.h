#include <lpc21xx.h>

void ADC_Init()
{
    PINSEL1 |= (1 << 24);   // P0.28 as AD0.1
    AD0CR = (1 << 1)        // Select channel AD0.1
          | (4 << 8)        // Clock division
          | (1 << 21);      // Enable ADC
}

unsigned int ADC_Read()
{
    AD0CR |= (1 << 24);          // Start conversion

    while (!(AD0GDR & (1 << 31)));  // Wait till DONE = 1

    return (AD0GDR >> 6) & 0x3FF;   // Extract 10-bit result
}
