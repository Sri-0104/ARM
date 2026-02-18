#include <LPC21xx.h>

#define M1F 1<<16
#define M1B 2<<16
#define M2F 1<<18
#define M2B 2<<18

void motor_config(void)
{
	IODIR1 = M1F|M1B|M2F|M2B;
}
void forward()
{
	IOCLR1 = M1F|M2F|M1B|M2B;
	IOSET1 = M1F|M2F;
	//IOCLR1 |= M1B|M2B;
}
void backward()
{
	IOCLR1 = M1F|M2F|M1B|M2B;
	IOSET1 = M1B|M2B;
	//IOCLR1 |= M1F|M2F;
}
void left ()
{
	if( IOPIN1==(M1F|M2F|M1B|M2B))  // in stop condition
		IOSET1 = M1F;		   // right wheel forward and left wheel stop
	if(	IOPIN1 == (M1B|M2B) )	   // in reverse condition
		IOCLR1 = M2B;		  //  right wheel backward and left wheel stop
	if(	IOPIN1 == (M1F|M2F) )	   // in forward condition
		IOCLR1 = M2F;		   // right wheel forward and left wheel stop
	if((IOPIN1== M2F)&&(((IOPIN1>>16)&1)==0)&&(((IOPIN1>>17)&1)==0)) // right forward and left stop
	{
		IOCLR1 = M2F;
		IOSET1 = M1F;
	}
}
void right ()
{
	if( IOPIN1==(M1F|M2F|M1B|M2B))  // in stop condition
		IOSET1 = M2F;		   // right wheel stop and left wheel forward
	if(	IOPIN1 == (M1B|M2B) )	   // in reverse condition
		IOCLR1 = M1B;		  //  right wheel stop and left wheel backward
	if(	IOPIN1 == (M1F|M2F) )	   // in forward condition
		IOCLR1 = M1F;		   // right wheel stop and left wheel forward
	if((IOPIN1== M1F)&&(((IOPIN1>>18)&1)==0)&&(((IOPIN1>>19)&1)==0)) // right stop and left forward
	{
		IOCLR1 = M1F;
		IOSET1 = M2F;
	}
}

void stop()
{
	IOCLR1 = M1F|M1B|M2F|M2B;
}	
