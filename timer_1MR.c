// timer0 ---> generate timer interrupt for 2 sec
//					upon 2sec --> blink LED for every 2 sec.

//								PR+1
//Tdelay  =     -------- x (MR)
//								Pclk

//PCLK = 15MHz

#include<lpc21xx.h>
void delay(int );
void blink_LED(int );

int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	T0PR = 14;					//Prescalar value
	T0MR0 = 500000;		//500msec 		//4,000,000,000  == 4000 secs
	T0MCR	= (1<<0)|(1<<1);			// interrupt | Reset the timer [2 1 0] --> [0 1 1]
	T0TCR	= (1<<0);			//enable timer0	
	while(1)
	{
		blink_LED(24);
		if(T0IR & (1<<0))			//check status of MR0
		{
			blink_LED(17);
			T0IR = 1<<0;			//clear the Flag bit to 0
		}
	}
}

void blink_LED(int led)
{
	IOSET1 = 1<<led;
	delay(1000);				//count by cpu
	IOCLR1 = 1<<led;
	delay(1000);				//count by cpu
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
