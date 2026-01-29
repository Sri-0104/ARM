/*Write an ECP to display A to Z in 16x2 LCD alphanumeric display using LPC2129*/
#include <LPC21xx.h>
#include "delayms.h" // Including the header file of delay in milliseconds

void LCD_init(void);					// funcion declaration of LCD initialisation
void LCD_cmd(unsigned int);   // funcion declaration of LCD command
void LCD_data(unsigned int);  // funcion declaration of LCD data 

#define LCD_D 0xff<<0  // Port 0.0 to 0.7 connected to D0 to D7 of LCD
#define RS 1<<8        // Port 0.8 connected to Register Select pin of LCD
#define E 1<<9         // Port 0.9 connected to Enable pin of LCD


void LCD_init()
{
	IODIR0=LCD_D|RS|E;  // P0.0 to P0.9 - Data pins and display control pins are configured as output
	LCD_cmd(0x01);      // Clear the display
	LCD_cmd(0x02);      // Put the cursor in the home position
	LCD_cmd(0x0C);      // Display ON, Cursor OFF
	LCD_cmd(0x38);			// 8 bits interfacing mode with both lines
	
}

void LCD_cmd(unsigned int cmd)
{
	IOCLR0 = LCD_D;     // clearing all the data pins
	IOSET0 = cmd;				// writing the command in the pin
	IOCLR0 = RS;				// clear the RS pin to select command register
	IOSET0 = E;					// set the enable pin
	delayms(2);					// wait for 2 seconds to complete the internal operation done by register and customised controller
	IOCLR0 = E;					// clear the enable pin
}

void LCD_data(unsigned int d)
{
	IOCLR0 = LCD_D;     // clearing all the data pins
	IOSET0 = d;					// writing the data in the pin
	IOSET0 = RS;				// set the RS pin to select data register
	IOSET0 = E;					// set the enable pin to latch the data from pin to the lcd display
	delayms(2);					// wait for 2 seconds to complete the internal operation done by register and customised controller
	IOCLR0 = E;					// clear the enable pin to let know the controller that lcd is ready to accept the next byte data
}
