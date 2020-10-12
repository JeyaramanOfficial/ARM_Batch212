//p1.25 as i/p ---> button 
//in IODIR [31---------[25]---------0] == 
//						[000-------[0]-------0000]

#include<lpc21xx.h>

void delay(int);

int main()
{
	int flag = 0;
	IODIR1 |= (0xFF<<17);		//LED pins as op
	IODIR1 = IODIR1 & ~(1<<25);		//p1.25 as ip
	while(1)
	{
		if(IOPIN1 & (1<<25))  // check status // once
		{
			if(flag == 0)				//1	3
			{
				IOSET1 = 1<<17;
				delay(500);
				flag = 1;
			}
			else if(flag ==1)		//2 4
			{
				IOCLR1 = 1<<17;
				delay(500);
				flag = 0;
			}
		}
	}
}

void delay(int ct)
{
	for(int i=0;i<ct;++i)
	{
		for(int j=0;j<6000;j++)
		{}
	}
}

// press once ---> LED ON STATE
// press next ---> LED OFF STATE

//make use of flag value 
