// timer0 ---> generate timer interrupt for 2 sec
//					upon 2sec --> blink LED for every 2 sec.

//								PR+1
//Tdelay  =     -------- x (MR)
//								Pclk

//PCLK = 15MHz

// timer0 --> 2sec interrupt and blink LED17
// timer1 --> 4sec interrupt and blink LED20
// background process --> LED24

#include<lpc21xx.h>
void delay(int );
void blink_LED(int );
void timer0_config(void);
void timer1_config(void);
void interrupt_config(void);
void timer0_isr1(void) __irq;				//ISR function for timer0
void timer1_isr2(void) __irq;				//ISR function for timer1
//__irq void timer0_isr1(void);
int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	timer1_config();
	timer0_config();
	T0TCR = (1<<0);
	T1TCR = (1<<0);
	interrupt_config();
	while(1)
	{
			blink_LED(24);
	}
}

void interrupt_config(void)
{
	VICIntSelect &= ~((1<<4)|(1<<5));			// selecting timer0 | timer1 as irq
	VICVectCntl4	= (1<<5)|4;			//slot enable | timer0 as peripheral	
	VICVectAddr4	= (long)timer0_isr1;		//loading address
	VICVectCntl5	= (1<<5)|5;			//slot enable | timer1 as peripheral	
	VICVectAddr5	= (long)timer1_isr2;
	VICIntEnable	= (1<<4)|(1<<5);				//enable timer0
}

void timer0_isr1(void) __irq
{
	blink_LED(17);
	T0IR = (1<<0);			//clear interrupt flag bit
	VICVectAddr	=	0x00000000;		//clear addr reg. space
}

void timer1_isr2(void) __irq
{
	blink_LED(20);
	T1IR = (1<<0);			//clear interrupt flag bit
	VICVectAddr	=	0x00000000;		//clear addr reg. space
}

void timer0_config(void)
{
	T0PR = 14;
	T0MR0 = 2000000;							//2sec
	T0MCR = (1<<0)|(1<<1);

}

void timer1_config(void)
{
	T1PR = 14;
	T1MR0 = 2000000;							//2sec
	T1MCR = (1<<0)|(1<<1);
	
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
