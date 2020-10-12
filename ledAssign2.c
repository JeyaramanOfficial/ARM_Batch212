#include<LPC21xx.h>		  //header for LPC2129

//	Assign 2
//	pattern blinking
//	0000 0001		== 0x01  == 1
//	0000 0010
//	0000 0011
//	0000 0100
//	0000 0101
//	0000 0110
//	0000 0111
//	0000 1000
//	.....
//	1111 1111  == 0xFF	== 255
	
void delay(int);

int main()
{
	int val;
	IODIR1 = IODIR1 | (0xFF<<17);//[31 --- [24 23 22 21 20 19 18 17]-----0]
									//0x01FE0000			// [0 0 ----[ 1 1 1 1 1 1 1 1]-------00000]
	while(1)
	{
		for(val =0x01;val <= 0xFF; val++)
		{
			IOSET1 = val<<17;
			delay(100);
			IOCLR1 = val<<17;
			delay(100);
		}
	}
}
void delay(int ct)
{
	int i,j;
	for(i=0;i<ct;++i)
	{
		for(j=0;j<6000;++j)				//6000 x 1000 == 1sec (Approx)
		{}
	}
}
