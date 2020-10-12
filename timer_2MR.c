#include<lpc21xx.h>

int main()
{
//	VPBDIV = 0x02;									//30 MHz PCLK Freq
//	VPBDIV = 0x01;									//60 MHz PCLK Freq
	int count=0;
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	T0PR = 14;											//Prescalar value
	T0MR0 = 2000000;								//4 sec 		//4,000,000,000  == 4000 secs
	T0MR1 = 4000000;								//8 sec
	T0MCR	= (1<<0)|(1<<3)|(1<<4);		//[0 1 1] [0 0 1]		// interrupt | Reset the timer [2 1 0] --> [0 1 1]
	T0TCR	= (1<<0);									//enable timer0	
	while(1)
	{
		count++;
		if(T0IR & (1<<0))							//[3 2 1 0 ] = [0 0 0 1]//check status of MR0
		{
			IOSET1 = (0xFF<<17);
			T0IR = 1<<0;								//clear the Flag bit to 0
		}
		
		if(T0IR & (1<<1))							//[3 2 1 0 ] = [0 0 1 0]//check status of MR1
		{
			IOCLR1 = (0xFF<<17);
			T0IR = 1<<1;								//clear the Flag bit to 0
		}
//		if(count >= 10 && count<20)
//		{
//			VPBDIV = 0x02;
//		}
//		if (count >= 20)
//		{ 
//			VPBDIV = 0x01;
//		} 
	
	}
}
