// LED --> p1.17 blink first
//						turn on time -> 1sec
//						turn off time --> 1sec
//and p1.24 blink next
//					turn on time -> 1sec
//					turn off time --> 1sec

#include<lpc21xx.h>

int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	T0PR = 14;											//Prescalar value
	T0MR0 = 1000000;								//1 sec 		//4,000,000,000  == 4000 secs
	T0MR1 = 2000000;								//2 sec
	T0MR2 = 3000000;								//3 sec
	T0MR3	= 4000000;								//4 sec
	T0MCR	= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<10);		//[0 1 1] [0 0 1]		// interrupt | Reset the timer [2 1 0] --> [0 1 1]
	T0TCR	= (1<<0);									//enable timer0	
	while(1)
	{
		if(T0IR & (1<<0))							//[3 2 1 0 ] = [0 0 0 1]//check status of MR0
		{
			IOSET1 = (1<<17);
			T0IR = 1<<0;								//clear the Flag bit0 to 0
		}
		
		if(T0IR & (1<<1))							//[3 2 1 0 ] = [0 0 1 0]//check status of MR1
		{
			IOCLR1 = (1<<17);
			T0IR = 1<<1;								//clear the Flag bit1 to 0
		}
		if(T0IR & (1<<2))							//[3 2 1 0 ] = [0 1 0 0]//check status of MR2
		{
			IOSET1 = (1<<24);
			T0IR = 1<<2;								//clear the Flag bit2 to 0
		}
		
		if(T0IR & (1<<3))							//[3 2 1 0 ] = [1 0 0 0]//check status of MR3
		{
			IOCLR1 = (1<<24);
			T0IR = 1<<3;								//clear the Flag bit3 to 0
		}
	}
}
