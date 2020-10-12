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
void eint1_isr(void) __irq;
//__irq void timer0_isr1(void);
int main()
{
	IODIR1 = IODIR1 | (0xFF<<17);		//LED pins as output
	IODIR0 |= (1<<11);
	timer1_config();
	timer0_config();
	interrupt_config();
	while(1)
	{
			blink_LED(24);
	}
}

void interrupt_config(void)
{
	PINSEL0 |= (1<<29);
	PINSEL0 &= ~(1<<28);													//p0.14 ---> EINT1
	VICIntSelect &= ~((1<<4)|(1<<5)|(1<<15));			// selecting timer0 | timer1 | EINT1 as irq
	VICVectCntl1	= (1<<5)| 15;										//slot enable | peripheral
	VICVectAddr1	=	(long)eint1_isr;
	VICVectCntl4	= (1<<5)|4;												//slot enable | timer0  as peripheral	
	VICVectAddr4	= (long)timer0_isr1;								//loading address
	VICVectCntl5	= (1<<5)|5;													//slot enable | timer1 as peripheral	
	VICVectAddr5	= (long)timer1_isr2;
	VICIntEnable	= (1<<4)|(1<<5)|(1<<15) ;				//enable timer0
	EXTMODE = (1<<1);														//EINT1	--> Edge triggered(1)
	EXTPOLAR	= (1<<1);														// Rising edge(1)
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

void eint1_isr(void) __irq
{
	IOSET0 = 1<<11;
	delay(300);				//count by cpu
	IOCLR0 = 1<<11;
	delay(300);				//count by cpu
	EXTINT  = (1<<1);
	VICVectAddr = 0x00000000;
}

void timer0_config(void)
{
	T0PR = 14;
	T0MR0 = 2000000;							//2sec
	T0MCR = (1<<0)|(1<<1);
	T0TCR = (1<<0);
}

void timer1_config(void)
{
	T1PR = 14;
	T1MR0 = 2000000;							//2sec
	T1MCR = (1<<0)|(1<<1);
	T1TCR = (1<<0);
	
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
