// timer0 ---> generate timer interrupt for 2 sec
//					upon 2sec --> blink LED for every 2 sec.

//								PR+1
//Tdelay  =     -------- x (MR)
//								Pclk

//PCLK = 15MHz

#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void timer0_config(void);
void interrupt_config(void);
void timer0_isr1(void) __irq;				//ISR function
//__irq void timer0_isr1(void);
int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	timer0_config();
	interrupt_config();
	while(1)
	{
			blink_LED(24);
	}
}

void interrupt_config(void)
{
	VICIntSelect &= ~(1<<4);			// selecting timer0 as irq
	VICVectCntl2	= (1<<5)|4;			//slot enable | timer0 as peripheral	
	VICVectAddr2	= (long)timer0_isr1;		//loading address
	VICIntEnable	= (1<<4);				//enable timer0
}

void timer0_isr1(void) __irq
{
	blink_LED(17);
	T0IR = (1<<0);			//clear interrupt flag bit
	VICVectAddr	=	0x00000000;		//clear addr reg. space
}

void timer0_config(void)
{
	T0PR = 14;
	T0MR0 = 2000000;
	T0MCR = (1<<0)|(1<<1);
	T0TCR = (1<<0);
}

void blink_LED(int led)
{
	IOSET1 = 1<<led;
	delay(300);				//count by cpu
	IOCLR1 = 1<<led;
	delay(300);				//count by cpu
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
