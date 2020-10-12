#include<LPC21xx.h>		  //header for LPC2129

//	LED RUN --> 17 then 18 then 19 ...... then 24
//	0000 0001
//	0000 0010
//	0000 0100
//	0000 1000
//	0001 0000
//	0010 0000
//	0100 0000
//	1000 0000
	
void delay(int);

int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);//[31 --- [24 23 22 21 20 19 18 17]-----0]
									//0x01FE0000			// [0 0 ----[ 1 1 1 1 1 1 1 1]-------00000]
	while(1)
	{
		for(int led =17;led <= 24; led++)
		{
			IOSET1 = 1<<led;
			delay(100);
			IOCLR1 = 1<<led;
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
